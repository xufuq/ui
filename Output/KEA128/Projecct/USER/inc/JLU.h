/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*/

#ifndef __FREECAR_H__
#define __FREECAR_H__
#include "KEA128_uart.h"



void push(unsigned char adr,unsigned short date);
void uSendOnePage(void);
void push_head(unsigned int raw,unsigned int line);
void push_in_data(int byte_num,unsigned char *buf);
void push_end(void);






#endif 
