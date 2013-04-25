sbit Lcd_en=P2^0;
sbit Lcd_rw=P2^1;
sbit Lcd_rs=P2^2;
#define data_out P0
/********************************************************************
* ���� : void Lcd_Write(uchar com,bit RS)
* ���� : д��Һ�����ݻ�������
* ���� : uchar com,bit RS		    ��
		comΪ���ݻ���ָ�RS=1ʱд���� RS=0ʱдָ��
* ��� : ��
***********************************************************************/
void Lcd_Write(uchar com,bit RS)
{
	Lcd_rw=0;
	Lcd_rs=RS;
	data_out=com;
	Delay(5);
	Lcd_en=1;
	Delay(5);
	Lcd_en=0;
}
/********************************************************************
* ���� : void puts(uchar *s)
* ���� : д��һ���ַ�����
* ���� : uchar *s		    
* ��� : ��
***********************************************************************/
void puts(uchar *s)
{
	while(*s!=0)
	{
		Lcd_Write(*s,1);
		s++;
	}
}

/********************************************************************
* ���� : void Write_Num(uchar num)
* ���� : д��һ����
* ���� : uchar num		    
* ��� : ��
***********************************************************************/
void Write_Num(uchar num)reentrant
{
	static i=0;
	if(num)
	{
		Write_Num(num/10);
		Lcd_Write(num%10+'0',1);
	}
	if(!i)
		Lcd_Write('0',1);	
}
