#ifndef _TIMER_0_H_
#define _TIMER_0_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
#define timer_0_start() EA=1;ET0=1;TR0=1;//�����жϣ���0�жϣ���0��ʱ��
uint timer_0=0;
void set_timer_0(void)
{
	TMOD=0X02;//���ö�ʱ��0 �Զ�����8λ��ʱ��/������
	TH0=0x19;			//���ö�ʱ��
	TL0=0x19;          //���ö�ʱ��
	timer_0++;
}
void Timer_ET0_250us() interrupt 1//��ʱ250us
{
	TF0=0;
	timer_0++;
}
#endif