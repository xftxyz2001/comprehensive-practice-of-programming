#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "SpeedCtrol.h"

// ȫ�ֱ�������
unsigned int speed_count = 0; // ռ�ձȼ����� 50��һ����
char front_left_speed_duty = SPEED_DUTY;
char front_right_speed_duty = SPEED_DUTY;
char behind_left_speed_duty = SPEED_DUTY;
char behind_right_speed_duty = SPEED_DUTY;

unsigned char tick_5ms = 0;	  // 5ms����������Ϊ�������Ļ�������
unsigned char tick_1ms = 0;	  // 1ms����������Ϊ����Ļ���������
unsigned char tick_200ms = 0; // ˢ����ʾ

char ctrl_comm = COMM_STOP; // ����ָ��
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
		front_right_speed_duty = SPEED_DUTY; // ����
		behind_left_speed_duty = SPEED_DUTY; // �ҵ��
		// behind_right_speed_duty=SPEED_DUTY;
	}
}
