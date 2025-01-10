/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "includes.h"
#include "stm32f4x7_eth.h"
#include "netconf.h"

extern void USART1_IRG_Handler(void);   
extern void USART2_IRG_Handler(void);   
extern void USART3_IRG_Handler(void);  
extern void UART4_IRG_Handler(void); 	
extern void interrupt4(void);
extern void TIM2_IRQHandler(void);


uint32_t Freq_InputCapture=0;


//extern void MoveConRun(void);
#if !SYSTEM_SUPPORT_OS
void SysTick_Handler(void)
     {
       //MoveConRun();
     }

#endif 

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
	//#if SYSTEM_SUPPORT_OS
		//OSIntEnter();
	//#endif

	//中断处理函数
  	USART1_IRG_Handler();

	//#if SYSTEM_SUPPORT_OS
		//OSIntExit();
	//#endif
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
	{
	  USART2_IRG_Handler();
	}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
}


/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
}




 
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET)   //E6  Z  轴零位中断
	{
		EXTI_ClearITPendingBit(EXTI_Line9);   //清楚外部中断
	}
}


 
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)   //E6  Z  轴零位中断
	{
		EXTI_ClearITPendingBit(EXTI_Line13);   //清楚外部中断
		interrupt4();
	}
	else if(EXTI_GetITStatus(EXTI_Line12)!=RESET)   //G12  探针触发
	{
		EXTI_ClearITPendingBit(EXTI_Line12);   //清楚外部中断
	}
}

void TIM2_IRQHandler(void)
{
	
	static uint32_t capture_value1 = 0, capture_value2 = 0;
	static uint16_t flag_capture = 0;
	static uint32_t capture = 0;

	//OSIntEnter();

	if(TIM_GetITStatus(TIM2,TIM_IT_CC1) != RESET){
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
		
		if(flag_capture == 0){
			flag_capture = 1;
			capture_value1 = (uint32_t)(TIM2->CCR1);
		}
		else if(flag_capture == 1){
			flag_capture = 0;
			capture_value2 = (uint32_t)(TIM2->CCR1);
		}

		if(capture_value2 > capture_value1)
			capture = (capture_value2 - capture_value1);
		else if(capture_value2 < capture_value1)
			capture = ((0xffffffff - capture_value1) + capture_value2);
		else
			capture = 0;

		Freq_InputCapture = (uint32_t)SystemCoreClock/2/capture;

		
	}
	
	//OSIntExit();
	
}


/************************************************************************************	
函数名称：void TIM5_IRQHandler(void)
函数功能：定时器5中断服务函数  5US一个中断
入口参数：无
返回参数：无
************************************************************************************/ 
void TIM5_IRQHandler(void)   
	{   

	   if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//检查TIMx更新中断发生与否
		{
		   TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  	//清除TIMx更新中断标志 
		   
                 /*
		   i++;
		   if(i>=200)
		   	{
		   	  i=0;
		   	      //系统1MS定时
		   	}
		   	*/
		}
	}



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @brief  This function handles ethernet DMA interrupt request.
  * @param  None
  * @retval None
  */
void ETH_IRQHandler(void)
{
	INT8U err;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // 关中断                               
    OSIntNesting++;	   		//中断嵌套层数，通知ucos
    OS_EXIT_CRITICAL();	   	//开中断
	/* Handles all the received frames */
    /* check if any packet received */
    while(ETH_CheckFrameReceived())
    { 
      /* process received ethernet packet */
      LwIP_Pkt_Handle();
    }
	/* Clear the Eth DMA Rx IT pending bits */
	ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
	ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
	OSIntExit();//中断退出，通知ucos，（该句必须加）	
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
