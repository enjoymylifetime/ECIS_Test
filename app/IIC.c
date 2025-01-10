/*By SLLF*/
#include "includes.h"

char I2C1_Data_Buffer[10]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
char I2C1_Data_Recie[10];
char Recive=0;


 /*******************************************************************************
* Function Name  : SoftDelayus
* Description    :Delay some time.
* Input          : time:Delay time ,if time=1,delay about 1us.
* Output         : None						 
* Return         : None
*******************************************************************************/
void SoftDelayus(unsigned long int time)
    {
	unsigned long int N;
	u32 i;
	for(i=0;i<time;i++)
	    {
		N=49;
		while(N)N--;
	    }
     }

 /*******************************************************************************
* Function Name  : SoftDelayms
* Description    :Delay some time.
* Input          : time:Delay time ,if time=1,delay about 1ms.
* Output         : None						 
* Return         : None
*******************************************************************************/
void SoftDelayms(unsigned long int time)
    {
         u32 i;
	  for(i=0;i<time;i++)
	      SoftDelayus(800);         //延时1 MS
     }



 /*******************************************************************************
* Function Name  : Delayus
* Description    :Delay some time.
* Input          : time:Delay time ,if time=1,delay about 1us.
* Output         : None						 
* Return         : None
*******************************************************************************/
void Delayus(unsigned long int time)
{
	unsigned long int N;
	u32 i;
	for(i=0;i<time;i++)
	{
		N=49;
		while(N)
			N--;
	}
 }

 /*******************************************************************************
* Function Name  : IIC_Start
* Description    :Write IIC bus start signal.
* Input          : None
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_Start(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SDA|SCL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SDA|SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 10 and pin 15 */ 
	GPIO_SetBits(IIC_IO, SCL);
	GPIO_SetBits(IIC_IO, SDA);
	Delayus(3);
	GPIO_ResetBits(IIC_IO, SDA);
	Delayus(3);
	GPIO_ResetBits(IIC_IO, SCL);
	Delayus(2);
}

 /*******************************************************************************
* Function Name  : IIC_Stop
* Description    :Write IIC bus stop signal.
* Input          : None
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_Stop(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SDA|SCL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SDA|SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 8 and pin 9 */
	GPIO_ResetBits(IIC_IO,SDA); 
	GPIO_SetBits(IIC_IO, SCL);
	Delayus(3);
	GPIO_SetBits(IIC_IO, SDA);
	Delayus(2);
}

 /*******************************************************************************
* Function Name  : IIC_ACK
* Description    :Read ACK signal after write a data to device.
* Input          :None
* Output         : None						 
* Return         : None
*******************************************************************************/
char IIC_ACK(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char readvalue;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SCL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);
	//GPIO_InitStructure.GPIO_Pin =SDA;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 8 and pin 9 */
	GPIO_SetBits(IIC_IO, SCL);
	Delayus(3);
	if(GPIO_ReadInputDataBit(IIC_IO, SDA))
		readvalue=1;
	else 
		readvalue=0;
	GPIO_ResetBits(IIC_IO, SCL);
	Delayus(3);
	return readvalue;
}

 /*******************************************************************************
* Function Name  : IIC_NACK
* Description    :Send ACK signal to device after read a data.
* Input          : None
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_NACK(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SDA|SCL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SDA|SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 8 and pin 9 */
	GPIO_ResetBits(IIC_IO, SDA);
	Delayus(3);
	GPIO_SetBits(IIC_IO, SCL);
	Delayus(3);
	GPIO_ResetBits(IIC_IO, SCL);
	Delayus(2);
}

 /*******************************************************************************
* Function Name  : IIC_Writebyte
* Description    :Write a byte from IIC bus.
* Input          : 1)byte:byte will be writed
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_WriteByte(signed char byte)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char i;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SCL|SDA;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SDA|SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 8 and pin 9 */
	for(i=0;i<8;i++){
		if(byte&0x80){
			GPIO_SetBits(IIC_IO, SDA);
			Delayus(2);
			GPIO_SetBits(IIC_IO,SCL);
			Delayus(3);
			GPIO_ResetBits(IIC_IO, SCL);
			Delayus(2);
		}
		else{
			GPIO_ResetBits(IIC_IO, SDA);
			Delayus(2);
			GPIO_SetBits(IIC_IO, SCL);
			Delayus(3);
			GPIO_ResetBits(IIC_IO, SCL);
			Delayus(2);
		}
		byte=byte<<1;
	}
}

 /*******************************************************************************
* Function Name  : IIC_ReciveByte
* Description    :Read a byte data from IIC bus.
* Input          : None
* Output         : readvalue:byte read from IIC bus.						 
* Return         : None
*******************************************************************************/
char IIC_ReadByte(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char readvalue=0,i;

	/* I2C1_SCL on PB.08, I2C1_SDA on PB.09 */
	//GPIO_InitStructure.GPIO_Pin =SCL;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);
	//GPIO_InitStructure.GPIO_Pin =SDA;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init(IIC_IO,&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin=SCL;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init(IIC_IO, &GPIO_InitStructure);

	/* Set the GPIOA port pin 8 and pin 9 */
	for(i=0;i<8;i++)
	{
		GPIO_SetBits(IIC_IO, SCL);
		Delayus(3);
		if(GPIO_ReadInputDataBit(IIC_IO, SDA))
			readvalue|=0x01;
		else 
			readvalue&=0xfe;
		GPIO_ResetBits(IIC_IO, SCL);
		Delayus(3);
		if(i!=7)
			readvalue=readvalue<<1;
	}
	return readvalue;
}

 /*******************************************************************************
* Function Name  : IIC_SendByte
* Description    :Write a byte data in Address of device.
* Input          : 1)Addr:Memory device's Address the data store in.
                      3)byte:byte will be writed.
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_SendByte(unsigned short int Addr,char byte)
{
	char flag=0,Addr0,Addr1;

	Addr0=(char)(Addr&0x00ff);
	Addr1=(char)((Addr&0xff00)>>8);

	start:
	IIC_Start();
	//Delayus(3);
	IIC_WriteByte(0xA0);
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr1);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr0);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(byte);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_Stop();
	else goto start;
}

 /*******************************************************************************
* Function Name  : IIC_SendString
* Description    :Send num datas which are stored in buf in Address.
* Input          : 1)Addr:Memory device's Address the data will be stored in
                      2)num:the data number which will be writed to memory device,num<=50
                      3)buf:Address of datas which will beWrite to memory device. 
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_SendString(u16 Addr,u8 num,u8 *buf)
{
	char flag,Addr0,Addr1,Buffer[50],i;

	Addr0=(char)(Addr&0x00ff);
	Addr1=(char)((Addr&0xff00)>>8);
	for(i=0;i<num;i++)
	{
	Buffer[i]=*buf;
	*buf++;
	}

	start:
	IIC_Start();
	//Delayus(3);
	IIC_WriteByte(0xA0);
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr1);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr0);
	else goto start;
	for(i=0;i<num;i++)
		{
		  flag=IIC_ACK();
		  if(!flag)IIC_WriteByte(Buffer[i]);
		  else goto start;
		}
	flag=IIC_ACK();
	if(!flag)IIC_Stop();
	else goto start;
}


 /*******************************************************************************
* Function Name  : IIC_ReciveByte
* Description    :Read abyte data from Address and store in buf.
* Input          : 1)Addr:Memory device's Address the data stored in
* Output         : readvalue:recive byte data						 
* Return         : None
*******************************************************************************/
char IIC_ReciveByte(unsigned short int Addr)
{
	char flag,readvalue=0,Addr0,Addr1;

	Addr0=(char)(Addr&0x00ff);
	Addr1=(char)((Addr&0xff00)>>8);

	start:
	IIC_Start();
	IIC_WriteByte(0xA0);
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr1);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr0);
	else goto start;
	flag=IIC_ACK();
	if(!flag)
	{
	IIC_Start();
	IIC_WriteByte(0xA1);
	}
	else goto start;
	flag=IIC_ACK();
	if(!flag)readvalue=IIC_ReadByte();
	else goto start;
	flag=IIC_ACK();
	if(flag)IIC_Stop();
	else goto start;
	return readvalue;
}

 /*******************************************************************************
* Function Name  : IIC_ReciveString
* Description    :Read num datas from Address and store in buf.
* Input          : 1)Addr:Memory device's Address the data stored in.
                      2)num:the data number will be readed from memory device
                      3)buf:Address recived data will be stored in 
* Output         : None						 
* Return         : None
*******************************************************************************/
void IIC_ReciveString(u16 Addr,u8 num,u8 *buf)
{
	char flag,readbuf[50],i,Addr0,Addr1;

	Addr0=(char)(Addr&0x00ff);
	Addr1=(char)((Addr&0xff00)>>8);

	start:
	IIC_Start();
	IIC_WriteByte(0xA0);
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr1);
	else goto start;
	flag=IIC_ACK();
	if(!flag)IIC_WriteByte(Addr0);
	else goto start;
	flag=IIC_ACK();
	if(!flag)
	{
		IIC_Start();
		IIC_WriteByte(0xA1);
	}
	else goto start;
	flag=IIC_ACK();
	if(!flag)
		for(i=0;i<num;i++)
		{
		   readbuf[i]=IIC_ReadByte();
		   if(i!=(num-1))IIC_NACK();
		}
	else goto start;
	flag=IIC_ACK();
	if(flag)IIC_Stop();
	else goto start;
	for(i=0;i<num;i++)
	{
		*buf=readbuf[i];
		*buf++;
	}
}

 

//=========================================
//MWriteByte 函数程序
//功能:存一个字节入闪存
//参数:    DATA1:  存入64的数据
//         ADDRESS:存入64中的地址
//==========================================
void  MWriteByte(u16 Address,u8 Data)
{
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	IIC_SendByte(Address,Data);
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	//Delay_Ms(3);
}

//=========================================
//MWRITEP 函数程序
//功能:存多个字节入闪存
//参数:  DATA1:  连续存入64中的数据首地址
//       ADDRESS:连续存入64中地址的首地址
//       LONG_L: 连续存入64中数据的长度 
//==========================================
void  MWRITEP(u8* DATA1,s16 ADDRESS,u8 LONG_L)
{
	DisableSystick();
	IIC_SendString(ADDRESS,LONG_L,DATA1);
	EnableSystick();
}

//=========================================
//MReadByte 函数程序
//功能:从闪存读出一个字节
//参数:  ADDRESS:读出64中指定地址的数据
//==========================================
u8  MReadByte(s16 ADDRESS)
{ 
	u8 Data;
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	Data=IIC_ReciveByte(ADDRESS);
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	//Delay_Ms(3);
	return Data;
}

//=========================================
//MREADP 函数程序
//功能:从闪存读出多个字节
//参数:   RDATA:   连续读出64中数据的存放处
//        ADDRESS: 连续读出64中数据的首地址              
//        LONG_L:  连续读出64中数据的总长度        
//==========================================
void MREADP(u8 RDATA[],s16 ADDRESS,u8 LONG_L)
{
	DisableSystick();
	IIC_ReciveString(ADDRESS,LONG_L,RDATA);
	EnableSystick();
}


//=========================================
//MWRITE_LONTINT 函数程序
//功能:存长整型数据入闪存4字节
//参数:  ADDRESS: 长整型数据存入64的首地址              
//          DATA: 长整型存入64的数据        
//==========================================
void MWriteLong(u16 Address,s32 Data)
{
	u8  i;
	u8 *Ptr;
	Ptr=(u8 *)(&Data);
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	for(i=0;i<4;i++)
	{
		MWriteByte(Address++,*(Ptr+i));
	}
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
}

//=========================================
//MReadLong 函数程序
//功能:从闪存读出长整型数据4字节
//参数:    ADDRESS:  长整型数据读出64的首地址                     
//==========================================	
s32  MReadLong(u16 Address)
{
	u8 i;
	u8  RDATA[4];
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	for(i=0;i<4;i++)
	{
		RDATA[i]=MReadByte(Address++);
	}
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	return(*((s32*)RDATA));
}


//=========================================
//MWriteInt 函数程序
//功能:存长整型数据入闪存4字节
//参数:  ADDRESS: 长整型数据存入64的首地址              
//          DATA: 长整型存入64的数据        
//==========================================
void MWriteInt(u16 Address,s16 Data)
{
	u8  i;
	u8 *Ptr;
	Ptr=(u8 *)(&Data);
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	for(i=0;i<2;i++)
	{
		MWriteByte(Address++,*(Ptr+i)); 
	}
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
}
//MReadInt 函数程序
//功能:从闪存读出长整型数据4字节
//参数:    ADDRESS:  长整型数据读出64的首地址                     
//==========================================	
s16  MReadInt(u16 Address)
{
	u8      i;
	u8  Rdata[2];
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	for(i=0;i<2;i++)
	{
		Rdata[i]=MReadByte(Address++);
	}
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	return (*((s16 *)(Rdata)));
}       
//=========================================
//MWriteFloat 函数程序
//功能:存浮点型数据入闪存4字节
//参数:   ADDRESS:  浮点型数据存入64的首地址 
//           DATA:  浮点型存入64的数据                         
//==========================================
void MWriteFloat(u16 Address,float Data)
{
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	MWriteLong(Address,*((s32 *)(&Data)));
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
}

//=========================================
//MReadFloat 函数程序
//功能:从闪存读出浮点型数据4字节
//参数:  ADDRESS: 浮点型数据读出64的首地址                    
//==========================================	
float MReadFloat(u16 Address)
{
	s32 Data;
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	Data=MReadLong(Address);
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	return(*((float *)(&Data)));
}


//=========================================
//MWritePage 函数程序
//功能:存多个字节入闪存
//参数:  DATA1:  连续存入64中的数据首地址
//       ADDRESS:连续存入64中地址的首地址
//       LONG_L: 连续存入64中数据的长度 
//==========================================
void  MWritePage(u8* DataAddress,u16 Address,u8 CharNum)
{
	//NVIC_SETPRIMASK();     //禁止中断
	DisableSystick();
	IIC_SendString(Address,CharNum,DataAddress);
	//NVIC_RESETPRIMASK();  //使能中断
	EnableSystick();
	//Delay_Ms(3);
}
//=========================================
//MReadPage 函数程序
//功能:从闪存读出多个字节
//参数:   RDATA:   连续读出64中数据的存放处
//        Address: 连续读出64中数据的首地址              
//        CharNum:  连续读出64中数据的总长度        
//==========================================
void MReadPage(u8 *DataAdddress,u16 Address,u8 CharNum)
{
    //NVIC_SETPRIMASK();     //禁止中断
    DisableSystick();
    IIC_ReciveString(Address,CharNum,DataAdddress);
    //NVIC_RESETPRIMASK();  //使能中断
    EnableSystick();
    //Delay_Ms(3);
}




 /*******************************************************************************
* Function Name  : WriteISL22316Val
* Description       :Write a byte data to  ISL22316.
* Input                : 
* Output              : None						 
* Return              : None
*******************************************************************************/
void WriteISL22316Val(u8 val, u8 Raddr)
{
	char flag=0;

	return;

	start:
	IIC_Start();
	IIC_WriteByte(0x50);                // 0101 0000   0x50
	
	flag=IIC_ACK();
	if(!flag)
		IIC_WriteByte(Raddr);              //D′è?0μ??·
	else 
		goto start;
	
	flag=IIC_ACK();
	if(!flag)
		IIC_WriteByte(val);
	else 
		goto start;
	
	flag=IIC_ACK();
	if(!flag)
		IIC_Stop();
	else 
		goto start;
}






