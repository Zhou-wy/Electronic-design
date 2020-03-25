#include "6050_USART.h"
#include "stdio.h"
POSE Fly_Pose;              //���й���ʵʩ��̬
POSE Fly_Pose_Begain;       //������̬
float a[3],w[3],angle[3],T;
unsigned char Re_buf[11],temp_buf[11],counter;
unsigned char sign;
unsigned char Temp[11];
void Un_Pack_6050_Get_Begain(void); 
void Get_Begain_Pose(void);


void USART2_6050_init(void)
{
/****************************************************************************************************/    
    
	GPIO_InitTypeDef    GPIO_InitStructure;	   //���ڶ˿����ýṹ�����
	USART_InitTypeDef   USART_InitStructure;   //���ڲ������ýṹ�����
	NVIC_InitTypeDef    NVIC_InitStructure; 					   //�������������жϵĽṹ�����
    
	//ʹ�� USART2 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);   //��PA�˿�ʱ��

	//��USART2 Tx�����ͽţ���GPIO����Ϊ���츴��ģʽ   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				  //ѡ���ĸ�IO�� ��ѡ��PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //�趨IO�ڵ�����ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);    				  //��ʼ��GPIOA

	//��USART2 Rx�����սţ���GPIO����Ϊ��������ģʽ														  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //ѡ���ĸ�IO�� ��ѡ��PA3
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	          //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);                    //��ʼ��GPIOA
	  
	//����USART2����
	USART_InitStructure.USART_BaudRate = 115200;	                //���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	    //����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	        //ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);                       //��ʼ��USART2
	
	//�򿪷����жϺͽ����ж�(�����Ҫ�ж�)
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);  // ʹ��ָ����USART2�����ж�
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ʹ��ָ����USART2�����ж�
    
	//����2�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			   //ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	   //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;             //ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	               //���ж�
	NVIC_Init(&NVIC_InitStructure);							       //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	//ʹ�� USART2�� �������
	USART_Cmd(USART2, ENABLE);                             // USART2ʹ��

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART2, USART_FLAG_TC);                //�崮��2���ͱ�־
    
/***************************************************************************************************/    
    Get_Begain_Pose();                                    //��ȡ��ʼ��̬  
}

void USART2_IRQHandler(void)		   //����2ȫ���жϷ�����
{ 
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
     {
      Temp[counter] = USART_ReceiveData(USART2);   //��������
      //�������ĳ���
      //if(counter == 0 && Re_buf[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
	  if(counter == 0 && Temp[0] != 0x55) return;      //�� 0 �����ݲ���֡ͷ������
      counter++; 
      if(counter==11) //���յ� 11 ������
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //���¸�ֵ��׼����һ֡���ݵĽ���
         sign=1;
      }
			Un_Pack_6050();				//�ڴ����ж��н��6050����
   }
}

void Un_Pack_6050(void)       //����6050���ݰ�
{
    if(sign)
    {  
     memcpy(Temp,Re_buf,11);
     sign=0;
     if(Re_buf[0]==0x55)       //���֡ͷ
     {  
        switch(Re_buf[1])
        {
           case 0x51: //��ʶ������Ǽ��ٶȰ�
              Fly_Pose.X_a = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X����ٶ�
              Fly_Pose.Y_a = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y����ٶ�
              Fly_Pose.Z_a = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z����ٶ�
              Fly_Pose.T   = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;     //�¶�
              break;
           case 0x52: //��ʶ������ǽ��ٶȰ�
              Fly_Pose.X_w = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
              Fly_Pose.Y_w = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
              Fly_Pose.Z_w = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
              Fly_Pose.T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
              break;
           case 0x53: //��ʶ������ǽǶȰ�
              Fly_Pose.X_angle = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
              Fly_Pose.Y_angle = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
              Fly_Pose.Z_angle = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
              Fly_Pose.T       = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //�¶�

              break;
           default:  break;
        } 
     }   
    }
}

void Un_Pack_6050_Get_Begain(void)       //����6050���ݰ�
{
    if(sign)
    {  
     memcpy(Temp,Re_buf,11);
     sign=0;
     if(Re_buf[0]==0x55)       //���֡ͷ
     {  
        switch(Re_buf[1])
        {
           case 0x51: //��ʶ������Ǽ��ٶȰ�
              Fly_Pose_Begain.X_a = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X����ٶ�
              Fly_Pose_Begain.Y_a = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y����ٶ�
              Fly_Pose_Begain.Z_a = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z����ٶ�
              Fly_Pose_Begain.T   = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;     //�¶�
              break;
           case 0x52: //��ʶ������ǽ��ٶȰ�
              Fly_Pose_Begain.X_w = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;      //X����ٶ�
              Fly_Pose_Begain.Y_w = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y����ٶ�
              Fly_Pose_Begain.Z_w = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z����ٶ�
              Fly_Pose_Begain.T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //�¶�
              break;
           case 0x53: //��ʶ������ǽǶȰ�
              Fly_Pose_Begain.X_angle = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X���ת�ǣ�x �ᣩ
              Fly_Pose_Begain.Y_angle = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y�ḩ���ǣ�y �ᣩ
              Fly_Pose_Begain.Z_angle = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z��ƫ���ǣ�z �ᣩ
              Fly_Pose_Begain.T       = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //�¶�

              break;
           default:  break;
        } 
     }   
    }
}




void Get_Begain_Pose()           //���6050�ĳ�ʼ��̬
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

