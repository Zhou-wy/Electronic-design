#ifndef __MY_TIM_H
#define __MY_TIM_H 
#include "sys.h"

void Motor_init(void);               //����ʼ��
/******************************/
//�ڿ������ŷ�ֵ�û����Ͻ��е��� �ڷ�ֵ�Ļ��������ӻ��С�İٷֵ�
//���޷�
void Set_Motor1_Speed(float date);   //�������1������ ��ڲ������ٷֱ� -100.0 ~ 100.0
void Set_Motor2_Speed(float date);   //�ı����2������ ��ڲ������ٷֱ� -100.0 ~ 100.0
/*****************************/

/*****************************/
//���������ŷ�ֱֵ�ӵ���������� ��������µ���
//���޷�
void Set_Motor1_Speed_root(float date);   //�������1������ ��ڲ������ٷֱ� 0.0-100.0
void Set_Motor2_Speed_root(float date);   //�ı����2������ ��ڲ������ٷֱ� 0.0-100.0
/*****************************/
void Set_Duoji1(u8 date);            //���ö��1�ĳ�ʼ�Ƕ�
void Change_Duoji2(int date);        //�ı���1��ƫת�Ƕ�
void Set_Duoji2(u8 date);            //���ö��2�ĳ�ʼ�Ƕ�
void Change_Duoji1(int date);        //�ı���2��ƫת�Ƕ�

void Change_Acc(int date);           //�ı����Ż�׼ֵ ��λ1us
void Set_Acc(u16 date);              //�������Ż�׼ֵ ��λ1us

#endif
