#ifndef __CMD_H_
#define __CMD_H_
#include "delay.h"
#include "Ultrasonic.h"
#include "PID.h"
#include "Control.h"


/*********************************************
time   : ��ͣʱ��(S)
hight1 : �趨��ʼ�߶�(m)
hight2 : �趨�仯�߶�(m)
Pid_H  :����߶�pid�ṹ��ָ��
*********************************************/
void Change_Hight(int time,int hight1,int hight2,PID* Pid_H);

#endif
