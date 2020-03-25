#include "CMD.h"

/***********************************************
time   : 悬停时间(S)
hight1 : 设定初始高度(m)
hight2 : 设定变化高度(m)
Pid_H  :传入高度pid结构体指针
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
