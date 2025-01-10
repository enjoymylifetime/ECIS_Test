#include "includes.h"


/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : Configures the TIMER channels for encoder mode.
* Input          : None
* Output         : None						 
* Return         : None

*******************************************************************************/
void TIM_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure; 

//------------Y轴TIM2------------------------------------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//GPIO_StructInit(&GPIO_InitStructure);
	/* Configure PA.00,01 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);

	/* Enable the TIM1 Update Interrupt */
	//NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);

	/* Timer configuration in Encoder mode */
	//TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 4;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	// Clear all pending interrupts
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE); 

}

void TIM_Configuration2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//GPIO_StructInit(&GPIO_InitStructure);
	/* Configure PA.00,01 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 8-1; // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel= TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity= TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection= TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler= TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_Cmd(TIM2, ENABLE); 

	TIM_ITConfig(TIM2, TIM_IT_Update|TIM_IT_CC1, ENABLE);

    //TIM2->CNT = 0;
	

}


void TIM2_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  			//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  		       //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  							//初始化NVIC寄存器
}



/************************************************************************************	
函数名称：void TIMER_Init(u16 ms)
函数功能：通用定时器3中断初始化
入口参数：ms：自动重装值。
返回参数：无
特别说明：时钟选择为APB1的2倍，而APB1为36M
************************************************************************************/  
void TIMER_Init(u16 ms)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 		//时钟使能
	
	//=====定时器TIM3初始化=====
	TIM_TimeBaseStructure.TIM_Period = (ms-1)*10; 				      //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = 16800-1; 				      //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	             //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	      //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 			       //根据指定的参数初始化TIMx的时间基数单位
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 					       //使能指定的TIM3中断,允许更新中断

	//=====中断优先级NVIC设置=====
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;  			//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  	       //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  		       //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  							//初始化NVIC寄存器
	TIM_Cmd(TIM6, ENABLE);  									//使能TIMx					 
}


//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//TIM3_Int_Init(5000-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms     

//------------使能定时中断-----------------------
void EnableSystick(void)
{
	SysTick->CTRL  |=SysTick_CTRL_TICKINT_Msk;
}

//------------禁止定时中断-----------------------
void DisableSystick(void)
{
	SysTick->CTRL  &=~SysTick_CTRL_TICKINT_Msk;
}

//------------------------------------------------------------
//-------初始化看门狗----------------------------------
void IDWG_Init(void)
{
	// IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);    //使能写入PR和RLR
	// IWDG_SetPrescaler(IWDG_Prescaler_256);                   //写入PR预分频值，复位时间约26秒
	// IWDG_SetReload(0xfff);      //写入RLR
	//IWDG_Enable();      //KR写入0xCCCC
}






