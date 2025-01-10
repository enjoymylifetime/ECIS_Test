#include "includes.h"
#define Testflag 1
#define WorkingFlag 1

u8  Brushless_motor_value = 0;
u8  Acceleration_DelayValue = 0;
u16 Centrifuge_speed = 0;
int MOTORA_ArrivalCount = 0;
int Position_ArrivalCount = 0;
int Position_ArrivalCount2 = 0;

const float Brushless_control_precision = 27.5;    //0-127 -> 0-4000 : 31.5;  0-127 -> 0-3000 : 23.6

u8 PulseBrake_flag=0;
u8 SpeedTime_flag=1;
u16 Overtime_counter=0;
u8 DetectStatus_flag=1;


void interrupt4(void)
{  
	//NCAreaPulseToServo();			  
}


/*******************************************************************************
* Function Name  : main_cycle
* Description    : Periodic complement function
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void main_cycle(void)
{
	//ReadScale();       //获取无刷电机编码器反馈


}



