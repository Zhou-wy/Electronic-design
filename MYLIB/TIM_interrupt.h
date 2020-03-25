#ifndef __TIM_H
#define __TIM_H 
#include "stm32f10x.h"

#define TIM2_Period     (10000-1)  //10ms
#define TIM2_Prescaler  (72-1)

void _10ms_T_interrupt(void);
void _20ms_T_interrupt(void);
void _40ms_T_interrupt(void);
void _80ms_T_interrupt(void); 
void _60ms_T_interrupt(void); 
void _100ms_T_interrupt(void);
void _120ms_T_interrupt(void);
void _160ms_T_interrupt(void); 

void TIM2_10Ms_Interrupt_Init(void);    //初始化定时器中断

#endif
