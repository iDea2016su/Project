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
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�
		  							    
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(3,3,TIM3_IRQChannel,3);//��ռ1�������ȼ�3����2									 
}
	 

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void PWM_Init(u16 arr,u16 psc)
{		 					 
 RCC->APB1ENR|=1<<1; 	//TIM3ʱ��ʹ��
	RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��	    

	GPIOA->CRL&=0X00FFFFFF;	//PA6 CH1 PA7 CH2
	GPIOA->CRL|=0XBB000000;	//���ù������ 	  	 
	   

	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������Ƶ


	TIM3->CCMR1|=7<<4;  	//CH1 PWM2ģʽ		 
	TIM3->CCMR1|=1<<3; 	    //CH1Ԥװ��ʹ��	   
	TIM3->CCER|=1<<0;   	//OC1 ���ʹ��
  TIM3->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч 

	TIM3->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM3->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	   
	TIM3->CCER|=1<<4;   	//OC2 ���ʹ��
  TIM3->CCER|=1<<5;    // OC2 �͵�ƽ��Ч

	TIM3->CR1&=1<<7;   	    //ARPEʹ�� 
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��3 		
}  	 

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{
		    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
void TimeCont0(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM2ʱ��ʹ��    
 	TIM2->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM2->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	TIM2->DIER|=1<<0;   //��������ж�				
 	TIM2->DIER|=1<<6;   //�������ж�	

  MY_NVIC_Init(1,3,TIM2_IRQChannel,1);//��ռ1�������ȼ�3����2									 
}
void TIM1_UP_IRQHandler(void)
 { 		    		  			    
 	if(TIM1->SR&0X0001)//����ж�
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
 	TIM1->SR&=~(1<<0);//����жϱ�־λ 
}	
 }
void TimeWeak(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11;//TIM1ʱ��ʹ��    
 	TIM1->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM1->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM1->DIER|=1<<0;   //��������ж�				
  //TIM1->DIER|=1<<6;   //�������ж�	   
	TIM1->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(2,3,TIM1_UP_IRQChannel,3);//��ռ1�������ȼ�3����2						 
}