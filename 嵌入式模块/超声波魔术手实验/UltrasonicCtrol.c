#include "UltrasonicCtrol.h"
#include "interface.h"
#include "stm32f10x.h"

volatile unsigned char status = 0;	   // ����ǰ״̬��0,���� 1 ���ʹ����źţ�2 �ȴ��źŷ���
unsigned int dis_count = 0;			   // ������ʱ
volatile unsigned int distance_cm = 0; // ��ǰ����

unsigned char t2_full_count = 0;	// ������������������
static unsigned int ultick_5ms = 0; // 5ms������

void Time4Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 72M / 72 = 1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

// �ⲿ�ж����� ������,����û�õ��жϼ�����ʽ
void UltraSoundInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; // ����һ���ⲿ�ж���صĽṹ��
	NVIC_InitTypeDef NVIC_InitStructure; // ����һ���жϵĽṹ��

	GPIO_InitStructure.GPIO_Pin = Echo_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����GPIO�˿��ٶ�
	GPIO_Init(IRIN_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Trig_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ����GPIO�˿��ٶ�
	GPIO_Init(Trig_GPIO, &GPIO_InitStructure);

	GPIO_EXTILineConfig(Echo_PORTSOURCE, Echo_PINSOURCE);	// ��GPIO�����ó��ⲿ�ж�
	EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;			// ����Ӧ��GPIO�����ӵ��ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // �ж��¼����ͣ��½���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		// ѡ��ģʽ���ж���
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;				// ʹ�ܸ��ж�
	EXTI_Init(&EXTI_InitStructure);							// �����úõĲ���д��Ĵ���

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // �׼�Ϊ0������Ƕ��
	NVIC_InitStructure.NVIC_IRQChannel = Echo_IRQCH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // �����ȼ�0�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  // �����ȼ������
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // ʹ�ܸ�ģ���ж�
	NVIC_Init(&NVIC_InitStructure);							  // �жϳ�ʼ�������ṹ�嶨�������ִ��

	Time4Init();
	Trig_RESET;
}

void Distance(void)
{
	ultick_5ms++;
	if (ultick_5ms >= 15)
	{
		ultick_5ms = 0;
		GetDistanceDelay();
	}
}

// ��ʱ�ķ�ʽ��ȡ����ֵ
void GetDistanceDelay(void)
{
	unsigned int high_time = 0;
	Trig_SET;
	delay_us(20); // ����ʱ�����10us
	Trig_RESET;

	// �ȴ�Echo��ߣ���ʱ��Ϊ60000us
	int timeout = 0;
	while (!Echo && timeout < 60000)
	{
		delay_us(1);
		timeout++;
	}
	if (timeout >= 60000)
	{
		distance_cm = 0;
		return;
	}

	// Echo��ߣ���ʼ��ʱ
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);

	while (Echo && high_time < 60000)
	{
		high_time = TIM_GetCounter(TIM4);
	}

	TIM_Cmd(TIM4, DISABLE);

	if (high_time >= 60000)
	{
		distance_cm = 0;
		return;
	}

	distance_cm = (unsigned int)(high_time * 0.034 / 2); // ��λcm���ٶ�340m/s
}
