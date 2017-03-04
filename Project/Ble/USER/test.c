#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 
#include "rtc.h"

#define speed1 300
#define speed2 400
#define speed3 500
#define speed4 600  
#define speed5 700
#define speed6 750
#define speed7 850
#define speed8 950  

extern u16 year;
extern u8 month;
extern u8 day;
extern u8 hour;
extern u8 min;
extern u8 sec;
//time_out_flag
bool time_out_flag = 0;
//
//weakcont
u16 offcont = 0;
//
//flag
bool vibrate_flag = 0;
bool pause_flag = 0;
bool run_flag = 0;
bool off_flag = 1;
bool first_vibrate = 0;
bool time_set = 0;
//time
u16 time_num[7][6]={0};
u16 time_long[7] = {0,0,0,3,4,5,6};
u16 autooff0=12;
u16 autooff1=12;
u16 autooff2=12;
//
//motor
u8 motor[7] ={ 2,0,0,0,0,0,0};
u8 speed[7] ={ 1,2,3,4,5,6,7};
//
//status
u8 status = 0;
u8 set_status = 1;//o--关机模式  c--配对模式 v--振动模式  p--暂停模式
//
//send
bool send_flag=1;
bool status_send_flag = 0;

bool first_pause =0;
bool first_virbate =0;

//
int main(void)

{		
	u8 i = 0,j = 0;
	u16 num=0;
	u16 cont =0;
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,57600);  //串口初始化 
 	EXTIX_Init();
  PWM_Init(1000,71);	 //不分频。PWM频率=72000/900=8Khz
  TimeCont0(65535,32768);//10Khz的计数频率，计数到5000为500ms  
  RTC_Init();
  PWM1 = 0;
  PWM2 = 0;
 	TIM2->CNT = 0;
 	TIM4->CNT = 0;
 // delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//  delay_ms(200);
 // printf("+++a");
 // delay_ms(200);
// 	printf("AT+HIBERNATE\r\n");
	//delay_ms(500);
	Sys_Stop();
 	while(1)
	{		  
    		delay_ms(30);
		    USART_RX_STA=0;
			  set_status=USART_RX_BUF[0]-'0';
			  switch(set_status)          //蓝牙接口设置参数
				{
					case 'a':break;
					
					case ('b'-'0'): send_flag=0;if(!send_flag){printf("s%d",speed[0]);send_flag = 1;}USART_RX_BUF[0]='a'+'0';break;
					
					case 1:speed[0]=1;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case 2:speed[0]=2;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case 3:speed[0]=3;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case 4:speed[0]=4;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case 5:speed[0]=5;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case 6:speed[0]=6;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case ('d'-'0'):speed[0]=7;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					case ('e'-'0'):speed[0]=8;printf("s%d",speed[0]);USART_RX_BUF[0]='a'+'0';break;
					
					case ('p'-'0'):pause_flag = 1;vibrate_flag = 0;USART_RX_BUF[0]='a'+'0';break;
					case ('s'-'0'):pause_flag = 0;vibrate_flag = 1;USART_RX_BUF[0]='a'+'0';break;
					
					case ('l'-'0'): delay_ms(30);
										autooff0 = (USART_RX_BUF[1]-'0')*10+(USART_RX_BUF[2]-'0');
					          printf("l%d",autooff0);
							      delay_ms(100);
					          USART_RX_BUF[0]='a'+'0';break;
					case ('m'-'0'): delay_ms(30);
										autooff1 = (USART_RX_BUF[1]-'0')*10+(USART_RX_BUF[2]-'0');
					          printf("m%d",autooff1);
							      delay_ms(100);
					          USART_RX_BUF[0]='a'+'0';break;
					case ('n'-'0'): delay_ms(30);
										autooff2 = (USART_RX_BUF[1]-'0')*10+(USART_RX_BUF[2]-'0');
									  printf("n%d",autooff2);
							      delay_ms(100);
					          USART_RX_BUF[0]='a'+'0';break;
					
					case 7: send_flag=0; if(!send_flag){printf("%d status",status);send_flag = 1;}USART_RX_BUF[0]='a'+'0';break; 
			
					case 8: 
						    send_flag=0;
						    if(!send_flag)
									{
										send_flag = 1;
										delay_ms(50);
									  for(i=0;i<7;i++)
										{
										//	printf("t%d %d %d %d %d %d&",
							//				time_num[i][0],
								//			time_num[i][1],
								//			time_num[i][2],
							//				time_num[i][3],
							//				time_num[i][4],
							//				time_num[i][5]);
										//	speed[i],
										//	time_long[i]);
									    delay_ms(100);
											// USART_RX_STA=0;
										}
										 	printf("r%d%d%d%d%d%d%d",speed[0],speed[1],speed[2],speed[3],speed[4],speed[5],speed[6]);
									   	delay_ms(70);
										  printf("q%d",time_long[0]);
									  	delay_ms(70);
										  printf("q%d",time_long[1]);
									  	delay_ms(70);
										  printf("q%d",time_long[2]);
									  	delay_ms(70);
										  printf("q%d",time_long[3]);
									  	delay_ms(70);
										  printf("q%d",time_long[4]);
										  delay_ms(70);
										  printf("q%d",time_long[5]);
											delay_ms(70);
										  printf("q%d",time_long[6]);
										  delay_ms(70);
										  printf("done");
					        }USART_RX_BUF[0]='a'+'0';break;
			//		case 9:send_flag =0;break;
					case ('c'-'0'):
						        delay_ms(30);
										year = (USART_RX_BUF[1]-'0')*1000+(USART_RX_BUF[2]-'0')*100+(USART_RX_BUF[3]-'0')*10+(USART_RX_BUF[4]-'0');
					          month =(USART_RX_BUF[5]-'0')*10+(USART_RX_BUF[6]-'0');
										day   =(USART_RX_BUF[7]-'0')*10+(USART_RX_BUF[8]-'0');
										hour =(USART_RX_BUF[9]-'0')*10+(USART_RX_BUF[10]-'0');
										min =(USART_RX_BUF[11]-'0')*10+(USART_RX_BUF[12]-'0');
										sec =(USART_RX_BUF[13]-'0')*10+(USART_RX_BUF[14]-'0');
										RTC_Set(year,month,day,hour,min,sec);  //设置时间	
							      delay_ms(100);
						      	printf("%d %d %d %d %d %d",year,month,day,hour,min,sec);
								//		time_num[0][0]=0;time_num[0][1]=0;time_num[0][2]=0;time_num[0][3]=0;time_num[0][4]=0;time_num[0][5]=0;
										time_num[1][0]=0;time_num[1][1]=0;time_num[1][2]=0;time_num[1][3]=0;time_num[1][4]=0;time_num[1][5]=0;
										time_num[2][0]=0;time_num[2][1]=0;time_num[2][2]=0;time_num[2][3]=0;time_num[2][4]=0;time_num[2][5]=0;
										time_num[3][0]=0;time_num[3][1]=0;time_num[3][2]=0;time_num[3][3]=0;time_num[3][4]=0;time_num[3][5]=0;
										time_num[4][0]=0;time_num[4][1]=0;time_num[4][2]=0;time_num[4][3]=0;time_num[4][4]=0;time_num[4][5]=0;
										time_num[5][0]=0;time_num[5][1]=0;time_num[5][2]=0;time_num[5][3]=0;time_num[5][4]=0;time_num[5][5]=0;
										time_num[6][0]=0;time_num[6][1]=0;time_num[6][2]=0;time_num[6][3]=0;time_num[6][4]=0;time_num[6][5]=0;
					 
										time_long[0]=0;time_long[1]=0;time_long[2]=0;time_long[3]=0;time_long[4]=0;time_long[5]=0;time_long[6]=0;
					
									//	speed[1]=0;speed[2]=0;speed[3]=0;speed[4]=0;speed[5]=0;speed[6]=0;
					
					       //   printf("%s",USART_RX_BUF);
					  	      USART_RX_BUF[0]='a'+'0';break;
						case ('t'-'0'):	if(year>0)printf("%d %d %d %d %d %d",year,month,day,hour,min,sec);else printf("time error");USART_RX_BUF[0]='a'+'0'; break;
						case ('x'-'0'):	printf("%d %d %d",autooff0,autooff1,autooff2); USART_RX_BUF[0]='a'+'0';break;
				    	default:break;
				}	
	
				if((off_flag)&&(PAin(0)==1))
				{
					LED_Init();
					TimeWeak(29999,35999);
					TIM1->CNT = 0;
					WeakUp = 0;
					while((off_flag)&&(PAin(0)==1))
					{
						delay_ms(10);
						if(num>190) {first_vibrate = 1; run_flag = 1;vibrate_flag =1;off_flag = 0;num = 0;WeakUp = 1; break;}
						num++;
					}
					time_long[0] = 0;
					offcont=0;
	}
		if((run_flag)&&vibrate_flag) //振动模式
		{
		    if(first_virbate)
				{
					printf("1 status");
					first_virbate = 0;
				}
				first_pause = 1;
		  	status = 1;
       switch(speed[0])
											{
												case 1:PWM1 = speed1;PWM2 = speed1;break;
												case 2:PWM1 = speed2;PWM2 = speed2;break;
												case 3:PWM1 = speed3;PWM2 = speed3;break;
												case 4:PWM1 = speed4;PWM2 = speed4;break;
												case 5:PWM1 = speed5;PWM2 = speed5;break;
												case 6:PWM1 = speed6;PWM2 = speed6;break;
												case 7:PWM1 = speed7;PWM2 = speed7;break;
												case 8:PWM1 = speed8;PWM2 = speed8;break;
												default:break;
											}
				if(first_vibrate)
					{
					while((PAin(0)==1));
								for(i=0;i<14;i++)
								{
									USART_RX_BUF[i]='o';
								}
						    first_vibrate =0;
				  }
        						
		}
	 if(pause_flag)
	{
		    if(first_pause)
				{
					printf("2 status");
					first_pause = 0;
				}
				first_virbate = 1;
		  	status = 2;
			  PWM1 = 0;
			  PWM2 = 0;
	}
		if((time_out_flag)||((vibrate_flag)&&(((TIM2->CNT/200)>=40))))//关闭模式
	{
		    time_out_flag = 0;
		    status = 0;
			  vibrate_flag = 0;
			  pause_flag = 0;
			  run_flag  =0;
			  off_flag = 1;
			  PWM1 = 0;
				PWM2 = 0;
				TIM2->CNT = 0;
			  TIM4->CNT = 0;	
		 			  for(i=6;i>0;i--)            //记录时间
				{
					
					time_num[i][0]=time_num[i-1][0];
					time_num[i][1]=time_num[i-1][1];
					time_num[i][2]=time_num[i-1][2];
					time_num[i][3]=time_num[i-1][3];
					time_num[i][4]=time_num[i-1][4];
					time_num[i][5]=time_num[i-1][5];
					motor[i]= motor[i-1];
					speed[i]= speed[i-1];
					time_long[i] = time_long[i-1];
					}
				time_num[0][0] = year;   //更新时间
				time_num[0][1] = month;
				time_num[0][2] = day;
				time_num[0][3] = hour;
				time_num[0][4] = min;
				time_num[0][5] = sec;
				while((PAin(0)==1));
				printf("3 status");
				TIM2->CNT = 0;
			  TIM4->CNT = 0;	
		//	 	delay_ms(30);
		//		delay_ms(100);
		//		delay_ms(50);
		//		delay_ms(50);
			//	printf("+++a");
			//	delay_ms(200);
			///	printf("AT+HIBERNATE\r\n");
		//		delay_ms(200);

				for(i=0;i<14;i++)
				{
					USART_RX_BUF[i]='o';
				}
				USART_RX_STA=0;
				Sys_Stop();
			  delay_ms(100);
	
					
	}
	if(off_flag&&(PAin(0)==0)) {	num = 0;cont =0 ;	Sys_Stop();}
		 
 }

}
