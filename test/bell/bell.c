#include<reg52.h>
sbit bell=P1^4;
int main(void)
{
	while(1)
	{
		bell=0;
	}
}
