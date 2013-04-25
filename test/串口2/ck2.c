/********************************************************************
* 文件名  ： 串口交互.c
* 描述    :  该文件实现通过单片机从电脑接收数据。通过数码管显示
该试验使用的晶振是11.0592,如果使用12M晶振，会出现串口接收
不正常的情况。原因是用12M晶振，波特率9600时的误差率达 8%
当下载这个程序到单片机时，单片机的最高为为乱码，是正常现象，
按一下复位键便可。是由于单片机下载也是通过串口下载引起的。

***********************************************************************/
#include"normal.h"
#include"led_4.h"
sbit idpdt_led1=P1^0;
sbit idpdt_led2=P1^1;
uchar Led[9]={0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
int main(void)
{
	uint i=0;
	uchar flag=-1,flag2=1;
	TMOD=0x11;//设置定时器工作方式1
	TH0=(65536-50000)/256;//定时50毫秒
	TL0=(65536-50000)%256;//定时50毫秒
	EA=1;//开总中断
	ET0=1;//开定时器0中断
	ET1=1;//开定时器1中断
	//	EX0=1;//开外部中断0
	TR0=1;//启动定时器0
	TR1=1;//启动定时器1
//	IT0=1;//中断信号的输入方式
	idpdt_led2=0;
	while(1)
	{
		if(count_interrupt_2==20)//定时1s
		{
			Led_set(i);
			i++;	
			count_interrupt_2=0;
		}
		if(count_interrupt_1==5)
		{
			if(flag2)
			{
				flag++;
				P1=Led[flag];
				if(flag==8)
					flag2=0;
			}
			else
			{
				P1=Led[flag];
				flag--;
				if(flag==-1)
					flag2=1;	
			}
			count_interrupt_1=0;
		}
		Led_display();
	}
}
/*void exter0() interrupt 0
{
	idpdt_led1=0;
}*/
void Error_ET0_50ms() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count_interrupt_1++;
}
void Error_ET1_50ms() interrupt 3
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count_interrupt_2++;
}
