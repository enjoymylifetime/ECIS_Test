#include "includes.h"


//vu16 AD_Value[N_TIME][M_CHANNEL];



/******************************************************************************

* *函数名:DAC_Ch1_Config
*功能:DAC1配置
*输入:None
*输出:None
*返回:None 
*******************************************************************************/ 
void DAC_Ch1_Config(void) 
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef   DAC_InitStructure; 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//打开GPIOA时 钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);//打开DCA时钟

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4; //DAC_OUT1=PA.4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN; //该脚为AN模式
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;  //不上拉不下拉

	GPIO_Init(GPIOA,&GPIO_InitStructure);//以参数初始化GPIOA 
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_Software;//软件触发
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//只电压输出
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_TriangleAmplitude_2047; //分辨力 
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Enable;//使能输出
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);//以参数初始化DAC1 
	DAC_Cmd(DAC_Channel_1,ENABLE);//使能DAC1通道 
	DAC_SetChannel1Data(DAC_Align_12b_R,0x0000);//写入初始值0
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);///软件触发转换
} 

/******************************************************************************
* *函数名:Dac1_Set
*功能:DAC数据写入
*输入:None
*输出:None
*返回:None 
******************************************************************************/

void Dac1_Set(u16 Dac_Data)
{ 
	DAC_SetChannel1Data(DAC_Align_12b_R,Dac_Data);        //写入数据
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);         //软件触发转换
} 


//-------------------------------------------------
void DacInit(void)
{
	DAC_Ch1_Config();
	Dac1_Set(2000);
}




/*定义ADC3的数据寄存器地址，DMA功能要用到外设的数据地址
 *ADC3的数据地址为外设基地址+偏移地址，基地址在RM0090 Reference
 *manual（参考手册）的地址映射表里，为0x40012200，ADC_DR
 *偏移地址为0x4C，故实际地址为0x40012200+0x4C = 0x4001224C */


#define  ADC1_DR_Address    ((uint32_t)0x4001204C)
#define  ADC2_DR_Address    ((uint32_t)0x4001214C)
#define  ADC3_DR_Address    ((uint32_t)0x4001224C)
u16      DCConvertedValue[10][5];


 
void DMA_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	/* DMA2 Stream0 channel0 configuration **************************************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 50;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	/* ADC Common Init **********************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	/* ADC3 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 5;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC3 regular channel12 configuration *************************************/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, ADC_SampleTime_3Cycles);
	/* Enable DMA request after last transfer (Single-ADC mode) */
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	/* Enable ADC3 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC3 */
	ADC_Cmd(ADC1, ENABLE);
	/* Start ADC3 Software Conversion */ 
	ADC_SoftwareStartConv(ADC1);   //如果不是外部触发则必须软件开始转换
}


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */




uint16_t ADC_Value[10][5];
#define ADC1_DR_ADDR  0x4001204C      //ADC1_DR 地址
static void Init_ADC_GPIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/**************************************************
	ADC1-8个通道  ADC2-8个通道
	ADC1_IN0~IN7--PA0~PA7
	ADC2_IN8~IN9--PB0~PB1
	ADC2_IN10~IN15--PC0~PC5
	*************************************************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;    //PC0~PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 //DMA2
 static void Init_DMA2_Channel0_Stream0(void)
 {
     DMA_InitTypeDef DMA_InitStructure;
     
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
     DMA_DeInit(DMA2_Stream0);
     
     DMA_InitStructure.DMA_Channel = DMA_Channel_0;
     DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDR;
     DMA_InitStructure.DMA_Memory0BaseAddr = (unsigned int)ADC_Value;
     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
     DMA_InitStructure.DMA_BufferSize = 50;
     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
     DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
     DMA_InitStructure.DMA_Priority = DMA_Priority_High;    
     DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
     DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
     DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
     DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
     DMA_Init(DMA2_Stream0, &DMA_InitStructure);
     DMA_Cmd(DMA2_Stream0, ENABLE);
 }
 
 void Init_ADC(void)
 {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	Init_ADC_GPIO();
	Init_DMA2_Channel0_Stream0();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit();
	//初始化ADC Common
	ADC_CommonInitStructure.ADC_Mode =ADC_Mode_Independent;   // ADC_DualMode_RegSimult;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_3;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 5;

	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 2, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 3, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 4, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 5, ADC_SampleTime_15Cycles);


	ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	ADC_DMACmd(ADC1, ENABLE);//使能ADC1_DMA

	ADC_Cmd(ADC1, ENABLE);  
	ADC_SoftwareStartConv(ADC1);   //如果不是外部触发则必须软件开始转换
}




