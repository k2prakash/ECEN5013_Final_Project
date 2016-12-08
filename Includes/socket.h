/*
 * socket.h
 *
 *  Created on: Dec 6, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_SOCKET_H_
#define INCLUDES_SOCKET_H_

#include "wiznet.h"
#include "delay.h"
#include "string.h"
#include "cbuffer.h"
#include "log.h"
#include "uart.h"

#define MAX_BUF 512

void close(uint8_t sock);
void disconnect(uint8_t sock);
uint8_t socket(uint8_t sock,uint8_t eth_protocol,uint16_t tcp_port);
uint8_t listen(uint8_t sock);
uint16_t send(uint8_t sock,const uint8_t *buf,uint16_t buflen);
//uint16_t recv(uint8_t sock,uint8_t *buf,uint16_t buflen);
uint16_t recv(uint8_t sock,cbuffer * rxbuf, uint16_t buflen);
uint16_t recv_size(void);
int strindex(char *s,char *t);


#endif /* INCLUDES_SOCKET_H_ */
