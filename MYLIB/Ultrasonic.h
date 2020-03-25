#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stm32f10x.h"
#include "delay.h"
#include "stdlib.h"
#define ULT_MODE  0

#define ULTRASONIC_ONCE_MAX 50

/************************串口模式*******************************/
#if ULT_MODE==0

struct HIGHT{
    u16 Now;
    u16 Last;
    u16 Begian;
};    
extern struct HIGHT Hight;

//串口三引脚
//RX PB11
//TX PB10
void Ultrasonic_Usart_Init(void);   //超声波串口模式初始化
void Ult_Once_Measure(void);        //开启一次超声波测量

#endif
/************************电平触发模式**************************/

#if ULT_MODE==1

#define Trig_H()   GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define Trig_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define Echo   	   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
void Ultrasonic_Init(void);      //超声波模块初始化（占用TIM3定时器）
u16  Ult_Once_Measure(void);     //返回一次测量的值
u16  Ult_Measure(u8);            //返回N次测量的平均值   注意防溢出 总长度为65m

#endif
/**************************************************************/

#endif
