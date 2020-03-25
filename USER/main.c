#include "include.h"


int main(void)
{	
    delay_init();                                           //初始化delay函数和系统时钟 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 	//设置NVIC中断分组
    Motor_init();                                           //马达初始化
    uart_init(9600);                                        //初始化串口 最高优先级
    USART2_6050_init();                                     //初始化6050
    Ultrasonic_Usart_Init();                                //超声波初始化
    Control_Init();                                         //控制初始化
    TIM2_10Ms_Interrupt_Init();                             //定时器中断初始化
    
//		Debug_Wait();                                          //等待启动信号/    TIM_Cmd(TIM2,ENABLE);		                            //启动定时器     需要时自行启动 
   	while(1)
    {
			printf("Debug Begin !");
			Hight_Limit(); 
//    Un_Pack_6050();                                     //解包6050的数据 
 //	Mode_1();
    }
}



/*************************************时基中断*****************************************/


void _10ms_T_interrupt()
{ 
    Ult_Once_Measure();                                 //更新高度信息  
    Hight_Limit();                                      //限高  
  
}

void _20ms_T_interrupt()
{ 
    Speed_Measure();                                    //速度测量
    Pose_W_Pid_Count();                                 //姿态环内环
    Inner_PID_Count();                                  //内环计算
    Inner_PID_Output();                                 //内环一次计算输出
//    Outer_PID_Count();
}


void _40ms_T_interrupt()
{
    
    Turn_Pid_Count();                                   //自旋pid运算
    Turn_Pid_Contorl();                                 //自旋pid控制
//    Pose_Pid_Count();
//    Outer_PID_Count();
}



void _80ms_T_interrupt()
{
    Pose_Pid_Count();                                   //姿态外环
}

void _60ms_T_interrupt()
{
    Outer_PID_Count();                                  //外环一次计算    
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
