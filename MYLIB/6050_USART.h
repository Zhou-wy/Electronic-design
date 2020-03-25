#ifndef __6050_H
#define __6050_H
#include "stm32f10x.h" 
#include "string.h"
#include "delay.h"

typedef struct _pose{
    float X_a;                  //X����ٶ�
    float Y_a;                  //Y����ٶ�
    float Z_a;                  //Z����ٶ�
    float X_w;                  //X����ٶ�
    float Y_w;                  //Y����ٶ�
    float Z_w;                  //Z����ٶ�
    float X_angle;              //X���ת��
    float Y_angle;              //Y�ḩ����
    float Z_angle;              //Z��ƫ���� (��׼ȷ��)
    float T;                    //�¶�
}POSE; 

extern POSE Fly_Pose;              //���й���ʵʩ��̬
extern POSE Fly_Pose_Begain;       //������̬

void USART2_6050_init(void);   //��ʼ�� ����USART2 �����ڽ���MPU6050���ݣ�ռ�ô���2��PA2,PA3��
void Un_Pack_6050(void);       //����6050���ݰ�

#endif
