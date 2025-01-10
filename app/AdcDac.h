#ifndef ADCDAC_H
#define  ADCCAC_H

#define N_TIME             50 //每通道采50次
#define M_CHANNEL      5 //为5个通道

extern   u16      DCConvertedValue[10][5];

extern u16 ADC_Value[10][5];

extern void DAC_Ch1_Config(void);
extern void Dac1_Set(u16 Dac_Data); 
//extern vu16 AD_Value[N_TIME][M_CHANNEL];
extern void Adc3_Init(void);
extern void DacInit(void);

extern void Init_ADC(void);


#endif
