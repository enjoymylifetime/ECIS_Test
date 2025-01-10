#ifndef __USART_h_
#define __USART_h_

#define  UsartBufferSize1      100
#define  UsartBufferSize2      100
#define  UsartBufferSize3      100
#define  UsartBufferSize4      100
#define  UsartBufferSize5      100
#define  UsartBufferSize6      100


typedef struct
{
   u8  RxBuffer1[UsartBufferSize1+1];    //å¤šæ”¾ä¸€ä¸ªé˜²æ­¢æº¢å‡º
   u8  TxBuffer1[UsartBufferSize1+1];
   u16 RxBuffer1Ptr;
   u16 TxBuffer1Ptr;
   u32 RxBuffer1Num;
   u8   TxBuffer1Num;
   u8   RxFinish1;              //æŽ¥æ”¶å®Œæˆæ ‡å¿—
   u8   WaitRecTime1;       //·¢ËÍÒÔºóµÈ´ý»Ø°ü
   u32 SendNum;
   u32 SuccessNum;
   u32 FailNum;
   
   u8 RxBuffer2[UsartBufferSize1+1];    //å¤šæ”¾ä¸€ä¸ªé˜²æ­¢æº¢å‡º
   u8 TxBuffer2[UsartBufferSize1+1];
   u16 RxBuffer2Ptr;
   u16 TxBuffer2Ptr;
   u32 RxBuffer2Num;
   u8 TxBuffer2Num;
   u8 RxFinish2;          //æŽ¥æ”¶å®Œæˆæ ‡å¿—
   
   u8 RxBuffer3[UsartBufferSize3+1];
   u8 TxBuffer3[UsartBufferSize3+1];
   u8 RxBuffer3Ptr;
   u8 TxBuffer3Ptr;
   u8 RxBuffer3Num;
   u8 TxBuffer3Num;
   u8 RxFinish3;      //0æŽ¥æ”¶æœªå®Œæˆ  å¦åˆ™ï¼ŒæŽ¥æ”¶å®Œæˆ

   u8 RxBuffer4[UsartBufferSize4+1];
   u8 TxBuffer4[UsartBufferSize4+1];  //·ÀÖ¹Òç³ö
   u8 RxBuffer4Ptr;
   u8 TxBuffer4Ptr;
   u8 RxBuffer4Num;
   u8 TxBuffer4Num;
   u8 RxFinish4;                 //0æŽ¥æ”¶æœªå®Œæˆ  å¦åˆ™ï¼ŒæŽ¥æ”¶å®Œæˆ

   u8 RxBuffer5[UsartBufferSize4+1];
   u8 TxBuffer5[UsartBufferSize4+1];  //·ÀÖ¹Òç³ö
   u8 RxBuffer5Ptr;
   u8 TxBuffer5Ptr;
   u8 RxBuffer5Num;
   u8 TxBuffer5Num;
   u8 RxFinish5;                 //0æŽ¥æ”¶æœªå®Œæˆ  å¦åˆ™ï¼ŒæŽ¥æ”¶å®Œæˆ

   u8 RxBuffer6[UsartBufferSize1+1];    //å¤šæ”¾ä¸€ä¸ªé˜²æ­¢æº¢å‡º
   u8 TxBuffer6[UsartBufferSize1+1];
   u16 RxBuffer6Ptr;
   u16 TxBuffer6Ptr;
   u32 RxBuffer6Num;
   u8 TxBuffer6Num;
   u8 RxFinish6;          //æŽ¥æ”¶å®Œæˆæ ‡å¿—

   u16 ComInterTime;          //>10±íÊ¾Í¨Ñ¶ÖÐ¶Ï
   u32  LcdRecDataTime;       //´Ó´¥ÃþÆÁ×îºó½ÓÊÕµ½Ò»¸öÍêÕûÊý¾Ý°ü
   u32  LcdSendDataTime;    // ×îºóÒ»´Î·¢ËÍÊý¾Ý

   u32  LcdRstTime;

}USARTDATA;

extern USARTDATA UsartData;

typedef struct
{
   u8  HeartBeat:1;
   u8  RunState:1;
   u8  SaveState:1;
   u8  PowerOffTime:5;
}STATADATABIT;

typedef union
{
  STATADATABIT bit;
  u8                    val;
}STATE1DATA;


typedef struct
{
  u8   			Head;
  u8   			Id;
  STATE1DATA   	State1;
  u8 			       SaveCntL;
  u8                       SaveCntH;
  u8   			Tail;
}SEND485DATABIT;

typedef union
{
  SEND485DATABIT Bit;
  u8                        Data[6];
}SEND485DATA;



extern SEND485DATA  Send485Data;


void USART1_Configuration(u32 BaudRate);
extern void USART1_IRG_Handler(void);   
void Usart2SendSubFunc(u8 Len);

#endif


