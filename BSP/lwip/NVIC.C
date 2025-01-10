/***********************************************************************
文件名称：NVIC.C
功    能：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
#include "NVIC.h"
#include "misc.h"
void ETH_NVIC_Configuration(void)
{
	
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 

	/* Enable the Ethernet global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);   	

}
