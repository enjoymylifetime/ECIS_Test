#ifndef _AD5933_H_
#define _AD5933_H_

#include "sys.h"


enum Ad5933channel{Channel1,Channel2,Channel3,Channel4,Channel5,Channel6,Channel7,
                                        Channel8,Channel9,Channel10,Channel11,Channel12,Channel13,Channel14};

enum Ad5933DataName {R_Impedance,realData,ImageData};


#define Ad5933SCLPin_1             GPIO_Pin_15
#define Ad5933SDAPin_1            GPIO_Pin_6
#define Ad5933IICSclIO_1          GPIOD
#define Ad5933IICSdaIO_1         GPIOC

//IO操作函数	 
#define Ad5933SCL_1                 PDout(15) //SCL
#define Ad5933SDA_1                PCout(6) //SDA
#define Ad5933READ_SDA_1      PCin(6)  //输入SDA




#define Ad5933SCLPin_2             GPIO_Pin_13
#define Ad5933SDAPin_2            GPIO_Pin_14
#define Ad5933IICSclIO_2          GPIOD
#define Ad5933IICSdaIO_2         GPIOD

//IO操作函数	 
#define Ad5933SCL_2                 PDout(13) //SCL
#define Ad5933SDA_2                PDout(14) //SDA
#define Ad5933READ_SDA_2      PDin(14)  //输入SDA



#define Ad5933SCLPin_3             GPIO_Pin_11
#define Ad5933SDAPin_3            GPIO_Pin_12
#define Ad5933IICSclIO_3          GPIOD
#define Ad5933IICSdaIO_3         GPIOD

//IO操作函数	 
#define Ad5933SCL_3                 PDout(11) //SCL
#define Ad5933SDA_3                PDout(12) //SDA
#define Ad5933READ_SDA_3      PDin(12)  //输入SDA


#define Ad5933SCLPin_4             GPIO_Pin_9
#define Ad5933SDAPin_4            GPIO_Pin_10
#define Ad5933IICSclIO_4          GPIOD
#define Ad5933IICSdaIO_4         GPIOD

//IO操作函数	 
#define Ad5933SCL_4                 PDout(9) //SCL
#define Ad5933SDA_4                PDout(10) //SDA
#define Ad5933READ_SDA_4      PDin(10)  //输入SDA


#define Ad5933SCLPin_5             GPIO_Pin_11
#define Ad5933SDAPin_5            GPIO_Pin_12
#define Ad5933IICSclIO_5          GPIOE
#define Ad5933IICSdaIO_5         GPIOE

//IO操作函数	 
#define Ad5933SCL_5                 PEout(11) //SCL
#define Ad5933SDA_5                PEout(12) //SDA
#define Ad5933READ_SDA_5      PEin(12)  //输入SDA


#define Ad5933SCLPin_6             GPIO_Pin_8
#define Ad5933SDAPin_6            GPIO_Pin_15
#define Ad5933IICSclIO_6          GPIOD
#define Ad5933IICSdaIO_6         GPIOB

//IO操作函数	 
#define Ad5933SCL_6                 PDout(8) //SCL
#define Ad5933SDA_6                PBout(15) //SDA
#define Ad5933READ_SDA_6      PBin(15)  //输入SDA


#define Ad5933SCLPin_7             GPIO_Pin_14
#define Ad5933SDAPin_7            GPIO_Pin_13
#define Ad5933IICSclIO_7          GPIOB
#define Ad5933IICSdaIO_7         GPIOB

//IO操作函数	 
#define Ad5933SCL_7                 PBout(14) //SCL
#define Ad5933SDA_7                PBout(13) //SDA
#define Ad5933READ_SDA_7      PBin(13)  //输入SDA


#define Ad5933SCLPin_8             GPIO_Pin_12
#define Ad5933SDAPin_8            GPIO_Pin_11
#define Ad5933IICSclIO_8          GPIOB
#define Ad5933IICSdaIO_8         GPIOB

//IO操作函数	 
#define Ad5933SCL_8                 PBout(12) //SCL
#define Ad5933SDA_8                PBout(11) //SDA
#define Ad5933READ_SDA_8      PBin(11)  //输入SDA


#define Ad5933SCLPin_9             GPIO_Pin_10
#define Ad5933SDAPin_9            GPIO_Pin_15
#define Ad5933IICSclIO_9          GPIOB
#define Ad5933IICSdaIO_9         GPIOE

//IO操作函数	 
#define Ad5933SCL_9                 PBout(10) //SCL
#define Ad5933SDA_9                PEout(15) //SDA
#define Ad5933READ_SDA_9      PEin(15)  //输入SDA



#define Ad5933SCLPin_10             GPIO_Pin_10
#define Ad5933SDAPin_10            GPIO_Pin_14
#define Ad5933IICSclIO_10          GPIOB
#define Ad5933IICSdaIO_10         GPIOB

//IO操作函数	 
#define Ad5933SCL_10                 PEout(14) //SCL
#define Ad5933SDA_10                PEout(13) //SDA
#define Ad5933READ_SDA_10      PEin(13)  //输入SDA


#define Ad5933SCLPin_11             GPIO_Pin_10
#define Ad5933SDAPin_11            GPIO_Pin_9
#define Ad5933IICSclIO_11          GPIOE
#define Ad5933IICSdaIO_11         GPIOE

//IO操作函数	 
#define Ad5933SCL_11                 PEout(10) //SCL
#define Ad5933SDA_11                PEout(9) //SDA
#define Ad5933READ_SDA_11      PEin(9)  //输入SDA


#define Ad5933SCLPin_12             GPIO_Pin_1
#define Ad5933SDAPin_12            GPIO_Pin_0
#define Ad5933IICSclIO_12          GPIOB
#define Ad5933IICSdaIO_12         GPIOB

//IO操作函数	 
#define Ad5933SCL_12                 PBout(1) //SCL
#define Ad5933SDA_12                PBout(0) //SDA
#define Ad5933READ_SDA_12      PBin(0)  //输入SDA

#define Ad5933SCLPin_13             GPIO_Pin_11
#define Ad5933SDAPin_13            GPIO_Pin_12
#define Ad5933IICSclIO_13          GPIOD
#define Ad5933IICSdaIO_13         GPIOD

//IO操作函数	 
#define Ad5933SCL_13                 PDout(11) //SCL
#define Ad5933SDA_13                PDout(12) //SDA
#define Ad5933READ_SDA_13      PDin(12)  //输入SDA


#define Ad5933SCLPin_14             GPIO_Pin_13
#define Ad5933SDAPin_14            GPIO_Pin_14
#define Ad5933IICSclIO_14          GPIOD
#define Ad5933IICSdaIO_14         GPIOD

//IO操作函数	 
#define Ad5933SCL_14                 PDout(13) //SCL
#define Ad5933SDA_14                PDout(14) //SDA
#define Ad5933READ_SDA_14      PDin(14)  //输入SDA




#define	AD5933_MCLK_USE_OUT	0	//0：内部时钟(16.776MHz)  1：外部时钟


//注意：
//AD5933测量较小电阻时，自身驱动能力不足，需要使用外部运放电路增强驱动能力，从而测量小于5.1K的小电阻
//测量大于或小于5.1K的电阻时，需要切换下面宏定义，且更改模块上跳线帽位置
		//#define _DEF_RSBIGGER5K		1		//接法1，测量大于5.1K( 5.1K-10M)电阻时,用跳线帽将模块上排针P6的1、2连接，P6的3,4断开，P5的1,2断开；
	#define _DEF_RSBIGGER5K		0		//接法2，测量小于5.1K(100R-5.1K)电阻时,用跳线帽将模块上排针P6的1、2断开，P6的3,4连接，P5的1,2连接；

#if _DEF_RSBIGGER5K == 1
#define REG_MIN	5100
#define REG_MAX	6000000
#define AD5933_Correction 101615461
#elif DEF_RSBIGGER5K == 0
#define REG_MIN	100
#define REG_MAX	8000
#define AD5933_Correction   957157       //6071526           //986558
#endif


#define uint unsigned int

//IO方向设置
//#define SDA_IN()  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=8<<16;}
//#define SDA_OUT() {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=3<<16;}


#define AD5933_SYS_Init					(1)<<12
#define AD5933_Begin_Fre_Scan		       (2)<<12
#define AD5933_Fre_UP					(3)<<12
#define AD5933_Fre_Rep					(4)<<12
#define AD5933_Get_Temp				(9)<<12
#define AD5933_Sleep					(10)<<12
#define AD5933_Standby					(11)<<12

#define AD5933_OUTPUT_2V				(0)<<9
#define AD5933_OUTPUT_1V				(3)<<9
#define AD5933_OUTPUT_400mV			(2)<<9
#define AD5933_OUTPUT_200mV			(1)<<9

#define AD5933_Gain_1					(1)<<8
#define AD5933_Gain_5					(0)<<8

#define AD5933_IN_MCLK					(0)<<3
#define AD5933_OUT_MCLK				(1)<<3

#define AD5933_Reset					(1)<<4

//定义函数
void Ini_I2c(void);
void SDA_1(void);
void SDA_0 (void);
void SCL_1(void);
void SCL_0 (void);
void GetACK(u8 GroupNo);
void SendNACK(u8 GroupNo);
void START(u8 GroupNo);
void STOP(u8 GroupNo);
void SendByte(u8 txd,u8 GroupNo);	// 发送一个字节数据子函数
u8 ReadByte(u8 GroupNo);  //读一个字节数据
void Write_Byte(char nAddr,uint nValue,u8 GroupNo);
void SetPointer(char nAddr,u8 GroupNo);
int Rece_Byte(char nAddr,u8 GroupNo);

void Delay_ms(unsigned long nValue);
float Scale_imp (u8 *SValue,u8 *IValue,u8 *NValue,u8 *CValue,u8 GroupNo);
u16 AD5933_Tempter(u8 GroupNo);
float Get_resistance(u16 num);
float AD5933_Sweep (float Fre_Begin,float Fre_UP,u16 UP_Num,u16 OUTPUT_Vatage,u16 Gain,u16 SWeep_Rep,u8 GroupNo);
float DA5933_Get_Rs(void);
float DA5933_Get_Cap(float Fre);
float DA5933_Get_L(float Fre);

float DA5933_Get_RsRealImage(float *R_Impedance, float *realData, float *imageData,u8 GroupNo);


extern float R_Impedance1;
extern float realData1;
extern float imageData1;	

extern float R_Impedance2;
extern float realData2;
extern float imageData2;	


typedef struct
	{
	   u8 CollectingMode;         //0 巡回采集模式   1  指定通道采集模式
	   u8 SingleModeChanle;    //指定通道模式下时的通道值
	   u8 MultiModeChanle;       //
	   u8 DataSendSign;            //  0 数据无更新  1有数据需要发送
	   u8 CmdSendSign;            //  0 无命令包发送  1有命令包发送
	   float FreBegin;                 //起点频率
	   float FreUP;                      //步进频率
	   float UPNum;                    //步进次数
	}AD5933CON;

extern AD5933CON  Ad5933Con;

extern float Ad5933Data[12][3];
extern float Ad5933DataBuf[12][3];


#endif

