#include<reg52.h>
#include<intrins.h>
#include"normal.h"
#include"led_4.h"
#include"key.h"
int main(void)
{
	uint i,j,k,t,n=0;
	while(1)
	{
		Led_set(Keys(keys));
		Led_display();
	}
}
