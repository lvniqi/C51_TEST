/********************************************************************
* �ļ���  �� ���ڽ���.c
* ����    :  ���ļ�ʵ��ͨ����Ƭ���ӵ��Խ������ݡ�ͨ���������ʾ
������ʹ�õľ�����11.0592,���ʹ��12M���񣬻���ִ��ڽ���
�������������ԭ������12M���񣬲�����9600ʱ������ʴ� 8%
������������򵽵�Ƭ��ʱ����Ƭ�������ΪΪ���룬����������
��һ�¸�λ����ɡ������ڵ�Ƭ������Ҳ��ͨ��������������ġ�

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
	TMOD=0x11;//���ö�ʱ��������ʽ1
	TH0=(65536-50000)/256;//��ʱ50����
	TL0=(65536-50000)%256;//��ʱ50����
	EA=1;//�����ж�
	ET0=1;//����ʱ��0�ж�
	ET1=1;//����ʱ��1�ж�
	//	EX0=1;//���ⲿ�ж�0
	TR0=1;//������ʱ��0
	TR1=1;//������ʱ��1
//	IT0=1;//�ж��źŵ����뷽ʽ
	idpdt_led2=0;
	while(1)
	{
		if(count_interrupt_2==20)//��ʱ1s
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
