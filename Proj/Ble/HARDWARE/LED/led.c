#include "led.h"
void LED_Init(void)
{ 
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��		
	
	
	GPIOA->CRH&=0XFFF0FFFF; 
	GPIOA->CRH|=0X00030000;//PA4 �������   	 
  GPIOA->ODR|=1<<12;	   //PA4xiala
	 	 
}






