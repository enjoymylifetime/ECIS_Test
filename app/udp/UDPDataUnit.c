#include "UDPDataUnit.h"
#include "..\app\Sci.h"

#include<string.h>
#include "ucos_ii.h"

struct	SAppIpAddress	gRemoteIp	;
struct	SAppIpAddress gLocalIp	;

struct	SFrameData	udpData;	
static	int	lcMsgID	= 0;

COMPACSTR	appDataToPc		;

struct	SAutoSendData	autosenddata;

u8 readIPAddr4FromDip();

int	getSFrameDataCrcLen()
{
	return 16;
	
}


void	initAutoSendData()
{
	autosenddata.pcAddr.addr	= 0;
	autosenddata.cycleTimeCount	= 0;
	autosenddata.cycleTimeSet	= 1;
	
	autosenddata.pcb	= NULL	;
	autosenddata.startSend = 0;
	autosenddata.pcPort	= 0;
	

	autosenddata.pudtBuf = NULL;
	//autosenddata.pudtBuf = pbuf_alloc(PBUF_RAW,sizeof(autosenddata.mFrame),PBUF_RAM);
	//autosenddata.pudtBuf -> payload = (void *)&autosenddata.mFrame;
	
}

void	makeTestFrame(void);


void	initMyUdpdata(void)
{
	gRemoteIp.ip[0] = 192	;
	gRemoteIp.ip[1] = 168	;
	gRemoteIp.ip[2] = 5		;
	gRemoteIp.ip[3] = 100	;

	gRemoteIp.mask[0] = 255	;
	gRemoteIp.mask[1] = 255	;
	gRemoteIp.mask[2] = 255	;
	gRemoteIp.mask[3] = 0	;

	gRemoteIp.port = 1030;

	gLocalIp.ip[0] = 192	;
	gLocalIp.ip[1] = 168	;
	gLocalIp.ip[2] = 5		;
	gLocalIp.ip[3] = readIPAddr4FromDip()	;

	gLocalIp.mask[0] = 255	;
	gLocalIp.mask[1] = 255	;
	gLocalIp.mask[2] = 255	;
	gLocalIp.mask[3] = 0	;

	gLocalIp.gw[0] = 192	;
	gLocalIp.gw[1] = 168	;
	gLocalIp.gw[2] = 5		;
	gLocalIp.gw[3] = 1		;

	gRemoteIp.port = 1031;

	makeTestFrame();
}


void	makeTestFrame()
{
	int	i	=0;
	udpData.header	= 0x55aaaa55;
	for( i=0; i<sizeof(udpData.data);i++)
	{
		udpData.data[i]	= i	;
	}
	
	udpData.trail = 0xaa5555aa	;
	udpData.frameLen	= sizeof(udpData);


	udpData.id	= lcMsgID++;
	udpData.checkSum	= CRC16((u8*)&udpData,getSFrameDataCrcLen())	;
	
}

void	initUdpFrame(struct	SFrameData *pFrame,u8 type)
{
	pFrame->header	= 0x55aaaa55;
	memset(pFrame->data,0,sizeof(pFrame->data));
	pFrame->trail = 0xaa5555aa	;
	pFrame->frameLen	= sizeof(udpData);
	pFrame->framType = type;

	pFrame->id	= lcMsgID++;
	pFrame->checkSum	= CRC16((u8*)pFrame,getSFrameDataCrcLen())	;
}


void	makeAckFrame(struct	SFrameData * psrc,struct	SFrameData * pAck,int result)
{
	int	i	=0;
	//struct	SFrameData	srcData ;
	//memcpy(&srcData,psrc,sizeof(srcData));
	memset(pAck,0,sizeof(struct	SFrameData));
	pAck->header	= 0x55aaaa55;
	pAck->id	= psrc->id	;
	pAck->framType = psrc->framType	;
	if (0 == result)
		{
		pAck->data[0]	= 'O';
		pAck->data[1]	= 'K';
		}
	else
		{	
		pAck->data[0]	= 'E';
		pAck->data[1]	= 'R';
		pAck->data[2]	= 'R';
		pAck->data[3]	= 'O';
		pAck->data[4]	= 'R';
		
		*(int*)(pAck->data+10) = result;
		}

	pAck->trail = 0xaa5555aa	;
	pAck->frameLen	= sizeof(struct	SFrameData);
	pAck->checkSum	= CRC16( (u8*)pAck,getSFrameDataCrcLen())	;

	
}


void setCommunicateParam(struct	SFrameData * psrc,struct	SFrameData	*pAck  )
{
	
	struct SCommunicateParam	*pCommData = (struct SCommunicateParam	*)psrc->data;
	
	makeAckFrame( psrc,pAck, 0);
	
	
	switch(pCommData->cmd)
	{
    case eCommSetRemoateIP   :
			gRemoteIp.ip[0] = pCommData->data[0];
			gRemoteIp.ip[1] = pCommData->data[1];
			gRemoteIp.ip[2] = pCommData->data[2];
			gRemoteIp.ip[3] = pCommData->data[3];
			gRemoteIp.mask[0] = pCommData->data[4];
			gRemoteIp.mask[1] = pCommData->data[5];
			gRemoteIp.mask[2] = pCommData->data[6];
			gRemoteIp.mask[3] = pCommData->data[7];			
			break;
    case eCommSetLocalIP     :
			gLocalIp.ip[0] = pCommData->data[0];
			gLocalIp.ip[1] = pCommData->data[1];
			gLocalIp.ip[2] = pCommData->data[2];
			gLocalIp.ip[3] = pCommData->data[3];
			gLocalIp.mask[0] = pCommData->data[4];
			gLocalIp.mask[1] = pCommData->data[5];
			gLocalIp.mask[2] = pCommData->data[6];
			gLocalIp.mask[3] = pCommData->data[7];
			gLocalIp.gw[0]   = pCommData->data[8];
			gLocalIp.gw[1]   = pCommData->data[9];
			gLocalIp.gw[2]   = pCommData->data[10];
			gLocalIp.gw[3]   = pCommData->data[11];
			break;
    case eCommSetSendCycle   :
			autosenddata.cycleTimeSet = *(int*)pCommData->data;
			break;
	}
}

void	readData(struct	SFrameData * psrc,struct	SFrameData	*pAck  )
{
	int i=0; 
	struct	SFrameData	srcData ;
	memcpy(&srcData,psrc,sizeof(srcData));
	
	memset(pAck,0,sizeof(struct	SFrameData));
	pAck->header	= 0x55aaaa55;

	for (i=0; i<200; i++)
		{
			pAck->data[i] = i;
		}
	pAck->id = srcData.id;
	pAck->framType = srcData.framType	;
	pAck->trail = 0xaa5555aa	;
	pAck->frameLen	= sizeof(struct	SFrameData);
	pAck->checkSum	= CRC16( (u8*)pAck,getSFrameDataCrcLen())	;
	
	//	
	memcpy(pAck->data,&appDataToPc,sizeof(appDataToPc));
	
}



void	setParam(struct SFrameData * psrc,struct	SFrameData	*pAck  )
{
	
	
	int i=0; 
	COMPACSTR *pUserData =  (COMPACSTR * )psrc->data ;
	if ( (eCmdWrite == pUserData->Cmd) && (eTargetParam == pUserData->Type))
	{
		ComRecPac = *(COMPACSTR * )psrc->data ;
	}
	//返回帧
	memset(pAck,0,sizeof(struct	SFrameData));
	pAck->header	= 0x55aaaa55;
	pAck->data[0]	= 'O';
	pAck->data[1]	= 'K';
	

	pAck->id = psrc->id;
	pAck->framType = psrc->framType	;
	pAck->trail = 0xaa5555aa	;
	pAck->frameLen	= sizeof(struct	SFrameData);
	pAck->checkSum	= CRC16( (u8*)pAck,getSFrameDataCrcLen())	;
}


int	checkFrame(char* p )
{
	//int  fls = sizeof(struct	SFrameData);
	struct	SFrameData *pFrame = (struct	SFrameData *)p ;
	return 	(0x55aaaa55 == pFrame->header ) && (0xaa5555aa == pFrame->trail) 
				&& (pFrame->frameLen	== sizeof(struct	SFrameData));
}


void	copyDataToSendBuff(COMPACSTR * pSrcData)
{
		memcpy(&appDataToPc,pSrcData,sizeof(appDataToPc));	
}

void	autoSendDataToPcNow(COMPACSTR * pSrcData)
{
	//OS_CPU_SR cpu_sr=0;
	err_t udpErr = 0;
	struct pbuf udpBuf;
	if (0 == autosenddata.startSend)
		return	;
	if (NULL == autosenddata.pcb)
		return;
	
	if (++autosenddata.cycleTimeCount 	 < autosenddata.cycleTimeSet) return ;
	
	autosenddata.cycleTimeCount = 0;
	initUdpFrame(&autosenddata.mFrame,eFrameSendData);
	
	struct pbuf *pudtBuf = pbuf_alloc(PBUF_RAW,sizeof(autosenddata.mFrame),PBUF_RAM);
	pudtBuf-> payload = (void *)&autosenddata.mFrame;
	
	memcpy(autosenddata.mFrame.data,pSrcData,sizeof(COMPACSTR));
	//OS_ENTER_CRITICAL();
	udpErr = udp_sendto(autosenddata.pcb,pudtBuf,&autosenddata.pcAddr,autosenddata.pcPort); /* 将收到的数据再发送出去 */	
	pbuf_free(pudtBuf);
	//OS_EXIT_CRITICAL();
	
	
}


void	autoSendDataToPc()
{
	//OS_CPU_SR cpu_sr=0;
	err_t udpErr = 0;
	struct pbuf udpBuf;
	if (0 == autosenddata.startSend)
		return	;
	if (NULL == autosenddata.pcb)
		return;
	
	if (++autosenddata.cycleTimeCount 	 < autosenddata.cycleTimeSet) return ;
	
	autosenddata.cycleTimeCount = 0;
	initUdpFrame(&autosenddata.mFrame,eFrameSendData);
	
	struct pbuf *pudtBuf = pbuf_alloc(PBUF_RAW,sizeof(autosenddata.mFrame),PBUF_RAM);
	pudtBuf-> payload = (void *)&autosenddata.mFrame;
	
	memcpy(autosenddata.mFrame.data,&appDataToPc,sizeof(appDataToPc));
	//OS_ENTER_CRITICAL();
	udpErr = udp_sendto(autosenddata.pcb,pudtBuf,&autosenddata.pcAddr,autosenddata.pcPort); /* 将收到的数据再发送出去 */	
	pbuf_free(pudtBuf);
	//OS_EXIT_CRITICAL();
	
	
}

//1:set auto sample data ,0:not send 
int	doReadCmd(struct SFrameData * psrc,struct	SFrameData	*pAck)
{
	int	rev=  0 ;
	COMPACSTR	sampleCmd = *(COMPACSTR * )psrc->data ;
	
	if (eTargetParam == sampleCmd.Type)
	{//read param
		
		if (eCmdRead == sampleCmd.Cmd)
		{
			ComRecPac.Type = eTargetParam;
			ComRecPac.Cmd = eCmdRead;
			readSampleParam();
			memcpy(pAck->data,&ComSendCmdPac,sizeof(ComSendCmdPac));
			rev	= 0;
		}
	}
	else
	{
		ComRecPac.Type = eTargetData;
		ComRecPac.Cmd = eCmdRead;
		memcpy(pAck->data,&sampleCmd,sizeof(sampleCmd));
		rev	= 1;
	}
	//memset(pAck,0,sizeof(struct	SFrameData));
	

	pAck->header	= 0x55aaaa55;
	pAck->id = psrc->id;
	pAck->framType = psrc->framType	;
	pAck->trail = 0xaa5555aa	;
	pAck->frameLen	= sizeof(struct	SFrameData);
	pAck->checkSum	= CRC16( (u8*)pAck,getSFrameDataCrcLen())	;

	return rev; 
}

void	readFrame(struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	//OS_CPU_SR cpu_sr=0;

	struct	SFrameData	ackFrame	;
	struct ip_addr destAddr = *addr; /* 获取远程主机 IP地址 */
	struct pbuf *p_temp = p;
	struct	SFrameData	*psrcFrame = (struct	SFrameData	*)p_temp->payload;
	err_t udpErr = 0;
	if (!checkFrame(p->payload))
		return ;


	switch (psrcFrame->framType)
		{ 
			case eFrameSetCommunicateParam:
				setCommunicateParam(psrcFrame,&ackFrame);
				memcpy(p->payload,&ackFrame,sizeof(ackFrame));
				//OS_ENTER_CRITICAL();
				udpErr = udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */	
				//OS_EXIT_CRITICAL();
				break;
			
			case eFrameSendData	://7
				break;
			
			case eFrameStartRead:
				if (0 != doReadCmd(psrcFrame,&ackFrame))
				{
					autosenddata.pcb	= pcb;
					autosenddata.pcAddr.addr = destAddr.addr;
					autosenddata.pcPort	= port;
					autosenddata.startSend	= 1	;					
				}
					
				
				//makeAckFrame(psrcFrame,&ackFrame,0);
				memcpy(p->payload,&ackFrame,sizeof(ackFrame));
				//OS_ENTER_CRITICAL();

				udpErr = udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */	
				//OS_EXIT_CRITICAL();
				break;
			
			case eFrameStopRead:
				makeAckFrame(psrcFrame,&ackFrame,0);
				memcpy(p->payload,&ackFrame,sizeof(ackFrame));
				//OS_ENTER_CRITICAL();
				autosenddata.pcb	= NULL;
				autosenddata.startSend	= 0	;
				udpErr = udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */	
				//OS_EXIT_CRITICAL();
				break;
			
			case eFrameSetParam:
				setParam(psrcFrame,&ackFrame);
				//makeAckFrame(psrcFrame,&ackFrame,0);
				memcpy(p->payload,&ackFrame,sizeof(ackFrame));
				//OS_ENTER_CRITICAL();
				udpErr = udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */	
				//OS_EXIT_CRITICAL();
				break;
			
			case eFrameGetParam:
				break;
 				
		}
	
		//autoSendDataToPc();//
}


/*********************************
 read the segment 4 of ip from switcher
*********************************/
u8 readIPAddr4FromDip()
{
	u8	addv = 201;
		return addv;
}

