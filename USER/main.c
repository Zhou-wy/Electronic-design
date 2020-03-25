#include "include.h"


int main(void)
{	
    delay_init();                                           //��ʼ��delay������ϵͳʱ�� 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 	//����NVIC�жϷ���
    Motor_init();                                           //����ʼ��
    uart_init(9600);                                        //��ʼ������ ������ȼ�
    USART2_6050_init();                                     //��ʼ��6050
    Ultrasonic_Usart_Init();                                //��������ʼ��
    Control_Init();                                         //���Ƴ�ʼ��
    TIM2_10Ms_Interrupt_Init();                             //��ʱ���жϳ�ʼ��
    
//		Debug_Wait();                                          //�ȴ������ź�/    TIM_Cmd(TIM2,ENABLE);		                            //������ʱ��     ��Ҫʱ�������� 
   	while(1)
    {
			printf("Debug Begin !");
			Hight_Limit(); 
//    Un_Pack_6050();                                     //���6050������ 
 //	Mode_1();
    }
}



/*************************************ʱ���ж�*****************************************/


void _10ms_T_interrupt()
{ 
    Ult_Once_Measure();                                 //���¸߶���Ϣ  
    Hight_Limit();                                      //�޸�  
  
}

void _20ms_T_interrupt()
{ 
    Speed_Measure();                                    //�ٶȲ���
    Pose_W_Pid_Count();                                 //��̬���ڻ�
    Inner_PID_Count();                                  //�ڻ�����
    Inner_PID_Output();                                 //�ڻ�һ�μ������
//    Outer_PID_Count();
}


void _40ms_T_interrupt()
{
    
    Turn_Pid_Count();                                   //����pid����
    Turn_Pid_Contorl();                                 //����pid����
//    Pose_Pid_Count();
//    Outer_PID_Count();
}



void _80ms_T_interrupt()
{
    Pose_Pid_Count();                                   //��̬�⻷
}

void _60ms_T_interrupt()
{
    Outer_PID_Count();                                  //�⻷һ�μ���    
}

void _100ms_T_interrupt()
{
     
}
    
void _120ms_T_interrupt()
{

}

void _160ms_T_interrupt()
{
    
}
/****************************************************************************************/
