#include "timer.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
extern u16 offcont;
extern u16  autooff0;
extern u16  autooff1;
extern u16  autooff2; 
extern bool time_out_flag;
extern bool first_pause;
extern u16 year;
extern u8 month;
extern u8 day;
extern u8 hour;
extern u8 min;
extern u8 sec;
//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3时钟使能    
 	TIM3->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	TIM3->DIER|=1<<0;   //允许更新中断				
	TIM3->DIER|=1<<6;   //允许触发中断
		  							    
	TIM3->CR1|=0x01;    //使能定时器3
  MY_NVIC_Init(3,3,TIM3_IRQChannel,3);//抢占1，子优先级3，组2									 
}
	 

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void PWM_Init(u16 arr,u16 psc)
{		 					 
 RCC->APB1ENR|=1<<1; 	//TIM3时钟使能
	RCC->APB2ENR|=1<<2;    	//使能PORTA时钟	    

	GPIOA->CRL&=0X00FFFFFF;	//PA6 CH1 PA7 CH2
	GPIOA->CRL|=0XBB000000;	//复用功能输出 	  	 
	   

	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器不分频


	TIM3->CCMR1|=7<<4;  	//CH1 PWM2模式		 
	TIM3->CCMR1|=1<<3; 	    //CH1预装载使能	   
	TIM3->CCER|=1<<0;   	//OC1 输出使能
  TIM3->CCER|=1<<1;   	//OC1 低电平有效 

	TIM3->CCMR1|=7<<12;  	//CH2 PWM2模式		 
	TIM3->CCMR1|=1<<11; 	//CH2预装载使能	   
	TIM3->CCER|=1<<4;   	//OC2 输出使能
  TIM3->CCER|=1<<5;    // OC2 低电平有效

	TIM3->CR1&=1<<7;   	    //ARPE使能 
	TIM3->CR1|=0x01;    	//使能定时器3 		
}  	 

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{
		    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}
void TimeCont0(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM2时钟使能    
 	TIM2->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM2->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	TIM2->DIER|=1<<0;   //允许更新中断				
 	TIM2->DIER|=1<<6;   //允许触发中断	

  MY_NVIC_Init(1,3,TIM2_IRQChannel,1);//抢占1，子优先级3，组2									 
}
void TIM1_UP_IRQHandler(void)
 { 		    		  			    
 	if(TIM1->SR&0X0001)//溢出中断
 {
    if(first_pause)
	  offcont++;
	 if((hour>=5)&&(hour<=11))if(offcont >=autooff0)
	 {
      offcont = 0;
		  time_out_flag = 1;
  	}		
  if(((hour>=11)&&(min>=30))&&(hour<=14))if(offcont >=autooff1)
	 {
      offcont = 0;
		  time_out_flag = 1;
  	}	
if(((hour>=18)&&(min>=30))&&(hour<=24))if(offcont >=autooff2)
	 {
      offcont = 0;
		  time_out_flag = 1;
  	}	
if(offcont ==60)
	 {
      offcont = 0;
		  time_out_flag = 1;
  	}	
 	TIM1->SR&=~(1<<0);//清除中断标志位 
}	
 }
void TimeWeak(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11;//TIM1时钟使能    
 	TIM1->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM1->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东东要同时设置才可以使用中断
	TIM1->DIER|=1<<0;   //允许更新中断				
  //TIM1->DIER|=1<<6;   //允许触发中断	   
	TIM1->CR1|=0x01;    //使能定时器3
  MY_NVIC_Init(2,3,TIM1_UP_IRQChannel,3);//抢占1，子优先级3，组2						 
}