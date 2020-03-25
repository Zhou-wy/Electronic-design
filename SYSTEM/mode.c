#include "mode.h"

extern PID *Hight_Pid; 
/**********缓慢降落**************/
void Low_Land(void)
{	
		TIM_Cmd(TIM2,DISABLE);
		TIM_SetCompare1(TIM1,1620); 
		TIM_SetCompare2(TIM1,1620);
		TIM_SetCompare3(TIM1,1400);				//接补偿7.0%占空比舵机
		TIM_SetCompare4(TIM1,1560);				//接补偿7.8%占空比舵机 
	
}
/*********软件复位************/
void SoftReset(void)
{
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}
/********紧急降落************/
void Fast_Land(void)
{
		 TIM_SetCompare1(TIM1,1000); 
		 TIM_SetCompare2(TIM1,1000); 
		 TIM_Cmd(TIM2,DISABLE);
}
/************基础部分开始*******************/
void Mode_1_Debug(void)//要求1:悬停超过A（0.3）点3S以上
{
		printf("2");
		 TIM2_10Ms_Interrupt_Init();									//初始化定时器
		 Reset_PID();																	//清除PID残余数据
		 TIM_Cmd(TIM2,ENABLE);
		printf("3");
//		while(1)
//		 {
//			 if(Hight.Now<520&&Hight.Now>480)
//			 {
//				 delay_s(1);
//				 if(Hight.Now<520&&Hight.Now>480)
//				 {
//					 delay_s(5);
//					 Fast_Land();
//					 break;
//				 }
//				 
//			 }
//		 }	
}

void Mode_2_Debug(void)//要求2：悬停CD段3S以上
{
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.15 ,15   ,0.25   ,0); 
		delay_s(5);
		Low_Land();
}

void Mode_3_Debug(void)//要求3：悬停于AB段亮LED1，后上升至CD段亮LED2
{
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Mode_Change_Hight();
		Low_Land();
}

void Mode_4_Debug(void)//要求4:精确定高至CD段（110cm）悬停5S LED1和LED2亮
{
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.10 ,15   ,0.25   ,0); 
		if(Hight.Now>1080&&Hight.Now<1120)
		{
			delay_s(1);
			if(Hight.Now>1080&&Hight.Now<1120)
			{
				LED_y=0;
				LED_G=0;
				delay_s(10);
				Low_Land();
			}
			
		}	
}
/************基础部分完结*******************/



/************发挥部分开始********************/
void Mode_5_Debug(void)//要求4:精确定高至CD段（110cm），人为干扰
{
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.10 ,15   ,0.25   ,0); 
/*****************************************
		需手动降落	
*****************************************/
}

void Mode_6_Debug(void)//要求4:精确定高至CD段（110cm）悬停5S LED1和LED2亮，误差不超过3CM
{
/****************视情况修改**********************/
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.10 ,15   ,0.25   ,0); 
		if(Hight.Now>1085&&Hight.Now<1115)
		{
			delay_s(1);
			if(Hight.Now>1085&&Hight.Now<1115)
			{
				LED_y=0;
				LED_G=0;
				delay_s(10);
				Low_Land();
			}
			
		}	
}

void Mode_7_Debug(void)//要求7：步进变高
{		
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(0.5 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.55 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.60 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.65 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.7 ,15   ,0.25   ,0); 
		delay_s(3);
		Low_Land();
	
}

void Mode_8_Debug(void)//要求8：加载砝码
{
		TIM2_10Ms_Interrupt_Init();									//初始化定时器
		Reset_PID();																	//清除PID残余数据
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(0.5 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.55 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.60 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.65 ,15   ,0.25   ,0); 
		delay_s(3);
		Hight_Pid=PID_Init(0.7 ,15   ,0.25   ,0); 
		delay_s(3);
		Low_Land();
	
}

void Mode_9_Debug(void)//要求9：自由发挥自动变轨迹
{
	Mode_1();
	Low_Land();	
}


