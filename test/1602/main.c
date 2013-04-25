#include"normal.h"
#include"1602.h"
#include"timer.h"
#include"Iic.h"
#include"At24.h"
/********************************************************************
* ���� : void Write_Time(uchar num)
* ���� : д��һ����
* ���� : uchar num		    
* ��� : ��
***********************************************************************/
void Write_Time(uchar num)
{
	char T []="00";
	T[1]=num%10+'0';
	num/=10;
	T[0]=num+'0';
	puts(T);	
}
/********************************************************************
* ���� : void write(uchar* time)
* ���� : д��ʱ��
* ���� : uchar *s 		    
* ��� : ��
***********************************************************************/
void Write_Array(uchar* time)
{
	Write_Time(time[0]);
	Lcd_Write(':',1);
	Write_Time(time[1]);
	Lcd_Write(':',1);
	Write_Time(time[2]);			
}
/********************************************************************
* ���� : void Display_Time()
* ���� : ��ʾʱ��
* ���� : �� 		    
* ��� : ��
***********************************************************************/
void Display_Time(char *t)
{
	if(timer==20)
		{
			timer=0;
			Delay(90);
			Lcd_Write(0x80+0x40,0);//���ָ��
			t[2]++;
			AT24_Send(2,t[2]);
			if(60<=t[2])
			{
				t[2]-=60;
				t[1]+=1;
				Delay(90);
				AT24_Send(1,t[1]);
				if(t[1]>=60)
				{
					t[1]-=60;
					t[0]++;
					Delay(90);
					AT24_Send(0,t[0]);
					if(t[0]>=24)
					{
						t[0]-=24;
						Delay(90);
					}
				}
			}
			Write_Array(t);
		}									  
}
int main(void)
{
	uchar t[3];
	uchar a[]="Hollo World!";
	Iic_Start();
	t[0]=AT24_Read(0);
	Delay(90);
	t[1]=AT24_Read(1);
	Delay(90);
	t[2]=AT24_Read(2);
	Delay(90);
	set_timer();
	Lcd_Write(0x38,0);//��ʾģʽ����
	Lcd_Write(0x0c,0);//��ʾ����
	Lcd_Write(0x06,0);//�������
	Lcd_Write(0x80,0);//���ָ��
	puts(a);
	Lcd_Write(0x80+0x40,0);//���ָ��
	timer=0;
	while(1)
	{
	  	Display_Time(t);
	}
	return 0;
}
