#include "UdpTask.h"  

#include "stm32f4x7_eth_bsp.h"

#include "netconf.h"
#include "UDP_SERVER.h"

//OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
OS_STK Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE];
//OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];

//UDP服务器收发任务
void Task_UDP_Server(void *pdata)
{
	int tickCount= 0;
	__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */

	/* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
	LwIP_Init();

	/* UDP_server Init */
	UDP_server_init();
	//UDP_client_init();
	while(1)
	{  
		LocalTime += 2;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 5);//挂起5ms，以便其他线程运行
 
	}
}
//UDP服务器收发任务
#if 0
void Task_UDP_Client(void *pdata)
{
	__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
	/* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
	LwIP_Init();

	/* UDP_client Init */
	UDP_client_init();
	while(1)
	{  
		udp_send(udp_pcb,udp_p);//发送数据
		LocalTime += 10;
		LwIP_Periodic_Handle(LocalTime);		
		OSTimeDlyHMSM(0, 0, 0, 10);//挂起10ms，以便其他线程运行
	}
}

#endif 

