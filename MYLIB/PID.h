//ģ�黯λ��ʽPID
#ifndef _PID_H_
#define _PID_H_
#include <stdlib.h>
#include "stm32f10x_conf.h"

//����һ��PID�ṹ��
typedef struct _pid{
    float Set;                 //�����趨ֵ
    float Actual;              //����ʵ��ֵ
    float Kp,Ki,Kd;            //������������֡�΢��ϵ��
    float err;                 //����ƫ��ֵ
    float err_last;            //������һ��ƫ��ֵ
    float Sum_err;             //����ƫ��֮��   
    float Proportion;          //��������ı���ϵ��
    float Pout,Iout,Dout;      //������������
}PID;

PID*   PID_Init(float S,float Kp,float Ki,float Kd);    //��ʼ��һ��PID�ṹ�� ����һ��pid�ṹ��ָ��
void   PID_Set_K(PID* pid_x,float Kp,float Ki,float Kd);//�޸�һ��PID�ṹ���PID����
void   PID_Set_S(PID* pid_x,float  s);                  //�޸�һ��PID�ṹ����趨ֵ       
void   PID_Count(PID* pid_x,float Act);                 //����һ��PID���� PID�ṹ��ָ�룬��ǰʵ��ֵ 
float  PID_Proportion(PID *pid_x);                      //����pid�����ֵ
void   PID_Kill(PID *pid_x);                            //����һ��PID�ṹ��

void PID_Count1(PID *pid_x, float Act,float Isum);

void PID_Reset(PID *pid_x);
 
#endif
