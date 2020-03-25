#ifndef __CONTROL_H_
#define __CONTROL_H_
#include "PID.h"
#include "Ultrasonic.h"
#include "6050_USART.h"
#include "My_PWM.h"
#include "led.h"
#define YOUMEN_MAX  (1.5)  //油门单次限幅
#define Hight_Sum_Max 40    //高度积分限幅最大值
#define Pose_Sum_Max  2   //姿态积分限幅
#define Turn_Sum_Max  30   //旋转积分限幅


#define Count_T   10
void Control_Init(void);
void Outer_PID_Count(void);    //外环 高度环运算
void Inner_PID_Count(void);    //内环 速度环运算
void Inner_PID_Output(void);   //内环 一次PID输出
void Turn_Pid_Contorl(void);   //自旋pid输出
void Turn_Pid_Count(void);     //自旋PID控制计算
void Speed_Measure(void);      //速度测量(融合滤波)
void Pose_Pid_Count(void);     //姿态环外环
void Pose_W_Pid_Count(void);   //姿态环内环

void Reset_PID(void);

#endif
