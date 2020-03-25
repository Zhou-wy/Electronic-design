#ifndef __CMD_H_
#define __CMD_H_
#include "delay.h"
#include "Ultrasonic.h"
#include "PID.h"
#include "Control.h"


/*********************************************
time   : 悬停时间(S)
hight1 : 设定初始高度(m)
hight2 : 设定变化高度(m)
Pid_H  :传入高度pid结构体指针
*********************************************/
void Change_Hight(int time,int hight1,int hight2,PID* Pid_H);

#endif
