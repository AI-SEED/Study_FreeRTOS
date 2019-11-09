#include "timer.h"


//FreeRTOS时间统计所用的节拍计数器
volatile unsigned long long FreeRTOSRunTimeTicks;

//初始化TIM3使其为FreeRTOS的时间统计提供时基
void ConfigureTimeForRunTimeStats(void)
{
	//定时器3初始化，定时器时钟为84M，分频系数为84-1，所以定时器3的频率
	//为84M/84=1M，自动重装载为50-1，那么定时器周期就是50us
	FreeRTOSRunTimeTicks=0;
	TIM3_Int_Init(50-1,84-1);	//初始化TIM3
}

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		FreeRTOSRunTimeTicks++;		    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能    
 	TIM3->ARR=arr;  	//设定计数器自动重装值 
	TIM3->PSC=psc;  	//预分频器	  
	TIM3->DIER|=1<<0;   //允许更新中断	  
	TIM3->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,0,TIM3_IRQn,4);	//抢占1，组4								 
}






















