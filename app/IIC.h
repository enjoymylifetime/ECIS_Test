#ifndef __IIC_H
#define __IIC_H
//#include<stm32f10x_lib.h>

#define SCL       GPIO_Pin_8
#define SDA       GPIO_Pin_9
#define IIC_IO    GPIOC

extern char I2C1_Data_Buffer[10];
extern char I2C1_Data_Recie[10];
extern char Recive;

void Delayus(unsigned long int time);
void IIC_Start(void);
void IIC_Stop(void);
char IIC_ACK(void);
void IIC_NACK(void);
void IIC_WriteByte(signed char byte);
char IIC_ReadByte(void);
void IIC_SendByte(unsigned short int Addr,char byte);
void IIC_SendString(unsigned short int Addr,u8 num,u8 *buf);
char IIC_ReciveByte(unsigned short int Addr);
void IIC_ReciveString(unsigned short int Addr,u8 num,u8 *buf);
void IIC_Device_Write(u8 byte);
void I2C_Configuration(void);
void I2C1_DMA(void);



 extern void  MWriteInt(u16 Address,s16 Data);
 extern s16   MReadInt(u16 Address);
 extern u8    MReadByte(s16 Address);
 extern void  MWriteByte(u16 Address,u8 Data);
 extern void  MWriteLong(u16 Address,s32 Data);
 extern s32   MReadLong(u16 Address);
 extern void  MReadPage(u8 *DataAdddress,u16 Address,u8 CharNum);
 extern void  MWritePage(u8* DataAddress,u16 Address,u8 CharNum);
 extern float MReadFloat(u16 Address);
 extern void  MWriteFloat(u16 Address,float Data);





void WriteISL22316Val(u8 val, u8 Raddr);






#endif
