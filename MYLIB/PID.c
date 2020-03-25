#include "pid.h"


PID *PID_Init(float S, float Kp, float Ki, float Kd) //��ʼ��һ��PID�ṹ�� ����һ��pid�ṹ��
{
    PID *pid_x = malloc(sizeof(PID));
    pid_x->Set = S;
    pid_x->Kp = Kp;
    pid_x->Ki = Ki;
    pid_x->Kd = Kd;
    pid_x->err_last = 0;
    pid_x->Sum_err = 0;
    pid_x->Proportion = 0;
    pid_x->Pout = 0;
    pid_x->Iout = 0;
    pid_x->Dout = 0;
    return pid_x;
}

void PID_Kill(PID *pid_x)
{
    free(pid_x);
}

float PID_Proportion(PID *pid_x)
{
    return pid_x->Proportion;
}

void PID_Count(PID *pid_x, float Act)
{
    pid_x->Actual = Act; //����ʵ��ֵ

    pid_x->err_last = pid_x->err;            //������һ��ƫ��
    pid_x->err = pid_x->Set - pid_x->Actual; //���µ�ǰƫ��ֵ
    pid_x->Pout = pid_x->Kp * pid_x->err;    //�������

    pid_x->Sum_err += pid_x->err;                               //������ʷƫ���ܺ�
    pid_x->Iout = (pid_x->Ki) * (pid_x->Sum_err);               //�������

    pid_x->Dout = (pid_x->Kd) * (pid_x->err - pid_x->err_last); //΢�����

    
    pid_x->Proportion = pid_x->Pout + pid_x->Iout + pid_x->Dout; //�����
}

void PID_Count1(PID *pid_x, float Act,float Isum)
{
    pid_x->Actual = Act; //����ʵ��ֵ

    pid_x->err_last = pid_x->err;            //������һ��ƫ��
    pid_x->err = pid_x->Set - pid_x->Actual; //���µ�ǰƫ��ֵ
    pid_x->Pout = pid_x->Kp * pid_x->err;    //�������

//    pid_x->Sum_err += pid_x->err;                               //������ʷƫ���ܺ�
    pid_x->Iout = Isum;               				//�������

    pid_x->Dout = (pid_x->Kd) * (pid_x->err - pid_x->err_last); //΢�����

    
    pid_x->Proportion = pid_x->Pout + pid_x->Iout + pid_x->Dout; //�����
}

void PID_Set_K(PID *pid_x, float Kp, float Ki, float Kd) //�޸�һ��PID�ṹ��Ĳ���
{
    pid_x->Kp = Kp;
    pid_x->Ki = Ki;
    pid_x->Kd = Kd;
}

void PID_Set_S(PID *pid_x, float s) //�޸�һ��PID�ṹ����趨ֵ
{
    pid_x->Set = s;
}

void PID_Reset(PID *pid_x)
{
		pid_x->Pout = 0;
		pid_x->Iout = 0;
		pid_x->Dout = 0;
}
