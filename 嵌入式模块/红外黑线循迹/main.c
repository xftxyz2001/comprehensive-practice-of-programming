// 连接方式 ：请参考interface.h文件
// 部份源码来源网络--请试用24小时后删除
#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "uart.h"

// 全局变量定义
unsigned int speed_count = 0; // 占空比计数器 50次一周期
char front_left_speed_duty = SPEED_DUTY;
char front_right_speed_duty = SPEED_DUTY;
char behind_left_speed_duty = SPEED_DUTY;
char behind_right_speed_duty = SPEED_DUTY;

unsigned char tick_5ms = 0;	  // 5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;	  // 1ms计数器，作为电机的基本计数器
unsigned char tick_200ms = 0; // 刷新显示

char ctrl_comm = COMM_STOP;		 // 控制指令
char ctrl_comm_last = COMM_STOP; // 上一次的指令
unsigned char continue_time = 0;
unsigned char bt_rec_flag = 0; // 蓝牙控制标志位

// 循迹，通过判断三个光电对管的状态来控制小车运动
void SearchRun(void)
{
	// 三路都检测到黑线
	if (SEARCH_M_IO == BLACK_AREA && SEARCH_L_IO == BLACK_AREA && SEARCH_R_IO == BLACK_AREA)
	{
		ctrl_comm = COMM_UP;
		return;
	}
	// 中间检测到，左右未检测
	if (SEARCH_M_IO == BLACK_AREA && SEARCH_L_IO != BLACK_AREA && SEARCH_R_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_UP;
		return;
	}
	// 偏右：左和中检测，右未检测
	if (SEARCH_L_IO == BLACK_AREA && SEARCH_M_IO == BLACK_AREA && SEARCH_R_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_LEFT;
		return;
	}
	// 偏左：右和中检测，左未检测
	if (SEARCH_R_IO == BLACK_AREA && SEARCH_M_IO == BLACK_AREA && SEARCH_L_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_RIGHT;
		return;
	}
	// 严重偏右
	if (SEARCH_L_IO == BLACK_AREA && SEARCH_M_IO != BLACK_AREA && SEARCH_R_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_LEFT;
		return;
	}
	// 严重偏左
	if (SEARCH_R_IO == BLACK_AREA && SEARCH_M_IO != BLACK_AREA && SEARCH_L_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_RIGHT;
		return;
	}
	// 未检测到黑线
	if (SEARCH_L_IO != BLACK_AREA && SEARCH_M_IO != BLACK_AREA && SEARCH_R_IO != BLACK_AREA)
	{
		ctrl_comm = COMM_STOP;
		return;
	}
}

int main(void)
{
	delay_init();
	GPIOCLKInit();
	UserLEDInit();
	LCD1602Init();
	// IRCtrolInit();
	TIM2_Init();
	MotorInit();
	ServoInit();

	RedRayInit();
	// USART3Conf(9600);

	while (1)
	{
		if (tick_5ms >= 5)
		{
			tick_5ms = 0;
			tick_200ms++;
			if (tick_200ms >= 40)
			{
				tick_200ms = 0;
				LEDToggle(LED_PIN);
			}

			SearchRun();
			if (ctrl_comm_last != ctrl_comm) // 指令发生变化
			{
				ctrl_comm_last = ctrl_comm;
				switch (ctrl_comm)
				{
				case COMM_UP:
					CarGo();
					break;
				case COMM_DOWN:
					CarBack();
					break;
				case COMM_LEFT:
					CarLeft();
					break;
				case COMM_RIGHT:
					CarRight();
					break;
				case COMM_STOP:
					CarStop();
					break;
				default:
					break;
				}
				Delayms(10); // 防抖
				// LCD1602WriteCommand(ctrl_comm);
			}
		}
	}
}
