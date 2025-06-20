#include "UltrasonicCtrol.h"
#include "interface.h"
#include "stm32f10x.h"

volatile unsigned char status = 0;	   // 程序当前状态，0,空闲 1 发送触发信号，2 等待信号返回
unsigned int dis_count = 0;			   // 脉宽长计时
volatile unsigned int distance_cm = 0; // 当前距离

unsigned char t2_full_count = 0;	// 计数器计满次数计数
static unsigned int ultick_5ms = 0; // 5ms计数器

void Time4Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 72M / 72 = 1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

// 外部中断配置 超声波,这里没用到中断计数方式
void UltraSoundInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; // 定义一个外部中断相关的结构体
	NVIC_InitTypeDef NVIC_InitStructure; // 定义一个中断的结构体

	GPIO_InitStructure.GPIO_Pin = Echo_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 配置GPIO端口速度
	GPIO_Init(IRIN_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Trig_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 配置GPIO端口速度
	GPIO_Init(Trig_GPIO, &GPIO_InitStructure);

	GPIO_EXTILineConfig(Echo_PORTSOURCE, Echo_PINSOURCE);	// 将GPIO口配置成外部中断
	EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;			// 将对应的GPIO口连接到中断线上
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 中断事件类型，下降沿
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		// 选择模式，中断型
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;				// 使能该中断
	EXTI_Init(&EXTI_InitStructure);							// 将配置好的参数写入寄存器

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); // 阶级为0，不可嵌套
	NVIC_InitStructure.NVIC_IRQChannel = Echo_IRQCH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级0，最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  // 子优先级，最低
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 使能该模块中断
	NVIC_Init(&NVIC_InitStructure);							  // 中断初始化，将结构体定义的数据执行

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

// 延时的方式读取距离值
void GetDistanceDelay(void)
{
	unsigned int high_time = 0;
	Trig_SET;
	delay_us(20); // 持续时间大于10us
	Trig_RESET;

	// 等待Echo变高，超时设为60000us
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

	// Echo变高，开始计时
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

	distance_cm = (unsigned int)(high_time * 0.034 / 2); // 单位cm，速度340m/s
}
