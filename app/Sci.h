//###########################################################################


#ifndef DSP6713_SCI_H
#define DSP6713_SCI_H



#ifdef __cplusplus
extern "C" {
#endif


u16 halfRvertCRC (u8 *ptr,u16 len);
u16 crc16(u8 *data,u16 length);	//CRC16 通讯循环码校验程序
u8 CRC8(u8 *ptr, u8 len);




typedef struct
{
    u8  ReceivePacSign:1;     //收到数据包
}COMMUNICATIONCON;

extern COMMUNICATIONCON ComCon;

enum   {
	eCmdRead   ,
	eCmdWrite  ,
}    ;

enum    {
eTargetParam  ,//
eTargetData   ,//
};



#pragma pack (1)
typedef struct
     {
	   u8   Type;              //协议类型    0  控制命令内    1 数据采集类
	   u8   Cmd;               //命令                    
          u8    CollectingMode;         //0 巡回采集模式   1  指定通道采集模式
	   u8    SingleModeChanle;    //指定通道模式下时的通道值
	   float FreBegin;                   //起点频率
	   float FreUP;                        //步进频率
	   float UPNum;                      //步进次数
          u8    Data[168];                  //采集数据
          u8    Nc[16];
     }COMPACSTR;
#pragma pack ()


extern  COMPACSTR  ComRecPac;        //接收数据包
//extern  COMPACSTR  ComSendPac;      //上传数据包
extern	COMPACSTR  ComSendCmdPac;      //上传数据包


void FuncCommunication(void);
u16 ASCII_change(u8 Hex_input);
void	readSampleParam(void);


#endif  

//===========================================================================
// No more.
//===========================================================================
