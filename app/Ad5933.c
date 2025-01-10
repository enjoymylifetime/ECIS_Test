#include "AD5933.h"
#include "delay.h"
#include <math.h>
#include "includes.h"



#define Delay_IIC_2     2
#define Delay_IIC_4     4
#define Delay_IIC_8     8



#define AD5933 1
#define AD5933_MCLK 16.776


float R_Impedance1, realData1, imageData1;	//所夹持电阻的阻值，实部数据，虚部数据
float R_Impedance2, realData2, imageData2;	//所夹持电阻的阻值，实部数据，虚部数据

u32                  Ad5933SdaGpioPinBuf[14];
GPIO_TypeDef  *Ad5933SdaGpioType[14];   

AD5933CON  Ad5933Con;

float Ad5933Data[12][3];
float Ad5933DataBuf[12][3];

void Ini_I2c( void )      //初始化I2C
	{
	    GPIO_InitTypeDef GPIO_InitStructure;
	    RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE );

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_1;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //推挽输出
	    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;    
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(Ad5933IICSclIO_1, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_1;
	    GPIO_Init(Ad5933IICSdaIO_1, &GPIO_InitStructure);
	    Ad5933SCL_1=1;
	    Ad5933SDA_1=1;
          Ad5933SdaGpioPinBuf[Channel1]=Ad5933SDAPin_1;
          Ad5933SdaGpioType[Channel1]=Ad5933IICSdaIO_1;



	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_2;
	    GPIO_Init(Ad5933IICSclIO_2, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_2;
	    GPIO_Init(Ad5933IICSdaIO_2, &GPIO_InitStructure);
	    Ad5933SCL_2=1;
	    Ad5933SDA_2=1;
          Ad5933SdaGpioPinBuf[Channel2]=Ad5933SDAPin_2;
          Ad5933SdaGpioType[Channel2]=Ad5933IICSdaIO_2;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_3;
	    GPIO_Init(Ad5933IICSclIO_3, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_3;
	    GPIO_Init(Ad5933IICSdaIO_3, &GPIO_InitStructure);
	    Ad5933SCL_3=1;
	    Ad5933SDA_3=1;
          Ad5933SdaGpioPinBuf[Channel3]=Ad5933SDAPin_3;
          Ad5933SdaGpioType[Channel3]=Ad5933IICSdaIO_3;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_4;
	    GPIO_Init(Ad5933IICSclIO_4, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_4;
	    GPIO_Init(Ad5933IICSdaIO_4, &GPIO_InitStructure);
	    Ad5933SCL_4=1;
	    Ad5933SDA_4=1;
          Ad5933SdaGpioPinBuf[Channel4]=Ad5933SDAPin_4;
          Ad5933SdaGpioType[Channel4]=Ad5933IICSdaIO_4;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_5;
	    GPIO_Init(Ad5933IICSclIO_5, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_5;
	    GPIO_Init(Ad5933IICSdaIO_5, &GPIO_InitStructure);
	    Ad5933SCL_5=1;
	    Ad5933SDA_5=1;
          Ad5933SdaGpioPinBuf[Channel5]=Ad5933SDAPin_5;
          Ad5933SdaGpioType[Channel5]=Ad5933IICSdaIO_5;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_6;
	    GPIO_Init(Ad5933IICSclIO_6, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_6;
	    GPIO_Init(Ad5933IICSdaIO_6, &GPIO_InitStructure);
	    Ad5933SCL_6=1;
	    Ad5933SDA_6=1;
          Ad5933SdaGpioPinBuf[Channel6]=Ad5933SDAPin_6;
          Ad5933SdaGpioType[Channel6]=Ad5933IICSdaIO_6;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_7;
	    GPIO_Init(Ad5933IICSclIO_7, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_7;
	    GPIO_Init(Ad5933IICSdaIO_7, &GPIO_InitStructure);
	    Ad5933SCL_7=1;
	    Ad5933SDA_7=1;
          Ad5933SdaGpioPinBuf[Channel7]=Ad5933SDAPin_7;
          Ad5933SdaGpioType[Channel7]=Ad5933IICSdaIO_7;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_8;
	    GPIO_Init(Ad5933IICSclIO_8, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_8;
	    GPIO_Init(Ad5933IICSdaIO_8, &GPIO_InitStructure);
	    Ad5933SCL_8=1;
	    Ad5933SDA_8=1;
          Ad5933SdaGpioPinBuf[Channel8]=Ad5933SDAPin_8;
          Ad5933SdaGpioType[Channel8]=Ad5933IICSdaIO_8;	  

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_9;
	    GPIO_Init(Ad5933IICSclIO_9, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_9;
	    GPIO_Init(Ad5933IICSdaIO_9, &GPIO_InitStructure);
	    Ad5933SCL_9=1;
	    Ad5933SDA_9=1;
          Ad5933SdaGpioPinBuf[Channel9]=Ad5933SDAPin_9;
          Ad5933SdaGpioType[Channel9]=Ad5933IICSdaIO_9;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_10;
	    GPIO_Init(Ad5933IICSclIO_10, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_10;
	    GPIO_Init(Ad5933IICSdaIO_10, &GPIO_InitStructure);
	    Ad5933SCL_10=1;
	    Ad5933SDA_10=1;
          Ad5933SdaGpioPinBuf[Channel10]=Ad5933SDAPin_10;
          Ad5933SdaGpioType[Channel10]=Ad5933IICSdaIO_10;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_11;
	    GPIO_Init(Ad5933IICSclIO_11, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_11;
	    GPIO_Init(Ad5933IICSdaIO_11, &GPIO_InitStructure);
	    Ad5933SCL_11=1;
	    Ad5933SDA_11=1;
          Ad5933SdaGpioPinBuf[Channel11]=Ad5933SDAPin_11;
          Ad5933SdaGpioType[Channel11]=Ad5933IICSdaIO_11;

	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_12;
	    GPIO_Init(Ad5933IICSclIO_12, &GPIO_InitStructure);
	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_12;
	    GPIO_Init(Ad5933IICSdaIO_12, &GPIO_InitStructure);
	    Ad5933SCL_12=1;
	    Ad5933SDA_12=1;
          Ad5933SdaGpioPinBuf[Channel12]=Ad5933SDAPin_12;
          Ad5933SdaGpioType[Channel12]=Ad5933IICSdaIO_12;

//	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_13;
//	    GPIO_Init(Ad5933IICSclIO_13, &GPIO_InitStructure);
//	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_13;
//	    GPIO_Init(Ad5933IICSdaIO_13, &GPIO_InitStructure);
//	    Ad5933SCL_13=1;
//	    Ad5933SDA_13=1;
//          Ad5933SdaGpioPinBuf[Channel13]=Ad5933SDAPin_13;
//          Ad5933SdaGpioType[Channel13]=Ad5933IICSdaIO_13;

//	    GPIO_InitStructure.GPIO_Pin = Ad5933SCLPin_14;
//	    GPIO_Init(Ad5933IICSclIO_14, &GPIO_InitStructure);
//	    GPIO_InitStructure.GPIO_Pin = Ad5933SDAPin_14;
//	    GPIO_Init(Ad5933IICSdaIO_14, &GPIO_InitStructure);
//	    Ad5933SCL_14=1;
//	    Ad5933SDA_14=1;
//          Ad5933SdaGpioPinBuf[Channel14]=Ad5933SDAPin_14;
//          Ad5933SdaGpioType[Channel14]=Ad5933IICSdaIO_14;

		
	    return;
	}


void SDA_IN(u8 RoudNo)
    {
	GPIO_InitTypeDef GPIO_InitStructure;
       GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
       GPIO_InitStructure.GPIO_Pin=Ad5933SdaGpioPinBuf[RoudNo];
	GPIO_Init(Ad5933SdaGpioType[RoudNo], &GPIO_InitStructure);
    }

void SDA_OUT(u8 RoudNo)
    {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=Ad5933SdaGpioPinBuf[RoudNo];;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init(Ad5933SdaGpioType[RoudNo], &GPIO_InitStructure);
    }


void GetACK(u8 GroupNo)
{
    u8 ucErrTime = 0;
    SDA_IN(GroupNo);      //SDA设置为输入
    switch(GroupNo)
    	{
    	  case Channel1:       Ad5933SDA_1 = 1;   break;
	  case Channel2:       Ad5933SDA_2 = 1;   break;  
	  case Channel3:       Ad5933SDA_3 = 1;   break;  
	  case Channel4:       Ad5933SDA_4 = 1;   break;  
	  case Channel5:       Ad5933SDA_5 = 1;   break;  
	  case Channel6:       Ad5933SDA_6 = 1;   break;  
	  case Channel7:       Ad5933SDA_7 = 1;   break;  
	  case Channel8:       Ad5933SDA_8 = 1;   break;  
	  case Channel9:       Ad5933SDA_9 = 1;   break;  
	  case Channel10:     Ad5933SDA_10 = 1;  break;  
	  case Channel11:     Ad5933SDA_11 = 1;  break;  
	  case Channel12:     Ad5933SDA_12 = 1;  break;  
	  case Channel13:     Ad5933SDA_13 = 1;  break;  
	  case Channel14:     Ad5933SDA_14 = 1;  break;  
         default:    break;
    	}
    delay_us(Delay_IIC_2);
    switch(GroupNo)
    	{
    	  case Channel1: 	Ad5933SCL_1 = 1;  break;
	  case Channel2: 	Ad5933SCL_2 = 1;  break;
	  case Channel3: 	Ad5933SCL_3 = 1;  break;
	  case Channel4: 	Ad5933SCL_4 = 1;  break;
	  case Channel5: 	Ad5933SCL_5 = 1;  break;
	  case Channel6: 	Ad5933SCL_6 = 1;  break;
	  case Channel7: 	Ad5933SCL_7 = 1;  break;
	  case Channel8: 	Ad5933SCL_8 = 1;  break;
	  case Channel9:   Ad5933SCL_9 = 1;  break;
	  case Channel10: Ad5933SCL_10 = 1;  break;
	  case Channel11: Ad5933SCL_11 = 1;  break;
	  case Channel12: Ad5933SCL_12 = 1;  break;
	  case Channel13: Ad5933SCL_13 = 1;  break;
	  case Channel14: Ad5933SCL_14 = 1;  break;
	  default: break;
    	}
    delay_us(Delay_IIC_2);

    switch(GroupNo)
    	{
    	  case Channel1: while(Ad5933READ_SDA_1)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
		  	  break;
	  case Channel2:   while(Ad5933READ_SDA_2)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel3:   while(Ad5933READ_SDA_3)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel4:   while(Ad5933READ_SDA_4)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;	
	  case Channel5:   while(Ad5933READ_SDA_5)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel6:   while(Ad5933READ_SDA_6)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel7:   while(Ad5933READ_SDA_7)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel8:   while(Ad5933READ_SDA_8)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel9:   while(Ad5933READ_SDA_9)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel10:   while(Ad5933READ_SDA_10)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel11:   while(Ad5933READ_SDA_11)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel12:   while(Ad5933READ_SDA_12)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel13:   while(Ad5933READ_SDA_13)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  case Channel14:   while(Ad5933READ_SDA_14)
			    {
			        ucErrTime++;
			        if(ucErrTime > 250)
			        {
			            STOP(GroupNo);
			            return;
			        }
			    }
	  	         break;
	  default: break;
    	}
	
    switch(GroupNo)
    	{
    	  case Channel1: 	Ad5933SCL_1 = 0; 	break;
	  case Channel2: 	Ad5933SCL_2 = 0;  	break;
	  case Channel3: 	Ad5933SCL_3 = 0;  	break;
	  case Channel4: 	Ad5933SCL_4 = 0;  	break;
	  case Channel5: 	Ad5933SCL_5 = 0;  	break;
	  case Channel6: 	Ad5933SCL_6 = 0;  	break;
	  case Channel7: 	Ad5933SCL_7 = 0;  	break;
	  case Channel8: 	Ad5933SCL_8 = 0;  	break;
	  case Channel9: 	Ad5933SCL_9 = 0;  	break;
	  case Channel10: Ad5933SCL_10 = 0;  	break;
	  case Channel11: Ad5933SCL_11 = 0;  	break;
	  case Channel12: Ad5933SCL_12 = 0;  	break;
	  case Channel13: Ad5933SCL_13 = 0;  	break;
	  case Channel14: Ad5933SCL_14 = 0;  	break;
	  default: break;
    	}	
}

void SendNACK(u8 GroupNo)
{
    switch(GroupNo)
    	{
    	  case Channel1:     
				Ad5933SCL_1 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_1 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_1 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_1 = 0;
				break;
	  case Channel2:    
				Ad5933SCL_2 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_2 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_2 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_2 = 0;
				break;
	  case Channel3:    
				Ad5933SCL_3 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_3 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_3 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_3 = 0;
	  	        break;
	  case Channel4:    
				Ad5933SCL_4 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_4 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_4 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_4 = 0;
	  	        break;
	  case Channel5:    
				Ad5933SCL_5 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_5 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_5 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_5 = 0;
	  	        break;
	  case Channel6:    
				Ad5933SCL_6 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_6 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_6 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_6 = 0;
	  	        break;
	  case Channel7:    
				Ad5933SCL_7 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_7 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_7 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_7 = 0;
	  	        break;
	  case Channel8:    
				Ad5933SCL_8 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_8 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_8 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_8 = 0;
	  	        break;
	  case Channel9:    
				Ad5933SCL_9 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_9 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_9 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_9 = 0;
	  	        break;
	  case Channel10:    
				Ad5933SCL_10 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_10 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_10 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_10 = 0;
	  	        break;
	  case Channel11:    
				Ad5933SCL_11 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_11 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_11 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_11 = 0;
	  	        break;
	  case Channel12:    
				Ad5933SCL_12 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_12 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_12 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_12 = 0;
	  	        break;
	  case Channel13:    
				Ad5933SCL_13 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_13 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_13 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_13 = 0;
	  	        break;
	  case Channel14:    
				Ad5933SCL_14 = 0;
				SDA_OUT(GroupNo);
				Ad5933SDA_14 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_14 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_14 = 0;
	  	        break;
	  default: break;
    	}

}

void START(u8 GroupNo)    // 启动数据总线
{
    switch(GroupNo)
    	{
    	  case Channel1:     
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_1 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_1 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_1 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_1 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel2:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_2 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_2 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_2 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_2 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel3:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_3 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_3 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_3 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_3 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel4:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_4 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_4 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_4 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_4 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel5:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_5 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_5 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_5 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_5 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel6:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_6 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_6 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_6 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_6 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel7:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_7 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_7 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_7 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_7 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel8:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_8 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_8 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_8 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_8 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel9:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_9 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_9 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_9 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_9 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel10:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_10 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_10 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_10 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_10= 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel11:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_11 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_11 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_11 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_11 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel12:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_12 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_12 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_12 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_12 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel13:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_13 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_13= 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_13 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_13 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  case Channel14:    
				SDA_OUT(GroupNo);     //sda线输出
				Ad5933SDA_14 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_14 = 1;
				delay_us(Delay_IIC_8);
				Ad5933SDA_14 = 0; //START:when CLK is high,DATA change form high to low
				delay_us(Delay_IIC_8);
				Ad5933SCL_14 = 0; //钳住I2C总线，准备发送或接收数据
				break;
	  default: break;
    	}

}

void STOP(u8 GroupNo)
{
   switch(GroupNo)
   	{
   	  case Channel1:     
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_1 = 0;
				Ad5933SDA_1 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_1 = 1;
				Ad5933SDA_1 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	              break;
	  case Channel2:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_2 = 0;
				Ad5933SDA_2 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_2 = 1;
				Ad5933SDA_2 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel3:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_3 = 0;
				Ad5933SDA_3 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_3 = 1;
				Ad5933SDA_3 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel4:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_4 = 0;
				Ad5933SDA_4 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_4 = 1;
				Ad5933SDA_4 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel5:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_5 = 0;
				Ad5933SDA_5 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_5 = 1;
				Ad5933SDA_5 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel6:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_6 = 0;
				Ad5933SDA_6 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_6 = 1;
				Ad5933SDA_6 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel7:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_7 = 0;
				Ad5933SDA_7 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_7 = 1;
				Ad5933SDA_7 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel8:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_8 = 0;
				Ad5933SDA_8 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_8 = 1;
				Ad5933SDA_8 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel9:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_9 = 0;
				Ad5933SDA_9 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_9 = 1;
				Ad5933SDA_9 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel10:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_10 = 0;
				Ad5933SDA_10 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_10 = 1;
				Ad5933SDA_10 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel11:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_11 = 0;
				Ad5933SDA_11 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_11 = 1;
				Ad5933SDA_11 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel12:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_12 = 0;
				Ad5933SDA_12 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_12 = 1;
				Ad5933SDA_12 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel13:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_13 = 0;
				Ad5933SDA_13 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_13= 1;
				Ad5933SDA_13 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  case Channel14:  
				SDA_OUT(GroupNo);//sda线输出
				Ad5933SCL_14 = 0;
				Ad5933SDA_14 = 0; //STOP:when CLK is high DATA change form low to high
				delay_us(Delay_IIC_8);
				Ad5933SCL_14 = 1;
				Ad5933SDA_14 = 1; //发送I2C总线结束信号
				delay_us(Delay_IIC_8);
	  	       	break;
	  default: break;
   	}

}

void SendByte(u8 txd,u8 GroupNo)	// 发送一个字节数据子函数
{
    u8 t;
   switch(GroupNo)
   	{
   	  case Channel1:      
				SDA_OUT(GroupNo);
				Ad5933SCL_1 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_1 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_1 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_1 = 0;
				delay_us(Delay_IIC_4);
				}
				break;
	  case Channel2:   
				SDA_OUT(GroupNo);
				Ad5933SCL_2 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_2 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_2 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_2 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel3:   
				SDA_OUT(GroupNo);
				Ad5933SCL_3 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_3 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_3 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_3 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel4:   
				SDA_OUT(GroupNo);
				Ad5933SCL_4 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_4 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_4 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_4 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel5:   
				SDA_OUT(GroupNo);
				Ad5933SCL_5 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_5 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_5 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_5 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel6:   
				SDA_OUT(GroupNo);
				Ad5933SCL_6 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_6 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_6 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_6 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel7:   
				SDA_OUT(GroupNo);
				Ad5933SCL_7 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_7 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_7 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_7 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel8:   
				SDA_OUT(GroupNo);
				Ad5933SCL_8 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_8 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_8 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_8 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel9:   
				SDA_OUT(GroupNo);
				Ad5933SCL_9 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_9 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_9 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_9 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel10:   
				SDA_OUT(GroupNo);
				Ad5933SCL_10 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_10 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_10 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_10 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel11:   
				SDA_OUT(GroupNo);
				Ad5933SCL_11 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_11 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_11 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_11 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel12:   
				SDA_OUT(GroupNo);
				Ad5933SCL_12 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_12 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_12 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_12 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel13:   
				SDA_OUT(GroupNo);
				Ad5933SCL_13 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_13 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_13 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_13 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  case Channel14:   
				SDA_OUT(GroupNo);
				Ad5933SCL_14 = 0; //拉低时钟开始数据传输
				delay_us(Delay_IIC_4);
				for(t = 0; t < 8; t++)
				{
				Ad5933SDA_14 = (txd & 0x80) >> 7;
				txd <<= 1;
				delay_us(Delay_IIC_4); //对TEA5767这三个延时都是必须的
				Ad5933SCL_14 = 1;
				delay_us(Delay_IIC_4);
				Ad5933SCL_14 = 0;
				delay_us(Delay_IIC_4);
				}
				 break;
	  default: break;
   	}
   

}

u8 ReadByte(u8 GroupNo)  //读一个字节数据
{
    unsigned char i, receive = 0;
	
    SDA_IN(GroupNo);//SDA设置为输入
    delay_us(Delay_IIC_4);

    switch(GroupNo)
    	{
    	  case Channel1:      
		  	       for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_1 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_1 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_1)receive++;
				        delay_us(Delay_IIC_2);
				    }
		  	  break;
	  case Channel2:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_2 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_2 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_2)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel3:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_3= 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_3 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_3)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel4:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_4 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_4 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_4)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel5:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_5 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_5 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_5)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel6:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_6 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_6 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_6)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel7:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_7 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_7 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_7)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel8:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_8 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_8 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_8)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel9:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_9 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_9 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_9)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel10:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_10 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_10 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_10)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;		 
	  case Channel11:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_11 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_11 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_11)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel12:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_12 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_12 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_12)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel13:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_13 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_13 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_13)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;
	  case Channel14:    
	  	              for(i = 0; i < 8; i++ )
				    {
				        Ad5933SCL_14 = 0;
				        delay_us(Delay_IIC_4);
				        Ad5933SCL_14 = 1;
				        receive <<= 1;
				        if(Ad5933READ_SDA_14)receive++;
				        delay_us(Delay_IIC_2);
				    }
	  	         break;				 
	  default: break;
    	}
    SendNACK(GroupNo);
    return receive;
}

void Write_Byte(char nAddr, uint nValue,u8 GroupNo) //nAddr中写入字节nValue
{
    int nTemp = 0x1A;      // AD5933的默认地址&写控制位（低）

    START(GroupNo);
    SendByte(nTemp,GroupNo);     // 发送地址
    GetACK(GroupNo);
    SendByte(nAddr,GroupNo);     // 发送地址字节
    GetACK(GroupNo);
    SendByte(nValue,GroupNo);	// 发送数据字节
    GetACK(GroupNo);
    STOP(GroupNo);	// 停止总线
    return;
}

void SetPointer(char nAddr,u8 GroupNo)  //   设置地址指针
{
    int nTemp = 0x1A;      // AD5933的默认地址&写控制位（低）

    START(GroupNo);
    SendByte(nTemp,GroupNo);     // 发送地址
    GetACK(GroupNo);     // 等待 ACK
    SendByte(0xB0,GroupNo);     // 发送指针命令1101 0000
    GetACK(GroupNo);
    SendByte(nAddr,GroupNo);	// 发送地址指针
    GetACK(GroupNo);
    STOP(GroupNo);	// 停止总线
    return;
}

int Rece_Byte(char nAddr,u8 GroupNo)//读取nAddr中的字节到返回值
{
    int nTemp ;

    SetPointer(nAddr,GroupNo);   //地址指针指向nAddr
    nTemp = 0x1B;    // AD5933的默认地址&读控制位（高）
    START(GroupNo);
    SendByte(nTemp,GroupNo);     // 发送地址
    GetACK(GroupNo);
    nTemp = ReadByte(GroupNo); //读一个字节数据
    SendNACK(GroupNo);//发送NO_ACK
    STOP(GroupNo);	// 停止总线
    return nTemp;
}


u16 AD5933_Tempter(u8 GroupNo)
{
    unsigned int Tm;   //温度


    //启动温度测量
    Write_Byte(0x80, 0x93,GroupNo);

    //读出温度，保存在Tm中
    Tm = Rece_Byte(0x92,GroupNo);
    Tm <<= 8;
    Tm += Rece_Byte(0x93,GroupNo);
    Tm <<= 2;

    return Tm;
}
#define swpPNTCnt	500
float resistance[swpPNTCnt];
float rads[swpPNTCnt];
float AD5933_Dat_Re[swpPNTCnt];
float AD5933_Dat_Im[swpPNTCnt];


void Maopao_Paixu(float *dat, u16 leng)
{
    u16 i, j;
    float buf;
    for(j = 0; j < leng - 1; j++)
        for(i = 0; i < leng - j - 1; i++)
            if(dat[i] > dat[i + 1])
            {
                buf = dat[i];
                dat[i] = dat[i + 1];
                dat[i + 1] = buf;
            }
}


float Get_AVE(float src[], u16 num)
{
    u16 i, cnt = 0;
    float sum;
    Maopao_Paixu(src, num);

    sum = 0;
    for(i = num / 2 - num / 4; i < num / 2 + num / 4; i++)
    {
        sum += src[i];
        cnt++;
    }
    sum = sum / cnt;
    return sum;
}
void Fre_To_Hex(float fre, u8 *buf)
{
    u32 dat;
    dat = (536870912 / (double)(AD5933_MCLK * 1000000)) * fre;

    buf[0] = dat >> 16;
    buf[1] = dat >> 8;
    buf[2] = dat;

}

/*
函数名：AD5933_Sweep
功  能：	频率扫描。按设定的频率起点，频率步进，步数及输出幅值，进行增量扫描或重复频率扫描，经内部gain增益后采集实部，虚部，换算阻抗值
输  入：	Fre_Begin 		开始频率；(范围：1k~100k Hz， 精度0.1Hz)
			Fre_UP			步进频率；(范围：1k~100k Hz， 精度0.1Hz)
			UP_Num			步进次数；(范围：0~511)
			OUTPUT_Vatage	输出电压；(范围：AD5933_OUTPUT_2V/AD5933_OUTPUT_1V/AD5933_OUTPUT_400mV/AD5933_OUTPUT_200mV)
			Gain： 			内部增益(范围：AD5933_Gain_1/AD5933_Gain_5)
			SWeep_Rep		扫描模式(范围：AD5933_Fre_UP:递增频率扫描；AD5933_Fre_Rep：重复频率扫描)
输  出：	R_Impedance：	电阻值；
			realData：		实部数据；
			imageData：	虚部数据；
注  释：无
*/
float AD5933_Sweep (float Fre_Begin, float Fre_UP, u16 UP_Num, u16 OUTPUT_Vatage, u16 Gain, u16 SWeep_Rep,u8 GroupNo)
{
    u8 SValue[3], IValue[3], NValue[2], CValue[2];
    u16 buf = 0;
    Fre_To_Hex(Fre_Begin, SValue);
    Fre_To_Hex(Fre_UP, IValue);
    NValue[0] = UP_Num >> 8;
    NValue[1] = UP_Num;
#if AD5933_MCLK_USE_OUT == 1
    buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_OUT_MCLK;
#else
    buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_IN_MCLK;
#endif
    CValue[0] = buf >> 8;
    CValue[1] = buf;

    Scale_imp(SValue, IValue, NValue, CValue,GroupNo);
    return 0;
}
/*SValue[3]起始频率，IValue[3]频率增量，NValue[2]增量数，CValue[2]控制字，ki增益系数，Ps扫频为1重复为0*/
long ReadTemp, realArr[3], imageArr[3];
float Scale_imp (u8 *SValue, u8 *IValue, u8 *NValue, u8 *CValue,u8 GroupNo)
{
    static uint16_t repCnt = 0;
    int i, j, AddrTemp;
    u8 Gain = ((~CValue[0]) & 0x01) ? 5 : 1;
    u8 SWeep_Rep = ((CValue[0] & 0xF0) == (AD5933_Fre_UP >> 8)) ? 1 : 0;
    u8 Mode = CValue[0] & 0x0f;

    float magnitude;
    j = 0;
    Ini_I2c();    //初始化I2C

    AddrTemp = 0X82; //初始化起始频率寄存器
    for(i = 0; i < 3; i++)
    {
        Write_Byte(AddrTemp, SValue[i],GroupNo);
        AddrTemp++;
    }
    AddrTemp = 0X85; //初始化频率增量寄存器
    for(i = 0; i < 3; i++)
    {
        Write_Byte(AddrTemp, IValue[i],GroupNo);
        AddrTemp++;
    }
    AddrTemp = 0X88; //初始化频率点数寄存器
    for(i = 0; i < 2; i++)
    {
        Write_Byte(AddrTemp, NValue[i],GroupNo);
        AddrTemp++;
    }

    // Transmit to settling time cycles register (沉降时间周期数)
    // program 15 output cycles at each frequency before a adc conversion
    Write_Byte ( 0x8B, 15,GroupNo);
    Write_Byte ( 0x8A, 0x00,GroupNo);

    //初始化控制寄存器
    AddrTemp = 0X80;
    //                for(i = 0;i <2;i++)
    {
        Write_Byte(AddrTemp, Mode | (AD5933_Standby >> 8),GroupNo);
        AddrTemp++;
        Write_Byte(AddrTemp, CValue[1],GroupNo);
        AddrTemp++;
    }

    Write_Byte(0x80, Mode | (AD5933_SYS_Init >> 8),GroupNo); //控制寄存器写入初始化频率扫描命令
    delay_ms(10);
    Write_Byte(0X80, Mode | (AD5933_Begin_Fre_Scan >> 8),GroupNo); //控制寄存器写入开始频率扫描命令

    repCnt = 0;
    while(1)
    {
        while(1)
        {
            ReadTemp = Rece_Byte(0x8F,GroupNo); //读取状态寄存器检查DFT是否完成
            if (ReadTemp & 0x02)
                break;
        }

        realArr[0] = Rece_Byte(0x94,GroupNo);
        realArr[1] = Rece_Byte(0x95,GroupNo);
        realArr[2] = realArr[0] * 0x100 + realArr[1];

        imageArr[0] = Rece_Byte(0x96,GroupNo);
        imageArr[1] = Rece_Byte(0x97,GroupNo);
        imageArr[2] = imageArr[0] * 0x100 + imageArr[1];

        rads[j] = atan2((float)imageArr[2], (float)realArr[2]) - 0.00143485062;

				if (realArr[2] >= 0x8000) //计算实部的原码(除符号位外，取反加一)
        {
            realArr[2] = -(0x10000-realArr[2]);
        }
        if (imageArr[2] >= 0x8000) //计算虚部的原码(除符号位外，取反加一)
        {
            imageArr[2] = -(0x10000-imageArr[2]);
        }
				
				AD5933_Dat_Re[j] = realArr[2];			//将实部数据存储到数组AD5933_Dat_Re
        AD5933_Dat_Im[j] = imageArr[2];			//将虚部数据存储到数组AD5933_Dat_Im
				
				#if 0
        if (realArr[2] >= 0x8000) //计算实部的原码(除符号位外，取反加一)
        {
            realArr[2] ^= 0xFFFF;
            realArr[2] ^= 0x8000;
            realArr[2] += 1;
            realArr[2] ^= 0x8000;
        }
        if (imageArr[2] >= 0x8000) //计算虚部的原码(除符号位外，取反加一)
        {
            imageArr[2] ^= 0xFFFF;
            imageArr[2] ^= 0x8000;
            imageArr[2] += 1;
            imageArr[2] ^= 0x8000;
        }
				#endif
				
        //AD5933_Dat_Re[j] = realArr[2];			//将实部数据存储到数组AD5933_Dat_Re
        //AD5933_Dat_Im[j] = imageArr[2];			//将虚部数据存储到数组AD5933_Dat_Im
        magnitude = sqrt((float)(realArr[2] * realArr[2] + imageArr[2] * imageArr[2])); //模值计算
				
        //resistance[j++] = 1 / (magnitude * Gain);		 //阻抗计算
				//resistance[j++]=100.0/magnitude;
				
				resistance[j++]=magnitude;//for test 20240926
				
        ReadTemp = Rece_Byte(0x8F,GroupNo); //读取状态寄存器检查频率扫描是否完成
        if (ReadTemp & 0x04)
            break;
        if (SWeep_Rep == 1)		//频率递增扫描模式
        {
            Write_Byte(0X80, CValue[0],GroupNo);	//控制寄存器写入增加频率（跳到下一个频率点)的命令
        }
        else		//频率重复模式
        {
            repCnt++;
            if(repCnt >= *NValue)
            {
                break;
            }
            Write_Byte(0X80, CValue[0],GroupNo);	//控制寄存器写入重复当前频率点扫描
        }
    }
    Write_Byte(0X80, 0XA1,GroupNo);	//进入掉电模式
    return magnitude;
}


/*
函数名：DA5933_Get_RsRealImage
功     能：获得所夹持电阻的阻值，及测得的实部数据及虚部数据
输     入：无
输     出：R_Impedance：电阻值；	realData：实部数据；	imageData：虚部数据；
注     释：无
*/


float DA5933_Get_RsRealImage(float *R_Impedance, float *realData, float *imageData,u8 GroupNo)
{
    float RsWord, ReWord, ImWord;

		//从频率10240Hz开始扫描，1Hz步进，扫描swpPNTCnt步，输出幅度2V，增益1,扫描模式
    //AD5933_Sweep(10240, 1, swpPNTCnt, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP,GroupNo);
    AD5933_Sweep(SysPara.FreBegin, SysPara.FreUP, SysPara.UPNum, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP,GroupNo);

	
    RsWord = Get_AVE(resistance,    SysPara.UPNum);	//阻抗数据的结果都存放在数组resistance， 从该数组求一个均值
    ReWord = Get_AVE(AD5933_Dat_Re, SysPara.UPNum);	//实部数据的结果都存放在数AD5933_Dat_Re，从该数组求一个均值
    ImWord = Get_AVE(AD5933_Dat_Im, SysPara.UPNum);	//虚部数据的结果都存放在数AD5933_Dat_Im，从该数组求一个均值

		//注：
		//AD5933测量值时，模值数据与电阻值具有一定的非线性，校准方法较多，一般比较简单的可采用多线段校正(也可用其他方法)
		//RsWord即为所测得阻抗模值，用户可利用该数据进行多线段校正，如分别记录5k，10k，50k，100k，500k时RsWord的值，
		//后续测得RsWord值时，找到RsWord值在哪个区间及其位置，再将值线性对应到该位置对应的阻值
		//下述例程为仅以10k标准电阻校准的简单校准方法，用户需更大范围或更准确数值时，可参考上述或其他方法
	
		//y = 164438x - 758.5(0-1k)
		//y = 2E+06x - 7188.5(1k-10k)
		//y = 317.83x2 + 19353x + 722.31(0.478194338,4.75737393)(10k-100k)
		//y = 2176.3x2 - 4534.9x + 72318(4.75737393,10.16260163)(100k-251k)
		#if 0
		if(RsWord <= 0.016)
		{
				//*R_Impedance = 164438*RsWord - 758.5;
				*R_Impedance = 1639100*RsWord - 7188.5;
		}
		else if(RsWord <= 0.478194338)
		{
				*R_Impedance = 1175.6 * pow(RsWord,2) + 20226*RsWord + 34.445;
		}
		else if(RsWord <= 4.75737393)
		{
				*R_Impedance = 317.83 * pow(RsWord,2) + 19353*RsWord + 722.31;
		}
		else if(RsWord <= 25)
		{
				*R_Impedance = 2176.3 * pow(RsWord,2) - 4534.9*RsWord + 72318;
		}		
		else
		{
				*R_Impedance = 1250000;
		}
		#endif
		//for test
		*R_Impedance = RsWord;
		
    //*R_Impedance = RsWord * AD5933_Correction;	//阻抗数据乘以一个校准因子，得到电阻值
		//*R_Impedance = sqrt(ReWord * ReWord + ImWord*ImWord);	//阻抗数据乘以一个校准因子，得到电阻值
    *realData = ReWord;
		//*realData = atan2(ImWord, ReWord)*180*0.318309886;
    *imageData = ImWord;

    return *R_Impedance;
}
