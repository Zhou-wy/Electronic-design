#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stm32f10x.h"
#include "delay.h"
#include "stdlib.h"
#define ULT_MODE  0

#define ULTRASONIC_ONCE_MAX 50

/************************����ģʽ*******************************/
#if ULT_MODE==0

struct HIGHT{
    u16 Now;
    u16 Last;
    u16 Begian;
};    
extern struct HIGHT Hight;

//����������
//RX PB11
//TX PB10
void Ultrasonic_Usart_Init(void);   //����������ģʽ��ʼ��
void Ult_Once_Measure(void);        //����һ�γ���������

#endif
/************************��ƽ����ģʽ**************************/

#if ULT_MODE==1

#define Trig_H()   GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define Trig_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define Echo   	   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
void Ultrasonic_Init(void);      //������ģ���ʼ����ռ��TIM3��ʱ����
u16  Ult_Once_Measure(void);     //����һ�β�����ֵ
u16  Ult_Measure(u8);            //����N�β�����ƽ��ֵ   ע������ �ܳ���Ϊ65m

#endif
/**************************************************************/

#endif
