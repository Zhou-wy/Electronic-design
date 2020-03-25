#include "Debug.h"
#include "core_cm3.h"
#include "led.h"

u8 Begain_Flag=0;
extern PID *Hight_Pid;
extern u8 flag;
extern u8  biao;

void Debug_Wait(void)
{
    while(1)
    {
        if(Begain_Flag==1)
            break;
         //printf("Wait Begain_Flag\r\n");
         //printf("%d\r\n",Hight.Now);
    }
}

void Debug_Printf(void)
{
      printf("CCR1:%d\r\n",TIM1->CCR1);
      printf("CCR2:%d\r\n",TIM1->CCR2); 
      printf("CCR3:%d\r\n",TIM1->CCR3);
      printf("CCR4:%d\r\n",TIM1->CCR4);
      printf("X:%.2f   Y:%.2f   Z:%.2f\r\n",Fly_Pose.X_a,Fly_Pose.Y_a,Fly_Pose.Z_w);       
      printf("Hight:%d\r\n",Hight.Now);  
}

void Hight_Limit()    //限高保安全
{
    if(Hight.Now>1500)                                  //紧急状态 断电卡死
    {
        TIM_Cmd(TIM2,DISABLE);
        Set_Motor1_Speed_root(0);
        Set_Motor2_Speed_root(0);    
        while(1);
    } 
}

u8 i=0;
float Pout=0;
void Mode_Change_Hight()
{	
		while(1)
				{
						Hight_Pid=PID_Init(0.5 ,15   ,0.25   ,0); 
						if(Hight.Now>=490&&Hight.Now<=510)
						{
								delay_s(1);								//延时1s
								if(Hight.Now>=490&&Hight.Now<=510)
								{
									LED_y=0;
									delay_s(3);							//延时3s
									Pout=Hight_Pid->Iout;
									LED_y=1;
									PID_Set_S(Hight_Pid,0.85);
									Hight_Pid->Kp = 20;
									biao = 1;								//关闭高度环和速度环计算
									break ;
									}
							}
				}
/******************************************************/
//			while(1)
//			{
//					if(Hight.Now>=Hight_Pid->Set*1000-10&&Hight.Now<=Hight_Pid->Set*1000+10)
//					{
//							PID_Set_S(Hight_Pid,0.7);
//							break ;
//					}
//			}
				delay_s(2);
				PID_Set_S(Hight_Pid,1.15);
				delay_s(1);
/**************************************************/
		while(1)
				{
//							PID_Set_S(Hight_Pid,0.7);
						if(Hight.Now>=1100&&Hight.Now<=1170)
						{
								Hight_Pid->Kp = 15;
								biao = 0;									//达到指定位置时打开pid计算		
								if(Hight.Now>=1100&&Hight.Now<=1170)
								{
									LED_G=0;
									delay_s(3);							//延时3s
									LED_y=1;
									break ;
									}
							}
				}
//				delay_s(1);
//				PID_Set_S(Hight_Pid,1.0);
//				delay_s(1);
/****************************************************/
//		while(1)
//		{
////						  PID_Set_S(Hight_Pid,1.0);
//						if(Hight.Now>=950&&Hight.Now<=1020)
//						{
//								Hight_Pid->Kp = 15;
//								biao = 0;							
//								if(Hight.Now>=990&&Hight.Now<=1010)
//								{
//									delay_s(5);							//延时5s
//									
//									PID_Set_S(Hight_Pid,0.8);
//									
//									
//									
//									biao = 1;	
////										flag = 0;	
//									break ;
//									}
//							}
//				}
/**********************************************************/
//		delay_s(1);
//		PID_Set_S(Hight_Pid,0.6);
//		delay_s(1);
//		PID_Set_S(Hight_Pid,0.5);
//		biao = 0;
/*************************************************************/
//					while(!(Hight.Now>=450&&Hight.Now<=550))
//					{
//							TIM_SetCompare1(TIM1,1425);  
//							TIM_SetCompare2(TIM1,1425);
//					}
					
}


void Mode_1(void)
{	
	while(1)
			{
					PID_Set_S(Hight_Pid,0.3);
					if(Hight.Now>=290&&Hight.Now<=310)
					{
						delay_s(1);								//延时1s
							if(Hight.Now>=290&&Hight.Now<=310)
							{
								delay_s(5);							//延时5s
								Pout=Hight_Pid->Iout;
								PID_Set_S(Hight_Pid,0.5);
								Hight_Pid->Kp = 20;
								biao = 1;								//关闭高度环和速度环计算
								break ;
								}
						}
			}
/******************************************************/
//			while(1)
//			{
//					if(Hight.Now>=Hight_Pid->Set*1000-10&&Hight.Now<=Hight_Pid->Set*1000+10)
//					{
//							PID_Set_S(Hight_Pid,0.7);
//							break ;
//					}
//			}
			delay_s(2);
			PID_Set_S(Hight_Pid,0.7);
			delay_s(1);
/**************************************************/
	while(1)
			{
//							PID_Set_S(Hight_Pid,0.7);
					if(Hight.Now>=650&&Hight.Now<=720)
					{
							Hight_Pid->Kp = 15;
							biao = 0;									//达到指定位置时打开pid计算		
							if(Hight.Now>=690&&Hight.Now<=710)
							{
								delay_s(5);							//延时5s
								PID_Set_S(Hight_Pid,0.85);
								Hight_Pid->Kp = 20;
								biao = 1;
								break ;
								}
						}
			}
			delay_s(1);
			PID_Set_S(Hight_Pid,1.0);
			delay_s(1);
/****************************************************/
	while(1)
	{
//						  PID_Set_S(Hight_Pid,1.0);
					if(Hight.Now>=950&&Hight.Now<=1020)
					{
							Hight_Pid->Kp = 15;
							biao = 0;							
							if(Hight.Now>=990&&Hight.Now<=1010)
							{
								delay_s(5);							//延时5s
								
								PID_Set_S(Hight_Pid,0.8);
								
								
								
								biao = 1;	
//										flag = 0;	
								break ;
								}
						}
			}
/**********************************************************/
	delay_s(1);
	PID_Set_S(Hight_Pid,0.6);
	delay_s(1);
	PID_Set_S(Hight_Pid,0.5);
	biao = 0;
/*************************************************************/
//					while(!(Hight.Now>=450&&Hight.Now<=550))
//					{
//							TIM_SetCompare1(TIM1,1425);  
//							TIM_SetCompare2(TIM1,1425);
//					}
			
	flag = 0;	

	
}



















