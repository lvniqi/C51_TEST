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
	ET2=1;          //����ʱ��2�ж�
	TR2=1;          //������ʱ����������Ϊ�Զ���װ��ģʽ
}
void Timer_ET2_50ms() interrupt 5//��ʱ50ms
{
	TF2=0;
	timer++;
}
#endif