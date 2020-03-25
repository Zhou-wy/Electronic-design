#ifndef __6050_H
#define __6050_H
#include "stm32f10x.h" 
#include "string.h"
#include "delay.h"

typedef struct _pose{
    float X_a;                  //X轴加速度
    float Y_a;                  //Y轴加速度
    float Z_a;                  //Z轴加速度
    float X_w;                  //X轴角速度
    float Y_w;                  //Y轴角速度
    float Z_w;                  //Z轴角速度
    float X_angle;              //X轴滚转角
    float Y_angle;              //Y轴俯仰角
    float Z_angle;              //Z轴偏航角 (不准确量)
    float T;                    //温度
}POSE; 

extern POSE Fly_Pose;              //飞行过程实施姿态
extern POSE Fly_Pose_Begain;       //启动姿态

void USART2_6050_init(void);   //初始化 配置USART2 （用于接收MPU6050数据）占用串口2（PA2,PA3）
void Un_Pack_6050(void);       //解析6050数据包

#endif
