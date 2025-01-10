#include "includes.h"

const u8 str[1024*16] __attribute__((at(0x08004000)));        //在FLASH中开辟16K空间

STORAGE PerPara;
STORAGE SysPara;


//--------保存重要参数-----------------------
void WritePageParaData(void)
{
	u16 i;

	PerPara=SysPara;

	FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
	  				FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	if(FLASH_EraseSector(FLASH_Sector_1, VoltageRange_3) != FLASH_COMPLETE)
	{ 
		while (1);
	}

	for(i=0;i<FLASHMEMNUM;i++)
	{
		FLASH_ProgramWord(BaseFlashAddr+4*i,*((u32 *)(&PerPara)+i));     //写入数据1
	}
	FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}


//---------------------------------------------------
//------读取重要参数--------------------------
void  ReadPageParaData(void)
  {
	u16 i;
	for(i=0;i<FLASHMEMNUM;i++)
	{
		*((u32 *)(&PerPara)+i)=*((u32 *)BaseFlashAddr+i);
	}

	SysPara=PerPara;
   }




/*******************************************************************************
* Function Name  : InitialPerpara
* Description    : -初始化固有参数-
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void InitialPerpara(void)
{

     if(PerPara.InitVal!=0xaaaaaaaa)
     	{
     	   SysPara.InitVal=0xaaaaaaaa;
	   SysPara.FreBegin=10000;
	   SysPara.FreUP=1;
	   SysPara.UPNum=10;
	   SysPara.PowerOffCnt=0;
	   WritePageParaData();
	   ReadPageParaData();        //读回系统参数里面
     	}
    else
    	{
           PerPara.PowerOffCnt++;
	    WritePageParaData();
	    ReadPageParaData();        //读回系统参数里面
    	}

	 
}


void PowerOnInitial(void)
	{
	    Ad5933Con.CollectingMode=0;     //循环采集模式
	    Ad5933Con.SingleModeChanle=0;
	}



//---------------------------------------------------------------------------            
void ParameterRecovery(void)
    {
	PowerOnInitial();
	ReadPageParaData();        //恢复永久参数
	InitialPerpara();
    }


