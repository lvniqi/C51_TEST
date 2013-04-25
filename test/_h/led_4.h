#ifndef _LED_4_H_
#define _LED_4_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
uchar code table[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
sbit Led1 = P3^6;
sbit Led2 = P3^7;
sbit Led3 = P3^5;
sbit Led4 = P3^4;
uchar LED_Buffer[4] = {0};//led 数字缓存
/********************************************************************
* 名称 : led_display(uint data)
* 功能 : 显示一个数字
* 输入 : int 四位 数字
* 输出 : 无
***********************************************************************/
void Led_display(uchar *data1)
{
		Delay_1ms(1);
		P0=table[data1[0]];
		Led1=0;
		Led2=1;
		Led3=1;
		Led4=1;
		Delay_1ms(1);
		P0=table[data1[1]];
		Led1=1;
		Led2=0;
		Led3=1;
		Led4=1;
		Delay_1ms(1);
		P0=table[data1[2]];
		Led1=1;
		Led2=1;
		Led3=0;
		Led4=1;
		Delay_1ms(1);
		P0=table[data1[3]];
		Led1=1;
		Led2=1;
		Led3=1;
		Led4=0;
}
/********************************************************************
* 名称 : void led_set(int a)
* 功能 : 数字_进行数据设置
* 输入 : int 四位 数字
* 输出 : 无
***********************************************************************/
void Led_set(int a)
{
	int i;
	for(i=0;i<4;i++)
	{
		LED_Buffer[i]=a%10;
		a/=10;
	}
}
/********************************************************************
* 名称 : void led_set_16(int a)
* 功能 : 数字_进行数据设置 	16位
* 输入 : int 四位 数字
* 输出 : 无
***********************************************************************/
void Led_set_16(int a)
{
	int i;
	for(i=0;i<4;i++)
	{
		LED_Buffer[i]=a%16;
		a/=16;
	}
}
#endif