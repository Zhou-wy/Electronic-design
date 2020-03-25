#ifndef __CONTROL_H_
#define __CONTROL_H_
#include "PID.h"
#include "Ultrasonic.h"
#include "6050_USART.h"
#include "My_PWM.h"
#include "led.h"
#define YOUMEN_MAX  (1.5)  //���ŵ����޷�
#define Hight_Sum_Max 40    //�߶Ȼ����޷����ֵ
#define Pose_Sum_Max  2   //��̬�����޷�
#define Turn_Sum_Max  30   //��ת�����޷�


#define Count_T   10
void Control_Init(void);
void Outer_PID_Count(void);    //�⻷ �߶Ȼ�����
void Inner_PID_Count(void);    //�ڻ� �ٶȻ�����
void Inner_PID_Output(void);   //�ڻ� һ��PID���
void Turn_Pid_Contorl(void);   //����pid���
void Turn_Pid_Count(void);     //����PID���Ƽ���
void Speed_Measure(void);      //�ٶȲ���(�ں��˲�)
void Pose_Pid_Count(void);     //��̬���⻷
void Pose_W_Pid_Count(void);   //��̬���ڻ�

void Reset_PID(void);

#endif
