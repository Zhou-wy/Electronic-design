#ifndef __DEBUG_H__
#define __DEBUG_H__ 
#include "stm32f10x.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "My_PWM.h"
#include "PID.h"
#include "6050_USART.h"
#include "Ultrasonic.h"
#include "TIM_interrupt.h"
#include "Control.h"

void Debug_Wait(void);
void Debug_Printf(void);
void Hight_Limit(void);    //限高保安全
void Mode_Change_Hight(void);
void SoftReset(void);
void Mode_1(void);
extern u8 Begain_Flag;

#endif
