#ifndef _IIC_H_
#define _IIC_H_
#include<reg52.h>
#include <intrins.h>
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
#define  Nop  _nop_()	   //延时
#define  SomeNops() 	Nop; Nop; Nop; Nop; Nop;		  //延时
sbit     SCL=P2^6;       //I2C  时钟 
sbit     SDA=P2^7;       //I2C  数据 
/********************************************************************
* 名称 : I2c总线启始
* 功能 : 开始I2c总线
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Iic_Start(void)
{
	SDA=1;
	Nop;
	SCL=1;
	SomeNops();//延时
	SDA=0;//跳变
	SomeNops();//延时
	SCL=0;
}
/********************************************************************
                     应答子函数
函数原型:  void Respons(bit a)
功能:      主控器进行应答信号(可以是应答或非应答信号，由位参数a决定)
********************************************************************/
void Respons(bit a)
{
	if(a)
		SDA=1;
	else
	 	SDA=0;
	SomeNops();
	SCL=1;
	SomeNops();
	SCL=0;
}
/*******************************************************************
                 字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:     将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
          此状态位进行操作.(不应答或非应答都使ack=0)     
           发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void  SendByte(uchar  date)
{
	uchar i,temp=date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		SDA=CY;
		SCL=1;
		SomeNops();
		SCL=0;
	}
	SDA=1;
	SomeNops();
}
/*******************************************************************
                 字节数据接收函数               
函数原型: UCHAR  GetByte();
功能:        用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
          发完后请用应答函数应答从机。  
********************************************************************/    
uchar GetByte()
{
	uchar byte=0,i;
	SomeNops();
	SDA=1;
	for(i=0;i<8;i++)
	{
		SCL=1;
		if(SDA)
			byte+=1;
		byte<<=1;
		SCL=0;
		SomeNops();
	}

}
/*******************************************************************
* 名称 : I2c总线结束
* 功能 : 结束I2c总线
* 输入 : 无
* 输出 : 无
********************************************************************/
void Iic_End(void)
{
	SDA=0;
	Nop;
	SCL=1;
	SomeNops();//延时
	SDA=1;//跳变
	SomeNops();//延时
	SCL=0;
}
#endif