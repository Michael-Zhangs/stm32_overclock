void HSE_Init(uint32_t RCC_PLLMul_x)//��Χ2-16
{
    ErrorStatus HSEStatus;//����
    //����RCC�����򲻻���Ч��
    RCC_DeInit();

    //��HSE
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStatus=RCC_WaitForHSEStartUp();

    //�ж�HSE��״̬
    if(HSEStatus==SUCCESS)
    {
        //������ֱ�ӳ��ģ����flash
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        FLASH_SetLatency(FLASH_Latency_2);

        //��AHB APB��APB����Ƶ
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );
        RCC_PCLK1Config( RCC_HCLK_Div2 );
        RCC_PCLK2Config( RCC_HCLK_Div1 );


        //����PLL���ٷ���������Ҫ�����ú��PLL
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
        //ʹ��PLL
        RCC_PLLCmd(ENABLE);

        //���PLL״̬���ȴ��ȶ��������
        while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET);
        //ϵͳʱ��ѡΪPLL
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK );
        while(RCC_GetSYSCLKSource()!=0x08);
    }
    else
    {
    //�������ʧ�ܣ�����ơ�
    LED_R_ON();
    }
}