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
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{	
	if(off_flag)
	{
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,57600);  //串口初始化 
 	EXTIX_Init();
  PWM_Init(1000,71);	 //不分频。PWM频率=72000/900=8Khz
  TimeCont0(65535,32768);//10Khz的计数频率，计数到5000为500ms  
	}
	delay_ms(20);//消抖
	//offcont = 0;
	if(PAin(0)==1)	 //按键2
	{
		  	TIM2->CNT = 0;
	    	TIM2->CR1|=0x01;    //使能定时器2  
	}	
  else if(PAin(0)==0)	
	{
		  TIM2->CR1&=0<<0;    //关闭定时器
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
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}

void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	//JTAG_Set(JTAG_SWD_DISABLE);//关闭JTAG和SWD   
  RCC->APB2ENR|=1<<0;     //开启辅助时钟		  
 	
	GPIOA->CRL&=0XFFFFFFF0;//PA0设置成输入	  
	GPIOA->CRL|=0X00000008;   
	
	Ex_NVIC_Config(GPIO_A,0,RTIR); //上升沿触发
	Ex_NVIC_Config(GPIO_A,0,FTIR); //下降沿触发
	

	MY_NVIC_Init(2,3,EXTI0_IRQChannel,3);    //抢占2，子优先级2，组2
}












