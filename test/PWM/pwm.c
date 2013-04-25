#include "normal.h"
#include "led_4.h"
uchar OFF=0xff;	 //关
uchar ON=0xfe;		 //开
uchar PWM=0;
uchar timer=0;
void SetTimer0(void);
void SetTimer2(void);
int main(void)
{
	bit flag=1;
	uchar flag2=0;
	uchar flag3=0;
	SetTimer0();
	SetTimer2();
	P1=OFF;
	while(1)
	{
		bit temp=flag;
		if(timer==2)
		{
			if(flag)
			{
				PWM++;
				if(PWM==100)
					flag=~flag;
			}
			else
			{
				PWM--;
				if(PWM==0)
					flag=~flag;
			}
			Led_set(PWM);
			timer=0;
			if(temp!=flag)
				flag2++;
			if(flag2==2)
			{
				if(flag3<7)
				{
					ON=~ON;
					ON<<=1;
					ON=~ON;
				}
				else
				{
					ON=~ON;
					ON>>=1;
					ON=~ON;
				}
				P1=OFF;
				flag3++;
				if(flag3==14)
						flag3=0;
				flag2=0;
			}
		}
		Led_display(LED_Buffer);
	}
}
void Timer0(void) interrupt 1//定时器0
{
	   static uint t=0;
	   if(100==t)
	   {
	   		t=0;
			P1=ON;
	   }
	   else if(t==PWM)
	   {
			P1=OFF;
	   }
	   t++;
}
void Timer2(void) interrupt 5 //定时器2
{
	timer++;
	TF2=0;
}
void SetTimer0(void)   //设置定时器0
{
 	TMOD=0x02;   //定时器0，工作模式2，8位定时模式 
 	TH0=100;     //写入预置初值（取值1-255，数越大PWM频率越高）
	TL0=100;     //写入预置值 （取值1-255，数越大PWM频率越高）
	TR0=1;       //启动定时器 
	ET0=1;       //允许定时器0中断
	EA=1;		 //开启总中断
}
void SetTimer2(void)   //设置定时器2
{
	RCAP2H=19456/256;//高8位
	RCAP2L=19456%256;//低8位
	TR2=1;	//启动定时器2
	ET2=1;	//允许定时器2中断
	EA=1;   //开启总中断
}