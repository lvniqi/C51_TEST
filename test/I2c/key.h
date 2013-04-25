#ifndef _KEY_H_
#define _KEY_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
uchar keys[8]={0};
sbit key_i1=P1^0;
sbit key_i2=P1^1;
sbit key_i3=P1^2;
sbit key_i4=P1^3;
sbit key_j1=P1^4;
sbit key_j2=P1^5;
sbit key_j3=P1^6;
sbit key_j4=P1^7;
/********************************************************************
* 名称 : restart_Keys(uchar *idpt)
* 功能 : 重置数据为0
* 输入 : uchar *idpt
* 输出 : 无
***********************************************************************/
void restart_Keys(uchar *idpt)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		idpt[i]=0;
	}
}
/********************************************************************
* 名称 : int Key(uchar *keys)
* 功能 : 单个矩阵按键读入
* 输入 : uchar *keys
* 输出 :  int 按键序号
***********************************************************************/
uchar Keys(uchar *keys)
{
	restart_Keys(keys);
	P1=0x0f;
	if(P1!=0x0f)
	{
		if(0==key_i1)
			keys[1]=1;
		else if(0==key_i2)
			keys[1]=2;
		else if(0==key_i3)
			keys[1]=3;
		else
			keys[1]=4;
	   P1=0xf0;
		if(0==key_j1)
			keys[0]=1; 
		else if(0==key_j2)
			keys[0]=2;
		else if(0==key_j3)
			keys[0]=3;
		else
			keys[0]=4;
		return (keys[0]-1)*4+keys[1];
	}
	else
		return 0;
	
}
#endif