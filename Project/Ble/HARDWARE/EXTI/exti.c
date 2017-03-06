#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "rtc.h"
extern bool peidui_flag;
extern bool vibrate_flag;
extern bool pause_flag;
extern bool run_flag;
extern bool off_flag;
extern u16 offcont;
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{	
	if(off_flag)
	{
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,57600);  //���ڳ�ʼ�� 
 	EXTIX_Init();
  PWM_Init(1000,71);	 //����Ƶ��PWMƵ��=72000/900=8Khz
  TimeCont0(65535,32768);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	}
	delay_ms(20);//����
	//offcont = 0;
	if(PAin(0)==1)	 //����2
	{
		  	TIM2->CNT = 0;
	    	TIM2->CR1|=0x01;    //ʹ�ܶ�ʱ��2  
	}	
  else if(PAin(0)==0)	
	{
		  TIM2->CR1&=0<<0;    //�رն�ʱ��
      if((run_flag)&&(vibrate_flag)&&(((TIM2->CNT/200>0)&&(TIM2->CNT/200<20))))  //pause
			{
				pause_flag =1;
				vibrate_flag =0;
				run_flag = 1;
				off_flag = 0;
			}
	 else if((run_flag)&&(pause_flag)&&(((TIM2->CNT/200>0)&&(TIM2->CNT/200<20))))  //vibrate
			{
				pause_flag =0;
				vibrate_flag =1;
				run_flag = 1;
				off_flag = 0;
			}
				TIM2->CNT = 0;
	}
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}

void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	//JTAG_Set(JTAG_SWD_DISABLE);//�ر�JTAG��SWD   
  RCC->APB2ENR|=1<<0;     //��������ʱ��		  
 	
	GPIOA->CRL&=0XFFFFFFF0;//PA0���ó�����	  
	GPIOA->CRL|=0X00000008;   
	
	Ex_NVIC_Config(GPIO_A,0,RTIR); //�����ش���
	Ex_NVIC_Config(GPIO_A,0,FTIR); //�½��ش���
	

	MY_NVIC_Init(2,3,EXTI0_IRQChannel,3);    //��ռ2�������ȼ�2����2
}












