#include "TIM_interrupt.h"


void TIM2_10Ms_Interrupt_Init(void)      //定时器2产生定时器中断
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;

	//定时器3参数配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//使能TIM2
	TIM_DeInit(TIM2);		//复位TIM2
	
	TIM_TimeBaseStructure.TIM_Period=TIM2_Period;			//定时器溢出周期								   			
	TIM_TimeBaseStructure.TIM_Prescaler=TIM2_Prescaler;			//分频系数											
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	//向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);		//配置初始化参数
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 	//清除TIM3中断标志
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//计数器溢出中断

	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;		//配置TIM3溢出中断	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;	//抢占优先级：3，子优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//中断使能
	NVIC_Init(&NVIC_InitStructure);		//中断参数初始化
	
	TIM_Cmd(TIM2,DISABLE);		//启动定时器     需要时自行启动
    
}

static u16 Init_times=0;
void TIM2_IRQHandler(void)                                  //定时器中断
{	     
    if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET )
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 	    //清除TIM3中断标志
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
