#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/***********************************************************************
						任务创建管理区
***********************************************************************/
//任务优先级
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParmeters);

/***********************************************************************/
//任务优先级
#define LED0_TASK_PRIO 2
//任务堆栈大小
#define LED0_STK_SIZE 50
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

/***********************************************************************/
//任务优先级
#define LED1_TASK_PRIO 3
//任务堆栈大小
#define LED1_STK_SIZE 50
//任务句柄
TaskHandle_t LED1Task_Handler;
//任务函数
void led1_task(void *pvParameters);

/***********************************************************************/
int main(void)
{   
	BaseType_t xReturn = pdPASS;
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化  
	uart_init(84,115200);		//初始化串口波特率为115200 
	LED_Init();					//初始化LED
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,
				(const char*	)"start_task",
				(uint16_t		)START_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)START_TASK_PRIO,
				(TaskHandle_t*	)&StartTask_Handler
	);
	if(xReturn == pdPASS)
	{
		vTaskStartScheduler();//开启任务调度
	}else{
		return 0;
	}
	while(1);
}

void start_task(void *pvParameters)
{
	
	BaseType_t xReturn = pdPASS;
	taskENTER_CRITICAL();	//进入临界段
	
	//创建LED0任务
	xTaskCreate((TaskFunction_t )led0_task,
				(const char*	)"led0_task",
				(uint16_t		)LED0_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)LED0_TASK_PRIO,
				(TaskHandle_t*	)&LED0Task_Handler
	);
	if(xReturn == pdPASS)	
	{
		printf("Tack_led0创建成功！\r\n");
	}		
	//创建LED0任务
	xTaskCreate((TaskFunction_t )led1_task,
				(const char*	)"led1_task",
				(uint16_t		)LED1_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)LED1_TASK_PRIO,
				(TaskHandle_t*	)&LED1Task_Handler
	);
	if(xReturn == pdPASS)	
	{
		printf("Tack_led1创建成功！\r\n");
	}
	vTaskDelete(StartTask_Handler);	//创建完任务后一定要删除本任务，否则会出错		
	//退出临界段
	taskEXIT_CRITICAL();
}

void led0_task(void *pvParameters)
{

    while(1)
    {
        LED0=~LED0;
        vTaskDelay(1000);
    }
}   
	u8 flag2=0;
/*  LED1任务函数 */
void led1_task(void *pvParameters)
{

    while(1)
    {
        LED1=0;
        vTaskDelay(200);
        LED1=1;
        vTaskDelay(800);
    }
}



















