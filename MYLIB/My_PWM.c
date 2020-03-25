#include "My_PWM.h"

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_AFIO, ENABLE); 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	
/**********************������·PWM���*************************/
                                                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;         //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                              

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	    
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
    TIM_SetCompare1(TIM1,1000);  
    TIM_SetCompare2(TIM1,1000);  
    TIM_SetCompare3(TIM1,1400);  
    TIM_SetCompare4(TIM1,1560);  
        	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
   
}


void Motor_init(void)        //��ʼ��TIM1��ʱ�� ����4·50Hz PMW
{
    TIM1_PWM_Init(20000,71); //50HZ PWM
//    Set_Duoji1(90);          //���ö����ʼ�Ƕ�
//    Set_Duoji2(90);

		TIM_SetCompare3(TIM1,1400);				//�Ӳ���7.0%ռ�ձȶ��  
		TIM_SetCompare4(TIM1,1560);				//�Ӳ���7.8%ռ�ձȶ��
}
/****************************************************************************/   

static int Youmen_fazhi=0;         //���Ż�׼ֵ ��λ1Us


/*****************��Ҫ����****************/
//���������Ϊ20ms*0.06=1.2ms
void Set_Motor1_Speed(float date)  //�������1������
{
    if((date*6)+1200+Youmen_fazhi<1200)
        TIM_SetCompare1(TIM1,1200);    
    else if((date*6)+1200+Youmen_fazhi>1990)
        TIM_SetCompare1(TIM1,1990);  
    else 
        TIM_SetCompare1(TIM1,(int)(date*6)+1200+Youmen_fazhi);            
}

void Set_Motor2_Speed(float date)  //�������2������
{
    if((date*6)+1200+Youmen_fazhi<1200)
        TIM_SetCompare2(TIM1,1200);    
    else if((date*6)+1200+Youmen_fazhi>1990)
        TIM_SetCompare2(TIM1,1990);  
    else 
        TIM_SetCompare2(TIM1,(int)(date*6)+1200+Youmen_fazhi);            
}
/*******************************************/

void Change_Acc(int date)              //���ӻ��С���Ż�׼ֵ  ��λ1us
{
    Youmen_fazhi+=date; 
}

void Set_Acc(u16 date)                 //�������Ż�׼ֵ ��λ1us
{
    Youmen_fazhi=date;
}

/*************����������**************/
void Set_Motor1_Speed_root(float date)   //�������1������ ��ڲ������ٷֱ� 0-100
{
    if(date<0)
    {
        date=0;
    }
    if(date>=98)
    {
        date=98;
    }
    TIM_SetCompare1(TIM1,(u16)(date*10+1000));
    
}

void Set_Motor2_Speed_root(float date)   //�ı����2������ ��ڲ������ٷֱ� 0-100
{
    if(date<0)
    {
        date=0;
    }
    if(date>=98)
    {
        date=98;
    }
    TIM_SetCompare2(TIM1,(u16)(date*10+1000));
}

/***************************************************************************/

void Set_Duoji1(u8 date)         //���ö��1��ƫת�Ƕ�
{
    
    TIM_SetCompare3(TIM1,500+(u16)(date*2000.0/180.0)); 
}


void Change_Duoji1(int date)         //���ö��1��ƫת�Ƕ�
{
    
    TIM_SetCompare3(TIM1,(u16)(TIM1->CCR3+date)); 
}

void Set_Duoji2(u8 date)         //���ö��2��ƫת�Ƕ�
{
    TIM_SetCompare4(TIM1,500+(u16)(date*2000.0/180.0));
}

void Change_Duoji2(int date)         //���ö��2��ƫת�Ƕ�
{
    TIM_SetCompare4(TIM1,(u16)(TIM1->CCR3+date)); 
}



