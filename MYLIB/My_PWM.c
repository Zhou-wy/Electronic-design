#include "My_PWM.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_AFIO, ENABLE); 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	
/**********************开启四路PWM输出*************************/
                                                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;         //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                              

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2预装载使能	
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH3预装载使能	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能	    
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
    TIM_SetCompare1(TIM1,1000);  
    TIM_SetCompare2(TIM1,1000);  
    TIM_SetCompare3(TIM1,1400);  
    TIM_SetCompare4(TIM1,1560);  
        	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
   
}


void Motor_init(void)        //初始化TIM1定时器 产生4路50Hz PMW
{
    TIM1_PWM_Init(20000,71); //50HZ PWM
//    Set_Duoji1(90);          //设置舵机初始角度
//    Set_Duoji2(90);

		TIM_SetCompare3(TIM1,1400);				//接补偿7.0%占空比舵机  
		TIM_SetCompare4(TIM1,1560);				//接补偿7.8%占空比舵机
}
/****************************************************************************/   

static int Youmen_fazhi=0;         //油门基准值 单位1Us


/*****************重要函数****************/
//电机的死区为20ms*0.06=1.2ms
void Set_Motor1_Speed(float date)  //设置马达1的速率
{
    if((date*6)+1200+Youmen_fazhi<1200)
        TIM_SetCompare1(TIM1,1200);    
    else if((date*6)+1200+Youmen_fazhi>1990)
        TIM_SetCompare1(TIM1,1990);  
    else 
        TIM_SetCompare1(TIM1,(int)(date*6)+1200+Youmen_fazhi);            
}

void Set_Motor2_Speed(float date)  //设置马达2的速率
{
    if((date*6)+1200+Youmen_fazhi<1200)
        TIM_SetCompare2(TIM1,1200);    
    else if((date*6)+1200+Youmen_fazhi>1990)
        TIM_SetCompare2(TIM1,1990);  
    else 
        TIM_SetCompare2(TIM1,(int)(date*6)+1200+Youmen_fazhi);            
}
/*******************************************/

void Change_Acc(int date)              //增加或减小油门基准值  单位1us
{
    Youmen_fazhi+=date; 
}

void Set_Acc(u16 date)                 //设置油门基准值 单位1us
{
    Youmen_fazhi=date;
}

/*************不考虑油门**************/
void Set_Motor1_Speed_root(float date)   //设置马达1的速率 入口参数：百分比 0-100
{
    if(date<0)
    {
        date=0;
    }
    if(date>=98)
    {
        date=98;
    }
    TIM_SetCompare1(TIM1,(u16)(date*10+1000));
    
}

void Set_Motor2_Speed_root(float date)   //改变马达2的速率 入口参数：百分比 0-100
{
    if(date<0)
    {
        date=0;
    }
    if(date>=98)
    {
        date=98;
    }
    TIM_SetCompare2(TIM1,(u16)(date*10+1000));
}

/***************************************************************************/

void Set_Duoji1(u8 date)         //设置舵机1的偏转角度
{
    
    TIM_SetCompare3(TIM1,500+(u16)(date*2000.0/180.0)); 
}


void Change_Duoji1(int date)         //设置舵机1的偏转角度
{
    
    TIM_SetCompare3(TIM1,(u16)(TIM1->CCR3+date)); 
}

void Set_Duoji2(u8 date)         //设置舵机2的偏转角度
{
    TIM_SetCompare4(TIM1,500+(u16)(date*2000.0/180.0));
}

void Change_Duoji2(int date)         //设置舵机2的偏转角度
{
    TIM_SetCompare4(TIM1,(u16)(TIM1->CCR3+date)); 
}



