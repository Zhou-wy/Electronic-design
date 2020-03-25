#include "TIM_interrupt.h"


void TIM2_10Ms_Interrupt_Init(void)      //��ʱ��2������ʱ���ж�
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;

	//��ʱ��3��������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//ʹ��TIM2
	TIM_DeInit(TIM2);		//��λTIM2
	
	TIM_TimeBaseStructure.TIM_Period=TIM2_Period;			//��ʱ���������								   			
	TIM_TimeBaseStructure.TIM_Prescaler=TIM2_Prescaler;			//��Ƶϵ��											
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);		//���ó�ʼ������
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 	//���TIM3�жϱ�־
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//����������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;		//����TIM3����ж�	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//��ռ���ȼ���3�������ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);		//�жϲ�����ʼ��
	
	TIM_Cmd(TIM2,DISABLE);		//������ʱ��     ��Ҫʱ��������
    
}

static u16 Init_times=0;
void TIM2_IRQHandler(void)                                  //��ʱ���ж�
{	     
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET )
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 	    //���TIM3�жϱ�־
        Init_times++;
        _10ms_T_interrupt();
        if(Init_times%2==0)
        {
            _20ms_T_interrupt(); 
        }
        if(Init_times%4==0)
        {
            _40ms_T_interrupt(); 
        }
        if(Init_times%6==0)
        {
            _60ms_T_interrupt(); 
        }
        if(Init_times%8==0)
        {
            _80ms_T_interrupt(); 
        }
        if(Init_times%10==0)
        {
            _100ms_T_interrupt(); 
        } 
        
        if(Init_times%12==0)
        {
            _120ms_T_interrupt(); 
        }
        if(Init_times%16==0)
        {
            _160ms_T_interrupt(); 
        }
        if(Init_times==5000)   
            Init_times=1;           
    }
}
