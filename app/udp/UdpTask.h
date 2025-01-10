/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#ifndef _APP_UDP_TASK_H_
#define _APP_UDP_TASK_H_

#include "ucos_ii.h"


#define TASK_UDP_SREVER_STK_SIZE	3000
//#define TASK_UDP_CLIENT_STK_SIZE	2000

extern OS_STK Stk_Task_UDP_Server[TASK_UDP_SREVER_STK_SIZE];
//extern OS_STK Stk_Task_UDP_Client[TASK_UDP_CLIENT_STK_SIZE];

void Task_UDP_Server(void *pdata);
//void Task_UDP_Client(void *pdata);

#endif
