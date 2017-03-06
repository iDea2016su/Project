#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//ͨ���ı�TIM3->CCR2��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define PWM1 TIM3->CCR1 
#define PWM2 TIM3->CCR2 
extern int time_pressed; 
extern int time_temp;
void Timerx_Init(u16 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
void TimeCont0(u16 arr,u16 psc);
void TimeCont1(u16 arr,u16 psc);
void TimeWeak(u16 arr,u16 psc);
#endif























