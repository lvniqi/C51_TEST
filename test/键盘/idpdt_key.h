#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint  unsigned int
#endif
uchar keys[8];
sbit i_key4=P1^0;
sbit i_key3=P1^1;
sbit i_key2=P1^2;
sbit i_key1=P1^3;
sbit j_key1=P1^4;
sbit j_key2=P1^5;
sbit j_key3=P1^6;
sbit j_key4=P1^7;
uchar idpt[4]={0};
/********************************************************************
* ���� : restart_Key(uchar *idpt)
* ���� : ��������Ϊ0
* ���� : uchar *idpt
* ��� : ��
***********************************************************************/
void restart_Key(uchar *idpt)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		idpt[i]=0;
	}
}
/********************************************************************
* ���� : Idpdt_Key(uchar *idpt)
* ���� : ������������
* ���� : uchar *idpt
* ��� : ��
***********************************************************************/
void Idpdt_Key(uchar *idpt)
{
	uchar i;
	P1=0x0f;
	if(P1!=0x0f)
	{
		;
	}
}
