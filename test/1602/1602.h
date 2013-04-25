sbit Lcd_en=P2^0;
sbit Lcd_rw=P2^1;
sbit Lcd_rs=P2^2;
#define data_out P0
/********************************************************************
* 名称 : void Lcd_Write(uchar com,bit RS)
* 功能 : 写入液晶数据或者命令
* 输入 : uchar com,bit RS		    、
		com为数据或者指令，RS=1时写数据 RS=0时写指令
* 输出 : 无
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
* 名称 : void puts(uchar *s)
* 功能 : 写入一组字符数据
* 输入 : uchar *s		    
* 输出 : 无
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
* 名称 : void Write_Num(uchar num)
* 功能 : 写入一个数
* 输入 : uchar num		    
* 输出 : 无
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
