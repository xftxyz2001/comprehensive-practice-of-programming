#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "SpeedCtrol.h"

// 全局变量定义
unsigned int speed_count = 0; // 占空比计数器 50次一周期
char front_left_speed_duty = SPEED_DUTY;
char front_right_speed_duty = SPEED_DUTY;
char behind_left_speed_duty = SPEED_DUTY;
char behind_right_speed_duty = SPEED_DUTY;

unsigned char tick_5ms = 0;	  // 5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;	  // 1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0; // 刷新显示

char ctrl_comm = COMM_STOP; // 控制指令
unsigned char continue_time = 0;

int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	LCD1602Init();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
	ServoInit();
	MeasureInit();

	while (1)
	{

		// front_left_speed_duty=SPEED_DUTY;
		front_right_speed_duty = SPEED_DUTY; // 左电机
		behind_left_speed_duty = SPEED_DUTY; // 右电机
		// behind_right_speed_duty=SPEED_DUTY;
	}
}
