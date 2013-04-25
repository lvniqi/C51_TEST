/*
* AD PCF8591
*
* 旋转电位器，串口助手将收到不同的数据
*/
#include <reg52.h>
#include <intrins.h>
#include "normal.h"
#include "led_4.h"
#include "Iic.h"
typedef unsigned char uint8;
typedef unsigned int uint16;

#define SLAVEADDR  0x90
#define nops()  do{_nop_();_nop_();_nop_();_nop_();_nop_();} while(0) //定义空指令


//sbit SCL = P2^6;       //I2C  时钟 
//sbit SDA = P2^7;       //I2C  数据 
uint8 timer=0;
/**
* 函数: i2c_start()
* 功能: 启动i2c
*/
void i2c_start()
{
        SCL = 1;
        nops();
        SDA = 1;
        nops();
        SDA = 0;
        nops();
        SCL = 0;
}

/**
* 函数: i2c_stop()
* 功能: 停止i2c
*/
void i2c_stop()
{
        SCL = 0;
        nops();
        SDA = 0;
        nops();
        SCL = 1;
        nops();
        SDA = 1;
        nops();
}

/**
* 函数: i2c_ACK(bit ck)
* 功能: ck为1时发送应答信号ACK,
*       ck为0时不发送ACK
*/
void i2c_ACK(bit ck)
{
    if (ck)
                SDA = 0;
    else
                SDA = 1;
    nops();
    SCL = 1;
    nops();
    SCL = 0;
        nops();
    SDA = 1;
    nops();
}

/**
* 函数: i2c_waitACK()
* 功能: 返回为0时收到ACK
*       返回为1时没收到ACK
*/
bit i2c_waitACK()
{
        SDA = 1;
        nops();
        SCL = 1;
        nops();
        if (SDA)
        {   
                SCL = 0;
                i2c_stop();
                return 1;
        }
        else
        {  
                SCL = 0;
                return 0;
        }
}

/**
* 函数: i2c_sendbyte(uint8 bt)
* 功能: 将输入的一字节数据bt发送
*/
void i2c_sendbyte(uint8 bt)
{
    uint8 i;
    
    for(i=0; i<8; i++)
    {  
        if (bt & 0x80) 
                        SDA = 1;
        else 
                        SDA = 0;
        nops();
        SCL = 1;
        bt <<= 1;
        nops();       
        SCL = 0;
    }
}

/**
* 函数: i2c_recbyte( )
* 功能: 从总线上接收1字节数据
*/
uint8 i2c_recbyte()
{
        uint8 dee, i;
        
        for (i=0; i<8; i++)
        {
                SCL = 1;    
                nops();
                dee <<= 1;
                if (SDA) 
                        dee = dee | 0x01;
                SCL = 0;
                nops();
        }
        
        return dee;
}

/**
* 函数: i2c_readbyte
* 输入: addr
* 功能: 读出一字节数据
* 返回值: 0->成功  1->失败
*/
bit i2c_readbyte(uint8 com, uint8 *dat)
{        
        i2c_start();
        i2c_sendbyte(SLAVEADDR);    //地址
    if (i2c_waitACK())
                return 1;
        i2c_sendbyte(com);        //控制字节
    if (i2c_waitACK())
                return 1;
        i2c_start();
        i2c_sendbyte(SLAVEADDR+1); //地址
    if (i2c_waitACK())
                return 1;
        *dat = i2c_recbyte();      //读数据
        i2c_ACK(0);                //因为只读一字节数据，不发送ACK信号
        i2c_stop();   
        
        return 0;
}

/**
* UART初始化
* 波特率：9600
*/
void uart_init(void)
{
    ET1=0;
    TMOD = 0x21;        // 定时器1工作在方式2（自动重装）
    SCON = 0x50;        // 10位uart，允许串行接受

    TH1 = 0xFD;
    TL1 = 0xFD;

    TR1 = 1;
}

/**
* UART 发送一字节
*/
void UART_Send_Byte(uint8 dat)
{
        SBUF = dat;
        while (TI == 0);
        TI = 0;
}
void set_timer(void)
{
	RCAP2H=19456/256;
	RCAP2L=19456%256;
	ET2=1;          //开定时器2中断
	TR2=1;          //开启定时器，并设置为自动重装载模式
	EA=1;
}
void Timer_ET2_50ms() interrupt 5//延时50ms
{
	TF2=0;
	timer++;
}

main()
{
        uint8 ans;
		set_timer();
        uart_init();
        while(1)
        {

                if(timer>10)
				{
					i2c_readbyte(0x41, &ans);
					UART_Send_Byte(ans);
					timer=0;
				}
            		Led_set(ans);
                Led_display(LED_Buffer);
                Delay(1);
        }
} 
