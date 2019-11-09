#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/***********************************************************************
						���񴴽�������
***********************************************************************/
//�������ȼ�
#define START_TASK_PRIO 1
//�����ջ��С
#define START_STK_SIZE 128
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParmeters);

/***********************************************************************/
//�������ȼ�
#define LED0_TASK_PRIO 2
//�����ջ��С
#define LED0_STK_SIZE 50
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

/***********************************************************************/
//�������ȼ�
#define LED1_TASK_PRIO 3
//�����ջ��С
#define LED1_STK_SIZE 50
//������
TaskHandle_t LED1Task_Handler;
//������
void led1_task(void *pvParameters);

/***********************************************************************/
int main(void)
{   
	BaseType_t xReturn = pdPASS;
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
	uart_init(84,115200);		//��ʼ�����ڲ�����Ϊ115200 
	LED_Init();					//��ʼ��LED
	//������ʼ����
	xTaskCreate((TaskFunction_t )start_task,
				(const char*	)"start_task",
				(uint16_t		)START_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)START_TASK_PRIO,
				(TaskHandle_t*	)&StartTask_Handler
	);
	if(xReturn == pdPASS)
	{
		vTaskStartScheduler();//�����������
	}else{
		return 0;
	}
	while(1);
}

void start_task(void *pvParameters)
{
	
	BaseType_t xReturn = pdPASS;
	taskENTER_CRITICAL();	//�����ٽ��
	
	//����LED0����
	xTaskCreate((TaskFunction_t )led0_task,
				(const char*	)"led0_task",
				(uint16_t		)LED0_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)LED0_TASK_PRIO,
				(TaskHandle_t*	)&LED0Task_Handler
	);
	if(xReturn == pdPASS)	
	{
		printf("Tack_led0�����ɹ���\r\n");
	}		
	//����LED0����
	xTaskCreate((TaskFunction_t )led1_task,
				(const char*	)"led1_task",
				(uint16_t		)LED1_STK_SIZE,
				(void*			)NULL,
				(UBaseType_t	)LED1_TASK_PRIO,
				(TaskHandle_t*	)&LED1Task_Handler
	);
	if(xReturn == pdPASS)	
	{
		printf("Tack_led1�����ɹ���\r\n");
	}
	vTaskDelete(StartTask_Handler);	//�����������һ��Ҫɾ�������񣬷�������		
	//�˳��ٽ��
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
/*  LED1������ */
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



















