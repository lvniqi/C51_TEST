#include"normal.h"
#include"led_4.h"
#include"Iic.h"
#include"At24.h"
#include"key.h"
#include"timer.h"
int main(void)
{
	int i=AT24_Read(0);
	uchar a[32]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	Led_set(AT24_Read(i+8));
	set_timer();
	AT24_Send_Page(8,a,20);
	Delay(90);
	while(1)
	{
		if(timer==10)
		{
			timer=0;
			if(i<18)
			{
				Led_set(AT24_Read(i+8));
				i++;
				AT24_Send(0,i);
			}
			else
				i=0;
		}
		Led_display();
	}
	return 0;
}