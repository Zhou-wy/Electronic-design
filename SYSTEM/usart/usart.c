#include "sys.h"
#include "usart.h"	
#include "mode.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  


#define _USART1_Mode   1

void uart_init(u32 bound){
      //GPIO�˿�����
      GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;
         
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1��GPIOAʱ��
 
#if _USART1_Mode==0 
        //USART1_TX   GPIOA.9
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
      GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9       
      //USART1_RX	  GPIOA.10��ʼ��
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
      GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
#endif
    
#if _USART1_Mode==1 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);   //ʹ�ܴ���1����ӳ��
      //USART1_TX   
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;         //PB6
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
      GPIO_Init(GPIOB, &GPIO_InitStructure);               
      //USART1_RX	 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;             //PB7
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
      GPIO_Init(GPIOB, &GPIO_InitStructure);                
#endif

       
      //Usart1 NVIC ����
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
        NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
      
       //USART ��ʼ������

        USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
        USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

      USART_Init(USART1, &USART_InitStructure); //��ʼ������1
      USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
      USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}


u8 BUFF,flag=0; 
#include "My_PWM.h"
#include "Debug.h"

void USART1_IRQHandler(void)                	//����1�жϷ������
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
     {
         BUFF = USART_ReceiveData(USART1);   //��������
         if(BUFF=='0')
         {
					Fast_Land();	//��ͣ						
         }
         if(BUFF=='1')
         {
					 Low_Land();//��������						
         }
         if(BUFF=='2')
         {
						SoftReset();//�����λ
         }
         if(BUFF=='3')
         {
					 printf("1");
						Mode_1_Debug();
         }
         if(BUFF=='4')
         {	
						Mode_2_Debug();
         }
				 if(BUFF=='5')
         {
				    Mode_3_Debug();
         }
         if("BUFF=='6'")
				 {
						Mode_4_Debug();
				 }
				  if("BUFF=='7'")
				 {
						Mode_5_Debug();
				 }
				   if("BUFF=='8'")
				 {
						Mode_6_Debug();
				 }
				   if("BUFF=='9'")
				 {
						Mode_7_Debug();
				 }
				   if("BUFF=='A'")
				 {
						Mode_8_Debug();
				 }
				   if("BUFF=='B'")
				 {
						Mode_9_Debug();
				 }
         
     }    
}        

#endif	

