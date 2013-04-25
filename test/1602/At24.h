#ifndef _AT24_H_
#define _AT24_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
#include "Iic.h"
const uchar AT24_address=0xa0;
/*-----------------------------------------
AT24C02
发送数据
函数原型: void AT24_Send(uchar byte_address,uchar num)
功能:     发送数据
-----------------------------------------*/
void AT24_Send(uchar byte_address,uchar num) 
{
	Iic_Start();
	SendByte(AT24_address);
	Respons();
	SendByte(byte_address);
	Respons();
	SendByte(num);
	Respons();
	Iic_End();
}
/*-----------------------------------------
AT24C02
发送数据
函数原型: void AT24_Send_Block(uchar byte_address,uchar num)
功能:     发送一组数据
-----------------------------------------*/
void AT24_Send_Page(uchar page_address,uchar *num,uchar len)//注意！！！！！开始地址必须为8的倍数！！！！！
{
	uchar i;
	Iic_Start();
	SendByte(AT24_address);
	Respons();
	SendByte(page_address);
	Respons();
	for(i=0;i<len;i++)
	{
		if(i!=0&&i%8==0)
		{
			Iic_End();
			Delay(90);
			Iic_Start();
			SendByte(AT24_address);
			Respons();
			SendByte(page_address+=8);
			Respons();	
		}
		SendByte(num[i]);
		Respons();
		SomeNops();
	}
	Iic_End();
}
/*-----------------------------------------
AT24C02
发送数据
函数原型: void AT24_Read(uchar byte_address,uchar num)
功能:     提取数据
-----------------------------------------*/
uchar AT24_Read(uchar byte_address)
{
	uchar i=0;
	Iic_Start();
	SendByte(AT24_address);	  
	Respons();
	SendByte(byte_address);
	Respons();
	Iic_Start();
	SendByte(AT24_address+1);
	Respons();
	i=GetByte();
	Iic_End();
	return i;
}
#endif