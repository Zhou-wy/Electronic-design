#ifndef __MY_TIM_H
#define __MY_TIM_H 
#include "sys.h"

void Motor_init(void);               //马达初始化
/******************************/
//在考虑油门阀值得基础上进行调节 在阀值的基础上增加或减小的百分点
//有限幅
void Set_Motor1_Speed(float date);   //设置马达1的速率 入口参数：百分比 -100.0 ~ 100.0
void Set_Motor2_Speed(float date);   //改变马达2的速率 入口参数：百分比 -100.0 ~ 100.0
/*****************************/

/*****************************/
//不考虑油门阀值直接调节马达速率 紧急情况下调用
//有限幅
void Set_Motor1_Speed_root(float date);   //设置马达1的速率 入口参数：百分比 0.0-100.0
void Set_Motor2_Speed_root(float date);   //改变马达2的速率 入口参数：百分比 0.0-100.0
/*****************************/
void Set_Duoji1(u8 date);            //设置舵机1的初始角度
void Change_Duoji2(int date);        //改变舵机1的偏转角度
void Set_Duoji2(u8 date);            //设置舵机2的初始角度
void Change_Duoji1(int date);        //改变舵机2的偏转角度

void Change_Acc(int date);           //改变油门基准值 单位1us
void Set_Acc(u16 date);              //设置油门基准值 单位1us

#endif
