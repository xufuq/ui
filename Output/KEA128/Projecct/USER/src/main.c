/*
*   author   : Fuqiang Xu
*   Done date: 2018-11-27
*   e-mail   : 17843124829@163.com
*   由于本人水平有限，数据发送频率不宜过大，20hz以内较好，否则造成数据卡顿
*/
#include "headfile.h"
#include "JLU.h"




uint32 baud;
int jj=0;



int main(void)
{
    get_clk();              //获取时钟频率 必须执行
    baud=uart_init(uart2,115200);
    
    
/*
*  电磁组数据发送例程    
*/
    /*
    while(1)
    {
        for(int i=0;i<16;i++)
        {
            jj=jj+100;
            push(i,jj);
        }
        if(jj>20000)
            jj=-20000;
        uSendOnePage();
        systick_delay_ms(20);
    }
    */
    
/*
*  摄像头组数据图像发送例程  
*/
    
    unsigned char picture=0;
    
    for(int i=0;i<16;i++)
    {
        push(i,1000*i);
    }
    while(1)
    {
        
        unsigned char buffer[8]={picture,picture+1,picture+2,picture+3,picture+4,picture+5,picture+6,picture+7};
        push_head(200,160);     
        for(int i=0;i<25;i++)
        {
            for(int j=0;j<20;j++)
            {
               push_in_data(8,buffer);            
            }
        }
        push_end();
        systick_delay_ms(50);
        picture+=8;
    }
    
}
