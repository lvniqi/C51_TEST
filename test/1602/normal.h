#ifndef _NORMAL_H_
#define	_NORMAL_H_
#include<reg52.h>
#include<intrins.h>
#include"timer_0.h"
#include"pt.h"
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
uchar count_interrupt=0; //定时器_计数
/********************************************************************
* 名称 : Delay()
* 功能 : 延时子程序，延时时间为 0.1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay(uint i)//0.1ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
		for(x=0;x<=1;x++);	
}
/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay_1ms(uint i)//1ms延时
{
	uchar x,j;
	for(j=0;j<i;j++)
		for(x=0;x<=148;x++);	
}
#endif