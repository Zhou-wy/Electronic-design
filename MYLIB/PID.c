#include "pid.h"


PID *PID_Init(float S, float Kp, float Ki, float Kd) //初始化一个PID结构体 返回一个pid结构体
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
    pid_x->Actual = Act; //更新实际值

    pid_x->err_last = pid_x->err;            //更新上一次偏差
    pid_x->err = pid_x->Set - pid_x->Actual; //更新当前偏差值
    pid_x->Pout = pid_x->Kp * pid_x->err;    //比例输出

    pid_x->Sum_err += pid_x->err;                               //更新历史偏差总和
    pid_x->Iout = (pid_x->Ki) * (pid_x->Sum_err);               //积分输出

    pid_x->Dout = (pid_x->Kd) * (pid_x->err - pid_x->err_last); //微分输出

    
    pid_x->Proportion = pid_x->Pout + pid_x->Iout + pid_x->Dout; //总输出
}

void PID_Count1(PID *pid_x, float Act,float Isum)
{
    pid_x->Actual = Act; //更新实际值

    pid_x->err_last = pid_x->err;            //更新上一次偏差
    pid_x->err = pid_x->Set - pid_x->Actual; //更新当前偏差值
    pid_x->Pout = pid_x->Kp * pid_x->err;    //比例输出

//    pid_x->Sum_err += pid_x->err;                               //更新历史偏差总和
    pid_x->Iout = Isum;               				//积分输出

    pid_x->Dout = (pid_x->Kd) * (pid_x->err - pid_x->err_last); //微分输出

    
    pid_x->Proportion = pid_x->Pout + pid_x->Iout + pid_x->Dout; //总输出
}

void PID_Set_K(PID *pid_x, float Kp, float Ki, float Kd) //修改一个PID结构体的参数
{
    pid_x->Kp = Kp;
    pid_x->Ki = Ki;
    pid_x->Kd = Kd;
}

void PID_Set_S(PID *pid_x, float s) //修改一个PID结构体的设定值
{
    pid_x->Set = s;
}

void PID_Reset(PID *pid_x)
{
		pid_x->Pout = 0;
		pid_x->Iout = 0;
		pid_x->Dout = 0;
}
