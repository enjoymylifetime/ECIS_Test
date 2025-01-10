#include "led.h" 

#include "includes.h"


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;      //LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;      //LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOG时钟
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_14;              //LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;    //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;    //上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);   //初始化GPIO

}

//----------------------------------------------------------------
void  Led_S_LIG1(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	   else
	   	   GPIO_SetBits(GPIOC,GPIO_Pin_9);
	}

void  Led_S_LIG2(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	   else
	   	   GPIO_SetBits(GPIOA,GPIO_Pin_8);
	}

void  Led_S_LIG3(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	   else
	   	   GPIO_SetBits(GPIOC,GPIO_Pin_8);
	}

void  Led_S_LIG4(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	   else
	   	   GPIO_SetBits(GPIOA,GPIO_Pin_11);
	}

void  Led_S_LIG5(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	   else
	   	   GPIO_SetBits(GPIOA,GPIO_Pin_12);
	}

void  Led_S_LIG6(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	   else
	   	   GPIO_SetBits(GPIOC,GPIO_Pin_7);
	}

void  Led_S_LIG7(u8 Val)
	{
	   if(Val==0)
	          GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	   else
	   	   GPIO_SetBits(GPIOC,GPIO_Pin_6);
	}

void  Led_S_LIG8(u8 Val)
{
	if(Val==0)
	    GPIO_ResetBits(GPIOG,GPIO_Pin_8);
	else
		GPIO_SetBits(GPIOG,GPIO_Pin_8);
}


/***************************************************************************/
/*  Function name: Led_S_Bot()                                   */
/*  Argument: 0 off   1  ON    	                                 */
/*  Return value:	    ON  */
/*  Function: 控制轮廓灯                                   */
/***************************************************************************/
void  Led_S_Bot(u8 Val)
{
	if(Val==0)
	    GPIO_ResetBits(GPIOG,GPIO_Pin_7);
	else
		GPIO_SetBits(GPIOG,GPIO_Pin_7);
}


/***************************************************************************/
/*  Function name: Led_S_Coaxial()                                   */
/*  Argument: 0 off   1  ON    	                                 */
/*  Return value:	    ON  */
/*  Function: 同轴光输出                                   */
/***************************************************************************/
void  Led_S_Coaxial(u8 Val)
{
	if(Val==0)
		GPIO_ResetBits(GPIOG,GPIO_Pin_6);
	else
		GPIO_SetBits(GPIOG,GPIO_Pin_6);
}



/***************************************************************************/
/*  Function name: Led_S407()                                   */
/*  Argument: 1 ON   0  OFF    	                               */
/*  Return value:	    NO  */
/*  Function: 407芯片指示灯                           */
/***************************************************************************/
void  Led_S407(u8 Val)
{
	if(Val==0)
		GPIO_SetBits(GPIOG,GPIO_Pin_14);
	else
		GPIO_ResetBits(GPIOG,GPIO_Pin_14);
}


//------------------------------------------------------------------------------
void ExitGPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//注意要打开SYSCFG时钟配置外部中断连接至那个GPIO和该I/O口的那个引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;                                     //XR
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;                                        //YR  
	GPIO_Init(GPIOG, &GPIO_InitStructure);


	/*
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;                                        //YR  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;                                        //ZR
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;                                        //WR
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;                                        //INT
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	*/
}


//----------------------------------------------------------------------------
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	/*
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);      //ZR
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);      //INT
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource7);      //WR
	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	*/

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource13);      //D13  
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG,EXTI_PinSource12);      //G12  探针输入
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
}


//--------------------------------------------------------------------------
void ExitNVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/*

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;               //INT
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;               //YR
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;               //XR
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;               //ZR WR
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
	EXTI_ClearITPendingBit(EXTI_Line13);   //清空中断标志
	EXTI_ClearITPendingBit(EXTI_Line12);   //清空中断标志
	ExitGPIO_Config();
	EXTI_Configuration();
	ExitNVIC_Config();

	                                         //初始化中断
	//EXTI->IMR|=EXTI_Line0;  
	// EXTI->IMR&=~EXTI_Line2;  
	// EXTI->IMR&=~EXTI_Line3;  
	EXTI->IMR|=EXTI_Line12;          //探针输入
	EXTI->IMR|=EXTI_Line13;          //FPGA脉冲中断输入


	/*
	//-----使能串口1中断-----
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //先占优先级2位，从优先级2位
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//-----使能串口2中断-----
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//-----使能串口3中断-----
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//-----使能串口4中断-----
	NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/

}


u8  FuncGpioRead(void)
{
	return 0;
}


void  FuncGpioWrite(u8 Val)
{
}


void PBB(u8 Sign)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	if(Sign){
		GPIO_SetBits(GPIOG, GPIO_Pin_11);
	}
	else{ 
		GPIO_ResetBits(GPIOG, GPIO_Pin_11);
	}

} 

/***************************************************************************/
/*  Function name: WorkLedCon()                                   */
/*  Argument: 无           */
/*  Return value: 无*/
/*  Function:  主控制芯片工作指示灯，1秒闪烁一次           */
void WorkLedCon(void)
{
	static u16 LedCon;

	LedCon++;
	LedCon%=400;
	if(LedCon<=200)
		GPIO_SetBits(GPIOG,GPIO_Pin_14);
	else if(LedCon<400)
		GPIO_ResetBits(GPIOG,GPIO_Pin_14);
}





void TIM3_GPIO_Config(void)
{
	//PE 8 9 10 11 12 13 14输出
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);
}


//TIM1做PWM输出
u32 TimerPeriod;
void Tim3_Config(void)
{
	u32 ccr1,ccr2,ccr3,ccr4;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod = (SystemCoreClock / 20000 ) - 1;
	ccr1 = TIM3PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/2 = 50%
	ccr2 = TIM3PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/3 = 33%
	ccr3 = TIM3PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/4 = 25%
	ccr4 = TIM3PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/5 = 20%

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	//时基初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //死区控制用。
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器方向
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;   //Timer clock = sysclock /(TIM_Prescaler+1) = 168M
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_Period = TIM3PWMCYCLE - 1;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccr1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = ccr4;
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);

	TIM_Cmd(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
}




void TIM1_GPIO_Config(void)
{
	//PE 8 9 10 11 12 13 14输出
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM1);

}

//TIM1做PWM输出
void Tim1_Config(void)
{
	u32 TimerPeriod,ccr1,ccr2,ccr3,ccr4;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod =  (SystemCoreClock / 20000 ) - 1;
	ccr1 = TIM1PWMCYCLE / 10;  //占空比1/2 = 50%
	ccr2 = TIM1PWMCYCLE / 10;  // TimerPeriod / 100;  //占空比1/3 = 33%
	ccr3 = TIM1PWMCYCLE / 10;  // TimerPeriod / 100;  //占空比1/4 = 25%
	ccr4 = TIM1PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/5 = 20%

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//时基初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //死区控制用。
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器方向
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;   //Timer clock = sysclock /(TIM_Prescaler+1) = 168M
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_Period = TimerPeriod - 1;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccr1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM1,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = ccr4;
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);

	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}


//-------------------------------------------------------
void TIM8_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM8);
}

//------------------------------------------------------------------------
//TIM8做PWM输出
void Tim8_Config(void)
{
	u32 ccr2,ccr3;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TimerPeriod =  (SystemCoreClock / 20000 ) - 1;
	ccr2 = TIM8PWMCYCLE / 10;  //占空比1/2 = 50%
	ccr3 = TIM8PWMCYCLE / 10;  //  TimerPeriod / 100;  //占空比1/5 = 20%

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	//时基初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //死区控制用。
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器方向
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;   //Timer clock = sysclock /(TIM_Prescaler+1) = 168M
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInitStructure.TIM_Period = TIM8PWMCYCLE - 1;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC2Init(TIM8,&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM8,&TIM_OCInitStructure);

	TIM_Cmd(TIM8,ENABLE);
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
}


void LightInit(void)
{
	TIM3_GPIO_Config();
	Tim3_Config();
	TIM1_GPIO_Config();
	Tim1_Config();
	TIM8_GPIO_Config();
	Tim8_Config();	 
}

/*******************************************************************************
* Function Name  : LightCon
* Description    : 光源输出控制
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LightCon(void)
{
	/*
	u32 ccr1,ccr2,ccr3,ccr4;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	ccr4=(u32)((float)LightLevel.BrightLess[0]/(float)200.0*TIM3PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr4;
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);        //S_LIG1

	ccr1=(u32)((float)LightLevel.BrightLess[1]/(float)200.0*TIM1PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr1;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);        //S_LIG2

	ccr3=(u32)((float)LightLevel.BrightLess[2]/(float)200.0*TIM3PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);       //S_LIG3

	ccr4=(u32)((float)LightLevel.BrightLess[3]/(float)200.0*TIM1PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr4;
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);       //S_LIG4

	ccr2=(u32)((float)LightLevel.BrightLess[5]/(float)200.0*TIM3PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);       // S_LIG6

	ccr1=(u32)((float)LightLevel.BrightLess[6]/(float)200.0*TIM3PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr1;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);      // S_LIG7

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	ccr2=(u32)((float)LightLevel.BrightLess[4]/(float)200.0*TIM1PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);       //S_LIG5

	ccr3=(u32)((float)LightLevel.BrightLess[7]/(float)200.0*TIM1PWMCYCLE);
	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);       // S_LIG8

	ccr3=(u32)((float)LightLevel.OutlineLight/(float)200.0*TIM8PWMCYCLE);     //底光
	TIM_OCInitStructure.TIM_Pulse = ccr3;
	TIM_OC3Init(TIM8,&TIM_OCInitStructure);       //S_Bot

	ccr2=(u32)((float)LightLevel.CoaAxisLight/(float)200.0*TIM8PWMCYCLE);    //同轴光
	TIM_OCInitStructure.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM8,&TIM_OCInitStructure);       //S_Coa

	LightLevel.Renew=0;
	*/

}


/*******************************************************************************
* Function Name  : McuWorkLedInit
* Description    : CPU工作指示灯IO初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void McuWorkLedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : McuWorkLedCon
* Description    : CPU工作指示灯控制，5MS调度任务，200次翻转
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void  McuWorkLedCon(void)
{
	static u16 McuLedCnt=0;

	McuLedCnt++;
	if(McuLedCnt<200){
		GPIO_SetBits(GPIOE,GPIO_Pin_0);
	}
	else if(McuLedCnt<400){
		GPIO_ResetBits(GPIOE,GPIO_Pin_0);
	}
	else{
		McuLedCnt=0;
	}
}








