#include "includes.h"

USARTDATA     UsartData;
SEND485DATA  Send485Data;

/********************************************************/ 
//UART1
/********************************************************/
void USART1_Configuration(u32 BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    //Ê¹ÄÜ´®¿Ú1Ê±ÖÓ  PA9ºÍPA10Îª´®¿Ú1ËùÓÃ

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       //Êä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOA,&GPIO_InitStructure);  

	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //8Î»Êý¾ÝÎ»
	USART_InitStructure.USART_StopBits = USART_StopBits_1;              //
	USART_InitStructure.USART_Parity = USART_Parity_No ;               //ÎÞÆæÅ¼Ð£Ñé
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;        //½ûÖ¹Ó²¼þÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      //·¢ËÍ¡¢½ÓÊÜË«Ïà´«ÊäÄ£Ê½
	USART_Init(USART1, &USART_InitStructure);

	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);   //Ê¹ÄÜ·¢ËÍ
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //Ê¹ÄÜ½ÓÊÕ
	//USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);  //Ê¹ÄÜ½ÓÊÕ

	USART_Cmd(USART1, ENABLE);                         //Ê¹ÄÜUSART1
	USART_ClearFlag(USART1,USART_FLAG_TC);             //Çå±êÖ¾£¬½â¾öµÚ1¸ö×Ö½ÚÎÞ·¨ÕýÈ··¢ËÍ³öÈ¥µÄÎÊÌâ

	//-----Ê¹ÄÜ´®¿Ú1ÖÐ¶Ï-----
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void USART1_IRG_Handler(void)   
{
	  volatile u8  kkk;
		 
	  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)   //å¦‚æžœæ˜¯æŽ¥æ”¶ä¸­æ–­
	    {
		  
	      UsartData.RxBuffer1Ptr%=UsartBufferSize1;
	      UsartData.RxBuffer1[UsartData.RxBuffer1Ptr++]=USART_ReceiveData(USART1);;
 	   }
	  else if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
		{
		 USART_SendData(USART1,UsartData.TxBuffer1[UsartData.TxBuffer1Ptr++]);
		 if(UsartData.TxBuffer1Ptr>UsartData.TxBuffer1Num)
		    {
                     USART_ITConfig(USART1,USART_IT_TXE,DISABLE);    
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);    
			UsartData.TxBuffer1Ptr=0;
			UsartData.TxBuffer1Num=0;
		    }	
	       }

        if (USART_GetITStatus(USART1, USART_IT_ORE) == SET)
        	{
		  USART_ClearFlag(USART1,USART_IT_ORE); 
		  USART_ClearITPendingBit(USART1,USART_IT_ORE);   
		  USART_ReceiveData( USART1);
        	}
        
        if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)
        	{
        	  kkk=USART_ReceiveData(USART1);
		  USART_ClearFlag(USART1,USART_IT_IDLE); 
		  UsartData.RxFinish1=1;
        	}

        if(USART_GetITStatus(USART1,USART_IT_ERR)!=RESET)
           {
        	  kkk=USART_ReceiveData(USART1);
		  USART_ClearFlag(USART1,USART_IT_ERR);            
	     }
	}


//--------------------------------------------------------------------
void Usart1SendSubFunc(u8 Len)
	{
	 memset(UsartData.RxBuffer1,0,50);
        UsartData.TxBuffer1Num = Len;
	 //memcpy(UsartData.TxBuffer1,Send485Data.Data,UsartData.TxBuffer1Num);
	 UsartData.TxBuffer1Ptr = 0;
	 UsartData.RxBuffer1Ptr = 0;
	 USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
	}



/********************************************************/ 
//UART2
/********************************************************/
void USART2_Configuration(u32 BaudRate)
	{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
         NVIC_InitTypeDef NVIC_InitStructure;

        /*USART2 */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    //ä½¿èƒ½ä¸²å£1æ—¶é’Ÿ  PA9å’ŒPA10ä¸ºä¸²å£1æ‰€ç”¨

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
         GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	   
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
         GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
     	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

	 
	 USART_InitStructure.USART_BaudRate                   = BaudRate;    //é€šè®¯é€ŸçŽ‡
	 USART_InitStructure.USART_WordLength               = USART_WordLength_9b;//8ä½æ•°æ®ä½
	 USART_InitStructure.USART_StopBits                    = USART_StopBits_1;   //
	 USART_InitStructure.USART_Parity                       = USART_Parity_Even ;//æ— å¥‡å¶æ ¡éªŒ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ç¦æ­¢ç¡¬ä»¶æµæŽ§åˆ¶
	 USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //å‘é€ã€æŽ¥å—åŒç›¸ä¼ è¾“æ¨¡å¼
	 USART_Init(USART2, &USART_InitStructure);	  
	 
 	 USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);        //ä½¿èƒ½æŽ¥æ”¶ä¸­æ–­*/
	 USART_ITConfig(USART2, USART_IT_TXE,DISABLE);         //ä½¿èƒ½æŽ¥æ”¶ä¸­æ–­
	 USART_ITConfig(USART2, USART_IT_IDLE,ENABLE);         //ä½¿èƒ½æŽ¥æ”¶ä¸­æ–­
       //USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);   //ä½¿èƒ½ä¼‘é—²ä¸­æ–­
	 
	 USART_Cmd(USART2, ENABLE); 					  //ä½¿èƒ½UART2
	 USART_ClearFlag(USART2,USART_FLAG_TC);       //æ¸…æ ‡å¿—ï¼Œè§£å†³ç¬¬1ä¸ªå­—èŠ‚æ— æ³•æ­£ç¡®å‘é€å‡ºåŽ»çš„é—®é¢˜
	 //memset(UsartData.RxBuffer2,0,UsartBufferSize2);
	 //memset(UsartData.TxBuffer2,0,100);

/**/	  //-----ä½¿èƒ½ä¸²å£2ä¸­æ–­-----
	 NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_Init(&NVIC_InitStructure);  
  }

/********************************************************/
//--------------USART2 ZÖá------------------------------
/********************************************************/
void USART2_IRG_Handler(void)   
	{
	  volatile u8  kkk;
		 
	  if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)   //å¦‚æžœæ˜¯æŽ¥æ”¶ä¸­æ–­
	    {
		  
	      UsartData.RxBuffer2Ptr%=UsartBufferSize2;
	      UsartData.RxBuffer2[UsartData.RxBuffer2Ptr++]=USART_ReceiveData(USART2);;
 	   }
	  else if(USART_GetITStatus(USART2,USART_IT_TXE)!=RESET)
		{
		 USART_SendData(USART2,UsartData.TxBuffer2[UsartData.TxBuffer2Ptr++]);
		 if(UsartData.TxBuffer2Ptr>UsartData.TxBuffer2Num)
		    {
		       //SoftDelayms(2);
                     USART_ITConfig(USART2,USART_IT_TXE,DISABLE);    
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);    
			UsartData.TxBuffer2Ptr=0;
			UsartData.TxBuffer2Num=0;
		    }	
	       }

        if (USART_GetITStatus(USART2, USART_IT_ORE) == SET)
        	{
		  USART_ClearFlag(USART2,USART_IT_ORE); 
		  USART_ClearITPendingBit(USART2,USART_IT_ORE);   
		  USART_ReceiveData( USART2);
        	}
        
        if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)
        	{
        	  kkk=USART_ReceiveData(USART2);
		  USART_ClearFlag(USART2,USART_IT_IDLE); 
		  UsartData.RxFinish2=1;
        	}

        if(USART_GetITStatus(USART2,USART_IT_ERR)!=RESET)
           {
        	  kkk=USART_ReceiveData(USART2);
		  USART_ClearFlag(USART2,USART_IT_ERR);            
	     }
	}


//--------------------------------------------------------------------
void Usart2SendSubFunc(u8 Len)
	{
	 memset(UsartData.RxBuffer2,0,50);
        UsartData.TxBuffer2Num = Len;
	 memcpy(UsartData.TxBuffer2,Send485Data.Data,UsartData.TxBuffer2Num);
	 UsartData.TxBuffer2Ptr = 0;
	 UsartData.RxBuffer2Ptr = 0;
	 USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
	}


