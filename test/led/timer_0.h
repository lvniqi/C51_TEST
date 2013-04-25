#ifndef _TIMER_0_H_
#define _TIMER_0_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
#define timer_0_start() EA=1;ET0=1;TR0=1;//开总中断，开0中断，开0定时器
uint timer_0=0;
void set_timer_0(void)
{
	TMOD=0X02;//设置定时器0 自动重载8位定时器/计数器
	TH0=0x19;			//设置定时器
	TL0=0x19;          //设置定时器
	timer_0++;
}
void Timer_ET0_250us() interrupt 1//延时250us
{
	TF0=0;
	timer_0++;
}
#endif