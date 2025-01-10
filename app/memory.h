#ifndef MEMORY
#define  MEMORY

#define  BaseFlashAddr       (0x08004000)        //第一扇区 可操作FLASH有16K  地址范围到 0x08008000 


#define  FLASHMEMNUM         15


typedef struct
   {
       u32  InitVal;                    // 此值不为0XAAAAAAAA时，就需要初始化参数
	float FreBegin;                 //0.1Hz~100kHz   起点频率   初始化为10K
	float FreUP;                      //0.1Hz~10Hz      步进频率   初始化为1
	float UPNum;                    //0~500              步进次数   初始化为10
	u16  PowerOffCnt;            //断电次数
	u16  NC2;
	float NC[10];
   }STORAGE;

extern STORAGE PerPara;    //保存参数
extern STORAGE SysPara;    //使用参数


void ParameterRecovery(void);
void WritePageParaData(void);


#endif

