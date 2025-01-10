#ifndef _APP_UDP_DATA_UNIT
#define _APP_UDP_DATA_UNIT
#include "lwip/UDP.h"
//#pragma pack (4)
#include <stm32f4xx.h>
#include <..\app\Sci.h>

#if 0
typedef struct
     {
	   u8    Type;              //协议类型    0  控制命令内    1 数据采集类
	   u8    Cmd;               //命令                    
     u8    CollectingMode;         //0 巡回采集模式   1  指定通道采集模式
	   u8    SingleModeChanle;    //指定通道模式下时的通道值
	   float FreBegin;                   //起点频率
	   float FreUP;                        //步进频率
	   float UPNum;                      //步进次数
		 u8    Data[168];                  //采集数据
     u8    Nc[16];
} COMPACSTR;
#endif 

#pragma pack (1)
struct	SFrameData
{
	int	header;
	int	id	;
	int	frameLen	;
	int	framType	;//帧类型	1:设置远程服务器IP 2:读取数据
	int	checkSum	;
	char	data[200]	;
	int	trail	;
} ;
int	getSFrameDataCrcLen();

enum	{
        eFrameNone      ,//0
				eFrameSetCommunicateParam,	//1
				eFrameStartRead ,//2
        eFrameStopRead  ,//3
        eFrameSetParam	,//4
        eFrameGetParam	,//5
        eFrameSendData	,//6
	};

//通讯参数配置命令
enum    ECommunicateCmd
{
    eCommSetRemoateIP   ,
    eCommSetLocalIP     ,
    eCommSetSendCycle   ,
};

//通讯参数配置包
struct  SCommunicateParam
{
    int  cmd ;//通讯配置命令
    char  data[196];
};
	

struct	SAppIpAddress
{
	char ip[4];
	char gw[4];
	char mask[4];
	int	 port		;
};


struct	SAutoSendData
{
	u16_t	cycleTimeCount	;//s
	u16_t	cycleTimeSet		;//s
	struct udp_pcb *pcb		;
	struct ip_addr pcAddr	;
	struct pbuf *pudtBuf	;
	u16_t		pcPort				;
	u8			startSend			;

	struct		SFrameData	mFrame	;
	
	
};
#pragma pack ()

void	initMyUdpdata(void);
void	readFrame(struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port);
void	initAutoSendData(void);
u16 CRC16 ( u8 *puchMsg, u16 usDataLen );
void	autoSendDataToPc();
void	autoSendDataToPcNow(COMPACSTR * pSrcData);

extern	struct	SAppIpAddress	gRemoteIp	;
extern	struct	SAppIpAddress gLocalIp	;

extern	COMPACSTR	appDataToPc	;

extern	struct	SAutoSendData	autosenddata;




#endif 
