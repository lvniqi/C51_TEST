/****************************************************
 * 声明:        此制作为CIKY单片机学习过程，欢迎爱好者
 *              一起学习和探讨，共同进步。
 * Title:       模拟PWM输出
 * Description: 51单片机模拟PWM输出控制灯的100个亮度级
 * @author      CIKY
 * Date:        Jan. 06, 2010
****************************************************/

#include "normal.h"
#include "led_4.h"
#define uInt unsigned int
#define uchar unsigned char
uchar PWM_T = 0;   //占空比控制变量
uchar timer=0;
uchar n=0;
void set_timer(void)  ;
//////////////////主程序入口//////////////////////
void main(void)       
{ 
 bit flag = 1; //控制灯渐亮渐熄方式

 TMOD=0x02;   //定时器0，工作模式2，8位定时模式 
 TH0=210;     //写入预置初值（取值1-255，数越大PWM频率越高）
 TL0=210;     //写入预置值 （取值1-255，数越大PWM频率越高）
 TR0=1;       //启动定时器 
 ET0=1;       //允许定时器0中断
set_timer()   ;
 EA=1;        //允许总中断

 P1=0xff;  //初始化P1

 while(1)     
 {    
		  //延时，将响应定时器中断，灯会自动加/减一个档次的亮度
                             //取值0-65535，数字越大变化越慢
 	if(timer==3)
	 { 
 		if(flag==1)   //灯渐亮
   			PWM_T++;
  		else    //灯渐熄
  		 	PWM_T--;
    
 		 if(PWM_T>=100) //设置灯亮度级别为10
 	 		 flag=0;

 		 if(PWM_T==0)   //限定最低亮度级别为0
   			flag = 1;
		timer=0;
		n++;
		Led_set(n);
 	}
	Led_display(LED_Buffer)		;
 }      

}

///////////////////定时器0中断模拟PWM////////////////////
timer0() interrupt 1 using 2   
{ 
 static  uchar   t ;   //PWM计数

 t++;    //每次定时器溢出加1
  
 if(t==100)   //PWM周期

 { 
  t=0;  //使t=0，开始新的PWM周期 
  P1=0x00;  //使LED灯亮   
   
 }
  
 if(PWM_T==t)  //按照当前占空比切换输出为高电平 
  P1=0xff;        //使LED灯灭   
}
void set_timer(void)
{
	RCAP2H=19456/256;
	RCAP2L=19456%256;
	ET2=1;          //开定时器2中断
	TR2=1;          //开启定时器，并设置为自动重装载模式
	EA=1;
}
void Timer_ET2_50ms() interrupt 5//延时50ms
{
	TF2=0;
	timer++;
}