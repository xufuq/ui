/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		NRF24L01
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 * @note	
					接线定义
					------------------------------------ 
					    模块管脚       	单片机管脚
					    CCD_AO	   		查看SEEKFREE_TSL1401文件内的AD_CHANNEL2   宏定义
                        CCD_AO	   		查看SEEKFREE_TSL1401文件内的AD_CHANNEL1   宏定义
					    CCD_CLK	   		查看SEEKFREE_TSL1401文件内的CCD_CLK_PORT  宏定义
					    CCD_SI	   		查看SEEKFREE_TSL1401文件内的CCD_SI_PORT   宏定义
					------------------------------------ 
 ********************************************************************************************************************/



#include "SEEKFREE_TSL1401.h"




#define CCD_CLK_PORT   B1                     	//CCD CLK引脚定义
#define CCD_SI_PORT    B0                     	//CCD SI 引脚定义
#define AD_CHANNEL1    ADC0_SE6                 //定义CCD1 AD采集通道  B2
#define AD_CHANNEL2    ADC0_SE7                 //定义CCD2 AD采集通道  B3
#define EXPOSURE_TIME  10                       //定义CCD曝光时间 单位MS



#define CCD_CLK(x)     gpio_set (CCD_CLK_PORT, x)
#define CCD_SI(x)      gpio_set (CCD_SI_PORT,  x)


uint16 ccd_data1[128];                           //CCD1数据
uint16 ccd_data2[128];                           //CCD2数据

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void ccd_init(void)     
{       
    adc_init (AD_CHANNEL1);                     //B2
    adc_init (AD_CHANNEL2);                     //B3
    gpio_init(CCD_CLK_PORT, GPO, 1);            //CLK
    gpio_init(CCD_SI_PORT,  GPO, 1);            //SI
    
    DisableInterrupts;
    pit_init_ms(pit0, EXPOSURE_TIME);   		//定时EXPOSURE_TIME(ms) 后中断
    set_irq_priority(PIT_CH0_IRQn,1);			//设置优先级,根据自己的需求设置 可设置范围为 0 - 3  越小优先级越高
    enable_irq(PIT_CH0_IRQn);                   //使能PIT0中断
    EnableInterrupts;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD数据采集
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void ccd_collect(void)
{
    uint16 i = 0;

 
    CCD_CLK(1);
    CCD_SI(0);
    

    CCD_SI(1);
    CCD_CLK(0);
    

    CCD_CLK(1);
    CCD_SI(0);
    
    
    for(i=0;i<128;i++)
    {
        CCD_CLK(0);   
        ccd_data1[i] = adc_once(AD_CHANNEL1, ADC_12bit);     
        ccd_data2[i] = adc_once(AD_CHANNEL2, ADC_12bit);    
        CCD_CLK(1);
    }
}
