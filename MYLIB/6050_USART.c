#include "6050_USART.h"
#include "stdio.h"
POSE Fly_Pose;              //飞行过程实施姿态
POSE Fly_Pose_Begain;       //启动姿态
float a[3],w[3],angle[3],T;
unsigned char Re_buf[11],temp_buf[11],counter;
unsigned char sign;
unsigned char Temp[11];
void Un_Pack_6050_Get_Begain(void); 
void Get_Begain_Pose(void);


void USART2_6050_init(void)
{
/****************************************************************************************************/    
    
	GPIO_InitTypeDef    GPIO_InitStructure;	   //串口端口配置结构体变量
	USART_InitTypeDef   USART_InitStructure;   //串口参数配置结构体变量
	NVIC_InitTypeDef    NVIC_InitStructure; 					   //定义用于配置中断的结构体变量
    
	//使能 USART2 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//打开串口复用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);   //打开PA端口时钟

	//将USART2 Tx（发送脚）的GPIO配置为推挽复用模式   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //选定哪个IO口 现选定PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);    				  //初始化GPIOA

	//将USART2 Rx（接收脚）的GPIO配置为浮空输入模式														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //选定哪个IO口 现选定PA3
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	          //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);                    //初始化GPIOA
	  
	//配置USART2参数
	USART_InitStructure.USART_BaudRate = 115200;	                //波特率设置：115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);                       //初始化USART2
	
	//打开发送中断和接收中断(如果需要中断)
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  // 使能指定的USART2发送中断
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // 使能指定的USART2接收中断
    
	//串口2中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			   //指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;             //指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //打开中断
	NVIC_Init(&NVIC_InitStructure);							       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	//使能 USART2， 配置完毕
	USART_Cmd(USART2, ENABLE);                             // USART2使能

	//如下语句解决第1个字节无法正确发送出去的问题
    USART_ClearFlag(USART2, USART_FLAG_TC);                //清串口2发送标志
    
/***************************************************************************************************/    
    Get_Begain_Pose();                                    //获取初始姿态  
}

void USART2_IRQHandler(void)		   //串口2全局中断服务函数
{ 
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
     {
      Temp[counter] = USART_ReceiveData(USART2);   //接收数据
      //网购给的程序
      //if(counter == 0 && Re_buf[0] != 0x55) return;      //第 0 号数据不是帧头，跳过
	  if(counter == 0 && Temp[0] != 0x55) return;      //第 0 号数据不是帧头，跳过
      counter++; 
      if(counter==11) //接收到 11 个数据
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //重新赋值，准备下一帧数据的接收
         sign=1;
      }
			Un_Pack_6050();				//在串口中断中解包6050数据
   }
}

void Un_Pack_6050(void)       //解析6050数据包
{
    if(sign)
    {  
     memcpy(Temp,Re_buf,11);
     sign=0;
     if(Re_buf[0]==0x55)       //检查帧头
     {  
        switch(Re_buf[1])
        {
           case 0x51: //标识这个包是加速度包
              Fly_Pose.X_a = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
              Fly_Pose.Y_a = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
              Fly_Pose.Z_a = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
              Fly_Pose.T   = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;     //温度
              break;
           case 0x52: //标识这个包是角速度包
              Fly_Pose.X_w = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X轴角速度
              Fly_Pose.Y_w = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
              Fly_Pose.Z_w = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
              Fly_Pose.T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
              break;
           case 0x53: //标识这个包是角度包
              Fly_Pose.X_angle = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
              Fly_Pose.Y_angle = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
              Fly_Pose.Z_angle = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
              Fly_Pose.T       = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //温度

              break;
           default:  break;
        } 
     }   
    }
}

void Un_Pack_6050_Get_Begain(void)       //解析6050数据包
{
    if(sign)
    {  
     memcpy(Temp,Re_buf,11);
     sign=0;
     if(Re_buf[0]==0x55)       //检查帧头
     {  
        switch(Re_buf[1])
        {
           case 0x51: //标识这个包是加速度包
              Fly_Pose_Begain.X_a = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
              Fly_Pose_Begain.Y_a = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
              Fly_Pose_Begain.Z_a = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
              Fly_Pose_Begain.T   = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;     //温度
              break;
           case 0x52: //标识这个包是角速度包
              Fly_Pose_Begain.X_w = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X轴角速度
              Fly_Pose_Begain.Y_w = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
              Fly_Pose_Begain.Z_w = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
              Fly_Pose_Begain.T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
              break;
           case 0x53: //标识这个包是角度包
              Fly_Pose_Begain.X_angle = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角（x 轴）
              Fly_Pose_Begain.Y_angle = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
              Fly_Pose_Begain.Z_angle = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角（z 轴）
              Fly_Pose_Begain.T       = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //温度

              break;
           default:  break;
        } 
     }   
    }
}




void Get_Begain_Pose()           //获得6050的初始姿态
{
    u8 times=100;
    while(1)
    {
        while(times--)
        {
            delay_ms(10);
            Un_Pack_6050_Get_Begain();
        }
        break;
//        if(Fly_Pose_Begain.T!=0)
//            break;
    }
}

