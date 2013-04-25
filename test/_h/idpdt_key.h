#ifndef _IDPDT_KEY_H_
#define _IDPDT_KEY_H_
#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
sbit idpdt_key4=P1^0;
sbit idpdt_key3=P1^1;
sbit idpdt_key2=P1^2;
sbit idpdt_key1=P1^3;
uchar idpt[4]={0};
/********************************************************************
* 名称 : restart_Key(uchar *idpt)
* 功能 : 重置数据为0
* 输入 : uchar *idpt
* 输出 : 无
***********************************************************************/
void restart_Key(uchar *idpt)
{
	uchar i;
	for(i=0;i<4;i++)
	{
		idpt[i]=0;
	}
}
/********************************************************************
* 名称 : Idpdt_Key(uchar *idpt)
* 功能 : 独立按键读入
* 输入 : uchar *idpt
* 输出 : 无
***********************************************************************/
void Idpdt_Key(uchar *idpt)
{
	uchar i=0;
	if(1==idpdt_key1)
		idpt[0]=0;
	else
		idpt[0]=1;
	if(1==idpdt_key2)
		idpt[1]=0;
	else
		idpt[1]=1;
	if(1==idpdt_key3)
		idpt[2]=0;
	else
		idpt[2]=1;
	if(1==idpdt_key4)
		idpt[3]=0;
	else
		idpt[3]=1;
}
#endif