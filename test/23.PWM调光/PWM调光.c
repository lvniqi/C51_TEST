/****************************************************
 * ����:        ������ΪCIKY��Ƭ��ѧϰ���̣���ӭ������
 *              һ��ѧϰ��̽�֣���ͬ������
 * Title:       ģ��PWM���
 * Description: 51��Ƭ��ģ��PWM������ƵƵ�100�����ȼ�
 * @author      CIKY
 * Date:        Jan. 06, 2010
****************************************************/

#include "normal.h"
#include "led_4.h"
#define uInt unsigned int
#define uchar unsigned char
uchar PWM_T = 0;   //ռ�ձȿ��Ʊ���
uchar timer=0;
uchar n=0;
void set_timer(void)  ;
//////////////////���������//////////////////////
void main(void)       
{ 
 bit flag = 1; //���Ƶƽ�����Ϩ��ʽ

 TMOD=0x02;   //��ʱ��0������ģʽ2��8λ��ʱģʽ 
 TH0=210;     //д��Ԥ�ó�ֵ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
 TL0=210;     //д��Ԥ��ֵ ��ȡֵ1-255����Խ��PWMƵ��Խ�ߣ�
 TR0=1;       //������ʱ�� 
 ET0=1;       //����ʱ��0�ж�
set_timer()   ;
 EA=1;        //�������ж�

 P1=0xff;  //��ʼ��P1

 while(1)     
 {    
		  //��ʱ������Ӧ��ʱ���жϣ��ƻ��Զ���/��һ�����ε�����
                             //ȡֵ0-65535������Խ��仯Խ��
 	if(timer==3)
	 { 
 		if(flag==1)   //�ƽ���
   			PWM_T++;
  		else    //�ƽ�Ϩ
  		 	PWM_T--;
    
 		 if(PWM_T>=100) //���õ����ȼ���Ϊ10
 	 		 flag=0;

 		 if(PWM_T==0)   //�޶�������ȼ���Ϊ0
   			flag = 1;
		timer=0;
		n++;
		Led_set(n);
 	}
	Led_display(LED_Buffer)		;
 }      

}

///////////////////��ʱ��0�ж�ģ��PWM////////////////////
timer0() interrupt 1 using 2   
{ 
 static  uchar   t ;   //PWM����

 t++;    //ÿ�ζ�ʱ�������1
  
 if(t==100)   //PWM����

 { 
  t=0;  //ʹt=0����ʼ�µ�PWM���� 
  P1=0x00;  //ʹLED����   
   
 }
  
 if(PWM_T==t)  //���յ�ǰռ�ձ��л����Ϊ�ߵ�ƽ 
  P1=0xff;        //ʹLED����   
}
void set_timer(void)
{
	RCAP2H=19456/256;
	RCAP2L=19456%256;
	ET2=1;          //����ʱ��2�ж�
	TR2=1;          //������ʱ����������Ϊ�Զ���װ��ģʽ
	EA=1;
}
void Timer_ET2_50ms() interrupt 5//��ʱ50ms
{
	TF2=0;
	timer++;
}