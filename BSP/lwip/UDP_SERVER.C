//#include "main.h"
#include "lwip/arch.h"
#include "UDPDataUnit.h"
#include "tcpAddressDefine.h"


//#include "lwip/api.h"
//#include "lwip/tcpip.h"
//#include "lwip/memp.h"

//#include "lwip/ip.h"
//#include "lwip/raw.h"
//#include "lwip/udp.h"
//#include "lwip/tcp.h"


/***********************************************************************
函数名称：udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
功    能：udp数据接收和发送
注    意：这是一个回调函数，当一个udp段到达这个连接时会被调用
***********************************************************************/
void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	struct ip_addr destAddr = *addr; /* 获取远程主机 IP地址 */
	struct pbuf *p_temp = p;
	//while(p_temp != NULL)
	{//>+ ice   UDP  的数据处理函数

		readFrame(pcb,p,addr,port);
		/******将数据原样返回*******************/
		//udp_sendto(pcb,p_temp,&destAddr,port); /* 将收到的数据再发送出去 */	
		
	}
	pbuf_free(p); 						/* 释放该UDP段 */
}


/***********************************************************************
函数名称：UDP_server_init(void)
功    能：完成UDP服务器的初始化，主要是使得UDP通讯快进入监听状态
***********************************************************************/
void UDP_server_init(void)
{
	struct udp_pcb *pcb;
	pcb = udp_new();								//申请udp控制块
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT); 	    /* 绑定本地IP地址和端口号（作为udp服务器） */
	udp_recv(pcb,udp_server_recv,NULL); 				/* 设置UDP段到时的回调函数 */

}
