#include"normal.h"
#include"led_4.h"
#include"key.h"
extern uchar keys[8]; 
uchar flag=0,a,temp=0;
uint timer=0;
uint Temp1=0;
void com_init(void);
void set_timer(void);
void Set_time(uint *a);
int main(void)
{
	com_init();
	set_timer();
	while(1)
	{
		if(flag==1)
		{
			ES=0;
			flag=0;
			SBUF=a;
			while(!TI);
			TI=0;
			ES=1;
		 }
		 while(temp>3)
		{
			ES=0;
			ET2=1;          //����ʱ��2�ж�
			TR2=1;          //������ʱ����������Ϊ�Զ���װ��ģʽ
			if(timer==20*60)
			{
				Temp1+=1;
				timer=0;
				Set_time(&Temp1);
			}
			Led_set(Temp1);
			Led_display(LED_Buffer);
		}
	}
}
void server(void) interrupt 4
{
	static i=0;
	if(1==RI)
	{
		RI=0;
		flag=1;
		temp++;
		a=SBUF;
		if(i)
		{
			Temp1*=10;
			Temp1+=a-'0';
			}
		i++;
	}
}
void com_init(void)
{
    TMOD=0X20;//���ö�ʱ��������ʽ
	PCON = 0x00;//���ñ���
    REN=1;//�򿪴���
	SM0=0;//�趨����ģʽ
	SM1=1;//�趨����ģʽ
	TH1=0XFD;//���üĴ�����ֵ
	TL1=0XFD;
	TR1=1;//������ʱ��1
	ES=1;//�򿪴����ж�
	EA=1;//���ж�
}
void set_timer(void)
{
	RCAP2H=19456/256;
	RCAP2L=19456%256;
}
void Timer_ET2_50ms() interrupt 5//��ʱ50ms
{
	TF2=0;
	timer++;
}
void Set_time(uint *a)//ʱ���׼��
{
	static uchar x=60;
	if(x==60)
	{
		uchar temp1=*a%100;
		uchar temp2=*a/100;
		uchar temp3=temp1/60;
		temp1%=60;
		temp2+=temp3;
		if(temp2==24)
			temp2=0;
		*a=temp2*100+temp1;
		if(temp1==0)
			x=1;
	}
	else
		x++;
}
