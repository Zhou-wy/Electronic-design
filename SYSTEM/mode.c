#include "mode.h"

extern PID *Hight_Pid; 
/**********��������**************/
void Low_Land(void)
{	
		TIM_Cmd(TIM2,DISABLE);
		TIM_SetCompare1(TIM1,1620); 
		TIM_SetCompare2(TIM1,1620);
		TIM_SetCompare3(TIM1,1400);				//�Ӳ���7.0%ռ�ձȶ��
		TIM_SetCompare4(TIM1,1560);				//�Ӳ���7.8%ռ�ձȶ�� 
	
}
/*********�����λ************/
void SoftReset(void)
{
    __set_FAULTMASK(1); // �ر������ж�
    NVIC_SystemReset(); // ��λ
}
/********��������************/
void Fast_Land(void)
{
		 TIM_SetCompare1(TIM1,1000); 
		 TIM_SetCompare2(TIM1,1000); 
		 TIM_Cmd(TIM2,DISABLE);
}
/************�������ֿ�ʼ*******************/
void Mode_1_Debug(void)//Ҫ��1:��ͣ����A��0.3����3S����
{
		printf("2");
		 TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		 Reset_PID();																	//���PID��������
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

void Mode_2_Debug(void)//Ҫ��2����ͣCD��3S����
{
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.15 ,15   ,0.25   ,0); 
		delay_s(5);
		Low_Land();
}

void Mode_3_Debug(void)//Ҫ��3����ͣ��AB����LED1����������CD����LED2
{
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
		TIM_Cmd(TIM2,ENABLE);
		Mode_Change_Hight();
		Low_Land();
}

void Mode_4_Debug(void)//Ҫ��4:��ȷ������CD�Σ�110cm����ͣ5S LED1��LED2��
{
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
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
/************�����������*******************/



/************���Ӳ��ֿ�ʼ********************/
void Mode_5_Debug(void)//Ҫ��4:��ȷ������CD�Σ�110cm������Ϊ����
{
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
		TIM_Cmd(TIM2,ENABLE);
		Hight_Pid=PID_Init(1.10 ,15   ,0.25   ,0); 
/*****************************************
		���ֶ�����	
*****************************************/
}

void Mode_6_Debug(void)//Ҫ��4:��ȷ������CD�Σ�110cm����ͣ5S LED1��LED2����������3CM
{
/****************������޸�**********************/
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
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

void Mode_7_Debug(void)//Ҫ��7���������
{		
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
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

void Mode_8_Debug(void)//Ҫ��8����������
{
		TIM2_10Ms_Interrupt_Init();									//��ʼ����ʱ��
		Reset_PID();																	//���PID��������
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

void Mode_9_Debug(void)//Ҫ��9�����ɷ����Զ���켣
{
	Mode_1();
	Low_Land();	
}


