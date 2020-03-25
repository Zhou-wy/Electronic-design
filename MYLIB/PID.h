//模块化位置式PID
#ifndef _PID_H_
#define _PID_H_
#include <stdlib.h>
#include "stm32f10x_conf.h"

//定义一个PID结构体
typedef struct _pid{
    float Set;                 //定义设定值
    float Actual;              //定义实际值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float err;                 //定义偏差值
    float err_last;            //定义上一个偏差值
    float Sum_err;             //定义偏差之和   
    float Proportion;          //定义输出的比例系数
    float Pout,Iout,Dout;      //定义各分量输出
}PID;

PID*   PID_Init(float S,float Kp,float Ki,float Kd);    //初始化一个PID结构体 返回一个pid结构体指针
void   PID_Set_K(PID* pid_x,float Kp,float Ki,float Kd);//修改一个PID结构体的PID参数
void   PID_Set_S(PID* pid_x,float  s);                  //修改一个PID结构体的设定值       
void   PID_Count(PID* pid_x,float Act);                 //进行一次PID计算 PID结构体指针，当前实际值 
float  PID_Proportion(PID *pid_x);                      //返回pid的输出值
void   PID_Kill(PID *pid_x);                            //消灭一个PID结构体

void PID_Count1(PID *pid_x, float Act,float Isum);

void PID_Reset(PID *pid_x);
 
#endif
