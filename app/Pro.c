#include "includes.h"

/*******************************************************************************
* Function Name  : NoneMemoryInit
* Description    :  非保存参数的初始化
* Input          :  None
* Output         : None
* Return         : None
*******************************************************************************/
void NoneMemoryInit(void)
{
	Init_ADC();
	LED_Init();		            //初始化LED端口 
}

/*******************************************************************************
* Function Name  : InitAllIo
* Description    :  初始化所有引脚
* Input          :  None
* Output         : None
* Return         : None
*******************************************************************************/
void InitAllIo(void)
{
      Ini_I2c();
}


/*******************************************************************************
* Function Name  : MainRun
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
float testValu = 1100;
void MainRun(void)
{Ad5933Con.CollectingMode=0;
	//McuWorkLedCon();
      if(Ad5933Con.CollectingMode==0)    //巡回采集
      	{
      	  SysPara.FreBegin=10000;
	  DA5933_Get_RsRealImage(&Ad5933Data[Ad5933Con.MultiModeChanle][R_Impedance], &Ad5933Data[Ad5933Con.MultiModeChanle][realData], &Ad5933Data[Ad5933Con.MultiModeChanle][ImageData],Ad5933Con.MultiModeChanle);	//
	  Ad5933Con.MultiModeChanle++;

	  if(Ad5933Con.MultiModeChanle>=14)
	  	{
	  	  Ad5933Con.MultiModeChanle%=14;
	  	   memcpy((u8 *)Ad5933DataBuf,(u8 *)Ad5933Data,168);      //将数据拷贝进缓冲区
	  	   Ad5933Con.DataSendSign=1;
	  	}

	  
	  if(Ad5933Con.MultiModeChanle%14==0)
	    {
            //SysPara.FreBegin=SysPara.FreBegin*1.01;
            SysPara.FreBegin=10000;
	     //if(SysPara.FreBegin>=1000000)
	         //SysPara.FreBegin=500;
	    }
         SysPara.FreUP=1;
         SysPara.UPNum=10;
	  
      	}
      else   //指定通道采集
      	{
      	  DA5933_Get_RsRealImage(&Ad5933Data[Ad5933Con.SingleModeChanle][R_Impedance], &Ad5933Data[Ad5933Con.SingleModeChanle][realData], &Ad5933Data[Ad5933Con.SingleModeChanle][ImageData],Ad5933Con.SingleModeChanle);	//
         Ad5933Con.DataSendSign=1;
      	}
}











