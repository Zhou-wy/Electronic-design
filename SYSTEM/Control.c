#include "Control.h"
#include "stdio.h"
#include "math.h"

PID *Hight_Pid; 
PID *Speed_Pid; 
PID *Pose_Pid;   //�ظ˷���Ƕ�PID
PID *Turn_Pid;   //����PID
PID *Pose_W_Pid; //��̬���еĽ��ٶ�PID

float Filter_Turn(float w);                     //�����˲�����
u8  biao=0;


void Control_Init()
{
	/************�ȽϺ�***********/
//    Hight_Pid=PID_Init(0.5 ,12   ,0.3   ,0); 			//�߶Ȼ�
//    Speed_Pid=PID_Init(0   ,2    ,0      ,0); 		//�ٶȻ�
//    Turn_Pid= PID_Init(0   ,1.2   ,0.05   ,0);	//������    
//    Pose_Pid =PID_Init(0   ,0   ,0   ,0);				//��̬�⻷
//    Pose_W_Pid= PID_Init(0   ,2   ,0   ,0); 		 	//��̬�ڻ� 
	
//	����
//	   Hight_Pid=PID_Init(0.5 ,12   ,0.3   ,0); 			//�߶Ȼ�
//    Speed_Pid=PID_Init(0   ,2    ,0      ,0); 		//�ٶȻ�
//    Turn_Pid= PID_Init(0   ,1.2   ,0.05   ,0);	//������    
//    Pose_Pid =PID_Init(0   ,0.8   ,0.1  ,0);				//��̬�⻷
//    Pose_W_Pid= PID_Init(0   ,2   ,0   ,0); 		 	//��̬�ڻ� 
	
		
		Hight_Pid=PID_Init(0.5 ,15   ,0.25   ,0); 
    Speed_Pid=PID_Init(0   ,2   ,0      ,0); 
   // Turn_Pid= PID_Init(0   ,1.5   ,0.02 ,0.001); 
		Turn_Pid= PID_Init(0   ,1.0   ,0.01 ,0);
	
    Pose_Pid =PID_Init(0   ,10   ,0.5   ,0);
    Pose_W_Pid= PID_Init(0   ,2.6   ,0.001   ,0);
}

static float Speed_H,Speed_A,Speed;
void Speed_Measure()                            //�ٶȲ���(�ں��˲�)
{
    Speed_H=(float)(Hight.Now-Hight.Last);      
    Speed_A+=(Fly_Pose.Z_a-0.9999) *9.8 /1000 * Count_T;
    Speed=Speed_H*1+Speed_A*0.0; 

    if(Speed>80)
        Speed=80;
    if(Speed<-80)
        Speed=-80;
   
//    printf("%.3f,",Speed);
//    printf("%d\r\n",Hight.Now);
//    printf("%.3f,",Hight_Pid->Iout);
//  printf("W:%f\n\r",Fly_Pose.Z_a);      
}

/***********************************************************/
/********************    �ڻ�    ***************************/
/***********************************************************/

void Inner_PID_Count()//�ڻ� �ٶȻ�
{
    
//    if(abs(Hight.Now-500)<6)
//       Hight_Pid=PID_Init(0.5 ,10   ,0.3   ,1); 
    
    
     float Speed_Xianfu=Speed*0.02;
    
//     /****�ٶ������޷�****/   
//     if(Speed_Xianfu>8)
//         Speed_Xianfu=8;
//     if(Speed_Xianfu<-8)
//         Speed_Xianfu=-8;
//     /********************/
     
     PID_Set_S(Speed_Pid ,PID_Proportion(Hight_Pid)); 
		 PID_Count(Speed_Pid ,Speed_Xianfu);        
//     PID_Count(Speed_Pid ,0);        //�������ٶȻ�
}

static float Last_Speed_Out=0;    //��һ���ٶȻ������
void Inner_PID_Output()           //�ڻ� һ�����
{
   /****************��̬���޷�*****************/
    float Pose_Out=PID_Proportion(Pose_W_Pid);  
    if(Pose_Out>10)
        Pose_Out=10;
    if(Pose_Out<-10)
        Pose_Out=-10;  
//    printf("%.3f,",Pose_Out);
//    printf("%.3f\r\n",Fly_Pose.Y_angle-Fly_Pose_Begain.Y_angle);
    
//   printf("%.3f\n",Fly_Pose.Y_w);
    /**************�ٶȻ������޷�**************/   
    float Speed_Out=PID_Proportion(Speed_Pid);    
    /************����һֱ����***************/
        if(Speed_Out-Last_Speed_Out>1.5)
        {
            Speed_Out=Last_Speed_Out+1.5;   
        }
        if(Speed_Out-Last_Speed_Out<-1.5)
        {
            Speed_Out=Last_Speed_Out-1.5;   
        } 
    /****************************************/
        
/**********************************************/
              
    /****************�ٶȻ��޷�*****************/
    if( Speed_Out>60)
        Speed_Out=60;
    if( Speed_Out<0)
        Speed_Out=0;
    Last_Speed_Out=Speed_Out;
    /******************���޷�*******************/


    /*******************************************/ 
			Set_Motor1_Speed(Speed_Out-Pose_Out+60);  
      Set_Motor2_Speed(Speed_Out+Pose_Out+60); 
		/**************************************************/
//		if(biao == 0)
//		{
//    Set_Motor1_Speed(Speed_Out-Pose_Out);  
//    Set_Motor2_Speed(Speed_Out+Pose_Out); 
//		}
//		else if(biao == 1)
//		{
//		Set_Motor1_Speed((Speed_Out-Pose_Out)-5+20*(Hight_Pid->Set-Hight.Now/1000));  
//    Set_Motor2_Speed((Speed_Out+Pose_Out)-5+20*(Hight_Pid->Set-Hight.Now/1000));	
//		}
    
//    printf("%d\r\n",Hight.Now);
     
}
/********************************************************************/
/**************************  �߶Ȼ�     *****************************/
/********************************************************************/

extern float Pout;

void Outer_PID_Count()//�⻷ �߶Ȼ�
{
		if(biao == 0)
			PID_Count(Hight_Pid ,Hight.Now/1000.0);  //����λ��ΪM���м���
		if(biao == 1)
		{
			PID_Count1(Hight_Pid ,Hight.Now/1000.0,Pout);
		}
    /**********�������߶Ȼ��������޷�***********/    
    if( (Hight_Pid->Sum_err)>( (Hight_Sum_Max/(Hight_Pid->Ki))-1))
        Hight_Pid->Sum_err=(Hight_Sum_Max/(Hight_Pid->Ki))-1;
    if( (Hight_Pid->Sum_err)<-(Hight_Sum_Max/(Hight_Pid->Ki))+1 )
        Hight_Pid->Sum_err=-(Hight_Sum_Max/(Hight_Pid->Ki))+1;
  
		printf("%d\r\n",Hight.Now);
//		printf("%f\r\n",Fly_Pose.Y_angle);
		
//    printf("%.3f\r\n",PID_Proportion(Hight_Pid));

}

/*******************************************************************/
/************************  ��������PID   ***************************/
/*******************************************************************/

void Turn_Pid_Count()  //����PID���Ƽ���
{
    
    PID_Count(Turn_Pid ,Fly_Pose.Z_w*0.8);  //����ƫ
    
    /**********�������������������޷�***********/   
    if( (Turn_Pid->Sum_err)>( (Turn_Sum_Max/(Turn_Pid->Ki))-2))
        Turn_Pid->Sum_err=(Turn_Sum_Max/(Turn_Pid->Ki))-2;
    if( (Turn_Pid->Sum_err)<-(Turn_Sum_Max/(Turn_Pid->Ki))+2 )
        Turn_Pid->Sum_err=-(Turn_Sum_Max/(Turn_Pid->Ki))+2;
    /******************************************/
  
}


void Turn_Pid_Contorl() 
{
    float Pid_output=PID_Proportion(Turn_Pid);
    if(Pid_output>66)
        Pid_output=66;
    if(Pid_output<-66)
        Pid_output=-66;
   // printf("������:%f  \r\n" ,Pid_output); 
//    printf("%.3f," ,Fly_Pose.Z_w);  
//    printf("%.3f\n",Pid_output);  

//		printf("%.3f," ,Fly_Pose.Z_w);  
//    printf("%.3f," ,Pid_output);
//		printf("%d\r\n",Hight.Now);
		
    TIM_SetCompare3(TIM1,(u16)(1400.0-Pid_output)); 
    TIM_SetCompare4(TIM1,(u16)(1560.0-Pid_output));   
}


/**********************************************************************/
/*******************         ��̬             *************************/
/**********************************************************************/
void Pose_Pid_Count()           //��̬���⻷
{   
    float Real_angle=Fly_Pose.Y_angle-Fly_Pose_Begain.Y_angle;
    if(Real_angle<0.1&&Real_angle>-0.1)
        Real_angle=0;
    PID_Count(Pose_Pid , Real_angle*0.01);  
    /**************��������̬���������޷�***********/    
    if( (Pose_Pid->Sum_err)>( (Pose_Sum_Max/(Pose_Pid->Ki))))
        Pose_Pid->Sum_err=(Pose_Sum_Max/(Pose_Pid->Ki));
    if( (Pose_Pid->Sum_err)<-(Pose_Sum_Max/(Pose_Pid->Ki)) )
        Pose_Pid->Sum_err=-(Pose_Sum_Max/(Pose_Pid->Ki));
  
}

void Pose_W_Pid_Count()         //��̬���ڻ�
{
    float Pose_Out=PID_Proportion(Pose_Pid);  
//    if(Pose_Out>5)
//        Pose_Out=5;
//    if(Pose_Out<-5)
//        Pose_Out=-5;  

    //   PID_Set_S(Pose_W_Pid,0);
    PID_Set_S(Pose_W_Pid,Pose_Out);
    PID_Count(Pose_W_Pid,Fly_Pose.Y_w*0.03);
 //   printf("%.3f\r\n",Fly_Pose.Y_w);

}

/********************************************************/
void Reset_PID()
{
		PID_Reset(Hight_Pid);
		PID_Reset(Speed_Pid);
		PID_Reset(Pose_Pid);
		PID_Reset(Turn_Pid);
		PID_Reset(Pose_W_Pid);
}


/******************************************************************/   
#include "stdlib.h"
static float W_Y_History[3]={0,0,0};
float Filter_Turn(float w)                      //�������յĽ��ٶ�
{
    float return_W;
    W_Y_History[0]=W_Y_History[1];
    W_Y_History[1]=W_Y_History[2];
    W_Y_History[2]=w;
    if(abs((int)(W_Y_History[2] - W_Y_History[1]))<200)
        return_W = W_Y_History[2];
    else
    {
        if(abs((int)(W_Y_History[2] - W_Y_History[0]))<200)
            return_W=W_Y_History[2];
        else
            return_W=W_Y_History[0];
    }
    return return_W;
}


