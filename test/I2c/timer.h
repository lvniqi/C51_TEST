#ifndef _TIMER_H_
#define _TIMER_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
uchar timer=0;
void set_timer(void)
{
	EA=1;
	RCAP2H=19456/256;
	RCAP2L=19456%256;
	ET2=1;          //开定时器2中断
	TR2=1;          //开启定时器，并设置为自动重装载模式
}
void Timer_ET2_50ms() interrupt 5//延时50ms
{
	TF2=0;
	timer++;
}
#endif