#include "normal.h"
#include "led_4.h"
uchar OFF=0xff;	 //��
uchar ON=0xfe;		 //��
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
void Timer0(void) interrupt 1//��ʱ��0
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
void Timer2(void) interrupt 5 //��ʱ��2
{
	timer++;
	TF2=0;
}
void SetTimer0(void)   //���ö�ʱ��0
{
 	TMOD=0x02;   //��ʱ��0������ģʽ2��8λ��ʱģʽ 
 	TH0=100;     //д��Ԥ�ó�ֵ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
	TL0=100;     //д��Ԥ��ֵ ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
	TR0=1;       //������ʱ�� 
	ET0=1;       //����ʱ��0�ж�
	EA=1;		 //�������ж�
}
void SetTimer2(void)   //���ö�ʱ��2
{
	RCAP2H=19456/256;//��8λ
	RCAP2L=19456%256;//��8λ
	TR2=1;	//������ʱ��2
	ET2=1;	//����ʱ��2�ж�
	EA=1;   //�������ж�
}