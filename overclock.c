void HSE_Init(uint32_t RCC_PLLMul_x)//范围2-16
{
    ErrorStatus HSEStatus;//定义
    //重置RCC，否则不会有效果
    RCC_DeInit();

    //打开HSE
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStatus=RCC_WaitForHSEStartUp();

    //判断HSE的状态
    if(HSEStatus==SUCCESS)
    {
        //库里面直接抄的，针对flash
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        FLASH_SetLatency(FLASH_Latency_2);

        //对AHB APB１APB２分频
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );
        RCC_PCLK1Config( RCC_HCLK_Div2 );
        RCC_PCLK2Config( RCC_HCLK_Div1 );


        //设置PLL，官方库中声明要先设置后打开PLL
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
        //使能PLL
        RCC_PLLCmd(ENABLE);

        //检测PLL状态，等待稳定跳出语句
        while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET);
        //系统时钟选为PLL
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK );
        while(RCC_GetSYSCLKSource()!=0x08);
    }
    else
    {
    //如果配置失败，亮红灯。
    LED_R_ON();
    }
}