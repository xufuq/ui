/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*/

#include "JLU.h"

unsigned char uSendBuf[32]={0};

/*
* 向16个数据通道压入待发送数据
* adr:数据通道序号；date：待发送数据
* adr:0~15;         date:-32768~32767
*/
void push(unsigned char adr,unsigned short date)
{
  uSendBuf[adr*2]=date/256;
  uSendBuf[adr*2+1]=date%256;
}

/*
* 示波器功能专用函数
* push压入待发送数据后执行此函数
* 图像显示功能不需要
*/
void uSendOnePage(void)
{
  unsigned char i; 
  uart_putchar(uart2,255);
  uart_putchar(uart2,37);
  for(i=0;i<16;i++)
  {
    uart_putchar(uart2, uSendBuf[i*2]);
    uart_putchar(uart2, uSendBuf[i*2+1]);
  }
  uart_putchar(uart2,37);
  uart_putchar(uart2,255);
  
}

/*
* 图像显示功能专用函数
* 可发送灰度图像和二值图像两个种
* 灰度图像一个字节存1个像素
* 二值图像一个字节存8个像素
* 在发送一帧图像之前先执行此函数
* raw ：此次发送图像行数，最大为320，即每列最多像素点数
* line：此次发送图像列数，最大为240，即每行最多像素点数
*/
void push_head(unsigned int raw,unsigned int line)
{
  uart_putchar(uart2,255);
  uart_putchar(uart2,37);
  uart_putchar(uart2,(unsigned char)((raw/10)&0xff));
  uart_putchar(uart2,(unsigned char)((line/10)&0xff));
  for(int i=0;i<32;i++)
  {
      uart_putchar(uart2,uSendBuf[i]);
  }
}

/*
* 图像显示功能专用函数
* 按照需求将图像数据依次压入发送序列
* byte_num:此次发送的字节数
* buf     :无符号字符型数组，最大容量不能超过256
*/
void push_in_data(int byte_num,unsigned char *buf)
{
  for(int i=0;i<byte_num;i++)
    {
        uart_putchar(uart2,(buf[i]&0xff));
    } 
}

/*
* 图像显示功能专用函数
* 在发送完成一帧图像后执行此函数
*/
void push_end(void)
{
  uart_putchar(uart2,37);  
  uart_putchar(uart2,255);
}
