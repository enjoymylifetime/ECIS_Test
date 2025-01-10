//###########################################################################
//DSP6713 定时器
// FILE:    CpuTimers.h
//

#ifndef CPU_TIMERS_H
#define CPU_TIMERS_H



typedef struct
{
	double SamplePeriod;					// Timer0 采样周期 单位:us
	u32 GenericCounter;				// Timer0  全局通用计数器 单位:ms
	u32 GetPositionCounter;				// 重新定位开始时的通用计数值
	u32 G04StartCounter;				// G04 开始时通用计数值
	u32 HardLimitStartCounter;			// 硬限位开始时通用计数值
	u32 SciBComCounter;	 
	u32 Z_LastInterpolationCounter;		//Z轴上次插补计数值，用于刚性攻牙
	double DeltaInterpolationTimer;		//unit:ms  CH0510
	u32 ORTM252Counter;				// 主轴通用定位用计数器
	u32 SpindleRealSpeedCounter;		// 用于计算主轴实际速度计数器
	u32 AutoToolLockCounter;			// 自动对刀锁定时计数器   CH0601
	u32 SPCStartCounter;				//SPC功能启动等待,防止启动时频繁加减速，造成震动
	u32 SPCRunFiltrateCounter;				//SPC功能运行过滤,防止运行时频繁加减速，造成震动
	u32 trackdeflectionCounter;			//运行结束轨迹偏移判断用计数器
	u32 ForwardFeedbackCompensateCounter;
	u32 ForwardFeedbackCompensateDeltaTimer;
}TIMER0;


//---------------------------------------------------------------------------
// Function prototypes and external definitions:
//

extern TIMER0 Timer0;	//定时器0 结构对象



void InitCpuTimers(void);
//void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period);
extern volatile struct CPUTIMER_REGS CpuTimer0Regs;

// Start Timer:
#define StartCpuTimer0()  CpuTimer0Regs.TCR.bit.TSS = 0

// Stop Timer:
#define StopCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
#define ReloadCpuTimer0() CpuTimer0Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
#define ReadCpuTimer0Counter() CpuTimer0Regs.TIM.all

// Read 32-Bit Period Value:
#define ReadCpuTimer0Period() CpuTimer0Regs.PRD.all


#endif  // end of DSP281x_CPU_TIMERS_H definition


//===========================================================================
// No more.
//===========================================================================
