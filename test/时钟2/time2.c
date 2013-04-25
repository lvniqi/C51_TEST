#include"normal.h"
#include"led_4.h"
#include"key.h"
extern uchar keys[8]; 
uchar flag=0,a,temp=0,count2=0;
uint timer=0;
uint Temp1=0;
void com_init(void);
void set_timer(void);
void Set_time(uint *a);
void Set(uchar key1);
int main(void)
{
	int count2;
	uchar key_temp;
	com_init();
	set_timer();
	while(1)
	{
		 if(temp>3)
		{
			ES=0;
		}
		if(timer==20*60)
			{
				Temp1+=1;
				timer=0;
				Set_time(&Temp1);
			}
		key_temp=Keys(keys);
		if(key_temp)
		{			
			count2++;
			if(count2==35)
			{
				count2=0;
				Set(key_temp);
				Set_time(&Temp1);
			}
		}
		Led_set(Temp1);
		Led_display(LED_Buffer);
	}
}
void server(void) interrupt 4
{
	static i=0;
	if(1==RI)
	{
		RI=0;
		temp++;
		if(i)
		{
			Temp1*=10;
			Temp1+=SBUF-'0';
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
	ET2=1;          //����ʱ��2�ж�
	TR2=1;          //������ʱ����������Ϊ�Զ���װ��ģʽ
}
void Timer_ET2_50ms() interrupt 5//��ʱ50ms
{
	TF2=0;
	timer++;
}
void Set_time(uint *a)//ʱ���׼��
{
	uchar temp1=*a%100;
	uchar temp2=*a/100;
	uchar temp3=temp1/60;
	temp1%=60;
	temp2+=temp3;
	if(temp2>=24)
		temp2-=24;
	*a=temp2*100+temp1;
}
void Set(uchar key1)
{
	switch(key1)
	{
	case 16:	Temp1+=1000;break;
	case 15:	Temp1+=100;break;
	case 14:	Temp1+=10;break;
	case 13:	Temp1++;break;
	case 12:	Temp1-=1000;break;
	case 11:	Temp1-=100;break;
	case 10:	Temp1-=10;break;
	case 9:		Temp1--;break;
	};
}
