#ifndef __Timer_h_
#define __Timer_h_



extern void TIM_Configuration(void);
void TIM2_NVIC_Configuration(void);


extern void EnableSystick(void);
extern void DisableSystick(void);
extern void IDWG_Init(void);

extern void TIMER_Init(u16 ms);
extern void TIM5_Int_Init(u16 arr,u16 psc);


 #endif


