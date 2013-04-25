#include"normal.h"
#include"pt.h"
#include"timer_0.h"
#include"Led_4.h"
static PT pt1,pt2;
static int protothread2(PT *pt)
{
	static int i;
	PT_BEGIN(pt);
	while(1)
	{
		PT_WAIT_WHILE(pt,timer_0%5);
		Led_display(LED_Buffer);
		Led_set(i++/10);
	}
	PT_END(pt);
}
static int protothread1(PT *pt)
{
  static uchar a = 0xff;
  static uchar i;
  PT_BEGIN(pt);
  while(1) 
	{
  		for(i=0;i<=8;i++)
		{
			PT_WAIT_UNTIL(pt, timer_0>=200+200*i);
			P1=a;
			a<<=1;
		}
		for(i=0;i<8;i++)
		{
			PT_WAIT_UNTIL(pt, timer_0>=2000+200*i);
			a=~a;
			a>>=1;
			a=~a;
			P1=a;
		}
		timer_0=0;
	}
  PT_END(pt);
}
int main(void)
{
	set_timer_0();
   	timer_0_start();
	PT_INIT(&pt1);
	PT_INIT(&pt2);
	while(1)
	{
		protothread1(&pt1);
		protothread2(&pt2);
	}
}
