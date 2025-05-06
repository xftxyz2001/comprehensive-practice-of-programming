#ifndef __MOTOR_H_
#define __MOTOR_H_

extern unsigned int speed_count;//占空比计数器 50次一周期
extern char front_left_speed_duty;   // 左前
extern char front_right_speed_duty;  // 右前
extern char behind_left_speed_duty;  // 左后
extern char behind_right_speed_duty; // 右后

void CarMove(void);
void CarGo(void);
void CarBack(void);
void CarLeft(void);
void CarRight(void);
void CarStop(void);
void MotorInit(void);
#endif

