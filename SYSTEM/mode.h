#ifndef __MODE_H
#define __MODE_H
#include "stm32f10x.h"
#include "delay.h"
#include "pid.h"
#include "TIM_interrupt.h"
#include "Control.h"
#include "Debug.h"
#include "led.h"
void Low_Land(void);
void SoftReset(void);
void Fast_Land(void);
void Mode_1_Debug(void);
void Mode_2_Debug(void);
void Mode_3_Debug(void);
void Mode_4_Debug(void);
void Mode_5_Debug(void);
void Mode_6_Debug(void);
void Mode_7_Debug(void);
void Mode_8_Debug(void);
void Mode_9_Debug(void);

#endif
