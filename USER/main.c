#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "arm_math.h" 

//++>ice
#include "UdpTask.h"
#include "app_cfg.h"
#include "Bsp_Global.h"

#include "UDPDataUnit.h"
#if !SYSTEM_SUPPORT_OS
	#include "UdpTask.h"  

	#include "stm32f4x7_eth_bsp.h"

	#include "netconf.h"
	#include "UDP_SERVER.h"

#endif 
/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			15 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
__align(8) OS_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *pdata);	 //任务函数

//RS485发送任务
//设置任务优先级
#define Send_TASK_PRIO       			11
//设置任务堆栈大小
#define Send_STK_SIZE  		    		0x200
//任务堆栈	
__align(8) OS_STK Send_TASK_STK[Send_STK_SIZE];
void send_task(void *pdata);  //任务函数

//RS485接收任务
//设置任务优先级
#define Receive_TASK_PRIO       			10 
//设置任务堆栈大小
#define Receive_STK_SIZE  		    		0x200
//任务堆栈	
__align(8) OS_STK Receive_TASK_STK[Receive_STK_SIZE];
void receive_task(void *pdata);  //任务函数
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			9 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		0x200
//任务堆栈	
__align(8) OS_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *pdata);  //任务函数



//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED1_STK_SIZE  			        0x400     //	64
//任务堆栈
__align(8) OS_STK LED1_TASK_STK[LED1_STK_SIZE];
void led1_task(void *pdata);   //任务函数

//task send data to pc
//__align(8) OS_STK Stk_Task_AutoDataSend[TASK_UDP_SREVER_STK_SIZE];
void autoDataSend_task(void *pdata);


int main(void)
{ 
	delay_init(168);		     //初始化延时函数
	//InitAllIo();
	delay_ms(1000);
	ParameterRecovery();
	USART1_Configuration(9600);        //SD卡
	USART2_Configuration(115200);    //485发送
	
	//TIM5_Int_Init(5-1,84-1);   	//(5 x 84) / 84M = 0.00001s.   5us定时
	OSInit();
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	//节拍计数器清0  
	OSTimeSet(0);
	OSStart();	
}


//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	INT8U	rev ;

	pdata = pdata; 
	OS_ENTER_CRITICAL();			    //进入临界区(无法被中断打断)
	OSTaskCreate(send_task, (void *)0, (OS_STK*)&Send_TASK_STK[Send_STK_SIZE-1], Send_TASK_PRIO);
	//OSTaskCreate(receive_task, (void *)0, (OS_STK*)&Receive_TASK_STK[Receive_STK_SIZE-1], Receive_TASK_PRIO);	
	OSTaskCreate(led0_task, (void *)0, (OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1], LED0_TASK_PRIO);		
	OSTaskCreate(led1_task, (void *)0, (OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1], LED1_TASK_PRIO);	 				   

//	//-->ice
//	rev = OSTaskCreate(Task_UDP_Server, (void *)0, &Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE-1], OS_USER_PRIO_GET(1));
	
	//rev = OSTaskCreate(autoDataSend_task,(void *)0, &Stk_Task_AutoDataSend[TASK_UDP_SREVER_STK_SIZE-1], OS_USER_PRIO_GET(8));
	OSTaskSuspend(START_TASK_PRIO);     //挂起起始任务.
	OS_EXIT_CRITICAL();				    //退出临界区(可以被中断打断)
} 


//发送任务

u8 examplestr[]="1a;";

void send_task(void *pdata)
{	
	while(1){

//---------------SD卡测试-----------------------------------------------
	  UsartData.TxBuffer1Num=strlen(examplestr);  	 
         memcpy(UsartData.TxBuffer1,examplestr,UsartData.TxBuffer1Num);
	  Usart1SendSubFunc(UsartData.TxBuffer1Num);

//----------------485测试--------------------------------------------------
	   Send485Data.Bit.Head=0xaa;
	   Send485Data.Bit.Id=0;
	   Send485Data.Bit.State1.bit.PowerOffTime=SysPara.PowerOffCnt;
	   Send485Data.Bit.SaveCntL=0x0;
	   Send485Data.Bit.SaveCntH=0x0;
	   Send485Data.Bit.Tail=0xbb;
	   
	   Usart2SendSubFunc(6);
    	   OSTimeDly(20);
	}
}


//RS485接收任务
void receive_task(void *pdata)
{	
	while(1)
	{
    	OSTimeDly(200);
	}
}

//LED0任务
void led0_task(void *pdata)
{	
	while(1)
	     {
		MainRun();
		OSTimeDly(1);
	     }
}


//LED1任务高等级任务
void led1_task(void *pdata)
{	
	while(1)
		{
		  FuncCommunication();
		  OSTimeDly(1);
	       }
}


