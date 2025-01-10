/*
************************************************************************************************
主要的包含文件I

文 件: INCLUDES.C ucos包含文件
作 者: Jean J. Labrosse
************************************************************************************************
*/

#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ucos_ii.h"
#include "os_cpu.h"
#include "os_cfg.h"
#include "math.h"

#include <stm32f4xx.h>	    


#include "usart.h"
#include "..\app\common.h"


#include "..\app\int_code.h"
#include "..\app\Pro.h"
#include "..\app\Sci.h"
#include "..\app\CpuTimers.h"
#include "..\BSP\fsmc.h"
#include "..\app\AdcDac.h"
#include "..\APP\memory.h"
#include "..\LED\Led.h"
#include "..\app\Timer.h"
#include "..\app\IIC.h"

#include "..\app\AD5933.h"



#define  PI          3.1415926

#define  atandp   atan
#define  cosdp     cos
#define  sindp      sin
#define  sqrtdp    sqrt
#define  powdp    pow


#define   TEST
//#define    VMS

#endif































