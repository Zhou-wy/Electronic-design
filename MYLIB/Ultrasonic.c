#include "Ultrasonic.h"
#include "stdio.h"

#if ULT_MODE==0

struct HIGHT Hight;
static u8 Ult_Flag;

static u8 Frist_flag;   //第一次测量标志位

void Ultrasonic_Usart_Init()   //超声波串口模式初始化
{
   u8 times=2; 
    
   USART_InitTypeDef USART_InitStructure;  
   NVIC_InitTypeDef NVIC_InitStructure;   
   GPIO_InitTypeDef GPIO_InitStructure;     
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
   // Configure USART3 Rx (PB.11) as input floating    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
   GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
   // Configure USART3 Tx (PB.10) as alternate function push-pull  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
   GPIO_Init(GPIOB, &GPIO_InitStructure);  
 
   USART_InitStructure.USART_BaudRate = 9600;  
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
   USART_InitStructure.USART_StopBits = USART_StopBits_1;  
   USART_InitStructure.USART_Parity = USART_Parity_No;  
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    
   // Configure USART3   
   USART_Init(USART3, &USART_InitStructure);
  
  // Enable USART1 Receive interrupts 
   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  
  
   // Enable the USART3 Interrupt   
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			   //指定中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;             //指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //打开中断
	NVIC_Init(&NVIC_InitStructure);							       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
   
    // Enable the USART3   
     USART_Cmd(USART3, ENABLE);
    //如下语句解决第1个字节无法正确发送出去的问题
    USART_ClearFlag(USART3, USART_FLAG_TC);                        //清串口3发送标志
    Ult_Flag=0;
    Frist_flag=1;
    
    while(times--)
    {
        delay_ms(50);
        Hight.Begian=Hight.Now;
    }
}

//限幅滤波
void  Distance_Filiter(u16 date) 
{
    if(abs(((int)date-(int)Hight.Now))<ULTRASONIC_ONCE_MAX)
    {
        Hight.Last=Hight.Now;
				if(abs(Hight.Now-260)<3)
				{
					Hight.Now = Hight.Last ;
				}
        Hight.Now = (u16)date; 
    } 
		
//			int del1,del2;
//			del1=abs((int)date-(int)Hight.Now);
//      Hight.Last=Hight.Now;
//     Hight.Now = (u16)date; 
//			del2= abs(Hight.Last-Hight.Now);
//			if(del1-del2<10||del1-del2>10)   
//			{
//				Hight.Now=del1+Hight.Now;
//			}
//			else 
//				Hight.Now = (u16)date; 
		
}


u8 Rec_Number;

void Ult_Once_Measure()       
{
    if(Ult_Flag==0)
    {
        USART_SendData(USART3,0x55);
        Ult_Flag=1; 
        Rec_Number=0;                
    }
}

u16 Data_Temp[2]={0,0};
void USART3_IRQHandler(void)                	
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
    {
        Data_Temp[Rec_Number]=USART_ReceiveData(USART3);
        Rec_Number++;
        if(Rec_Number==2)
        {
            if(Frist_flag==1)
            {
                Frist_flag=0;
                Hight.Last=Hight.Now=(Data_Temp[0]<<8)+Data_Temp[1];
                Ult_Flag=0;
            }
            else
            {
                Distance_Filiter((Data_Temp[0]<<8)+Data_Temp[1]);
                Ult_Flag=0;
            }                
        }
       USART_ClearFlag(USART3, USART_IT_RXNE);
    }   
} 

#endif

#if ULT_MODE==1
static u8 Overflow=0;          //溢出标志位
void Ultrasonic_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
    
    
/*************************配置引脚*****************************/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;				
	GPIO_Init(GPIOA, &GPIO_InitStructure);
/**************************************************************/
    
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//使能TIM3
	TIM_DeInit(TIM3);
	//TIM_TimeBaseStructure.TIM_Period=0xffff;			
    TIM_TimeBaseStructure.TIM_Period=1000;	    
	TIM_TimeBaseStructure.TIM_Prescaler=719;	//10us一个数						
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	   
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//计数器溢出中断
	
    Trig_L();  	                //将发射脚的电平拉低	                	
	//TIM_Cmd(TIM3,ENABLE);
}

u16  Ult_Once_Measure(void)     //返回一次测量的值
{
    u16 TIM_CNT;
	Trig_H();
	delay(400);
	Trig_L();
    while(!Echo);
    TIM_Cmd(TIM3,ENABLE);       //打开
    TIM3->CNT=0;
    while( Echo&&(!Overflow) )
    {
        TIM_Cmd(TIM3,ENABLE);       //打开
    }        
    TIM_Cmd(TIM3,DISABLE);      //关闭
    TIM_CNT=TIM3->CNT;
    if(Overflow==1)
    {
        Overflow=0;
        //printf("error //to long \r\n");
        return 0;
    }
    else        
        return TIM_CNT*1.7;         //单位mm
}

u16  Ult_Measure(u8 N)           //返回N次测量的平均值
{
    u8 i;
    u16 distans=0;
    for(i=0;i<N;i++)
    {
        distans+=Ult_Once_Measure();
    }
    return distans/N;
}

void TIM3_IRQHandler(void)      //中断防溢出
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)				   	      
	{
        Overflow=1;
        TIM_Cmd(TIM3,DISABLE);      //关闭
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
#endif
