#include "CMD.h"

/***********************************************
time   : ��ͣʱ��(S)
hight1 : �趨��ʼ�߶�(m)
hight2 : �趨�仯�߶�(m)
Pid_H  :����߶�pid�ṹ��ָ��
**********************************************/
void Change_Hight(int time,int hight1,int hight2,PID* Pid_H)
{
	PID_Set_S(Pid_H,hight1);
	if (Hight.Now<hight1+0.03&&Hight.Now>hight1-0.03)
	{	
		delay_s(time);
	}
	PID_Set_S(Pid_H,hight2);
	if (Hight.Now<hight2+30&&Hight.Now>hight2-30)
	{	
		delay_s(time);
	}
	
	PID_Set_S(Pid_H,hight1);
	if (Hight.Now<hight1+30&&Hight.Now>hight1-30)
	{	
		delay_s(time);
	}
}
