#include "redvoid.h"
#include "interface.h"
#include "motor.h"

extern char ctrl_comm;

// 获取红外避障模块状态
char GetVoidStatus(void)
{
    char left = 0, right = 0;
    char count;
    if (VOID_L_IO == BARRIER_Y)
    {
        count = 2;
        while (--count) // 10ms 采集2次均要采集到前面障碍物信息，滤波
        {
            if (VOID_L_IO == BARRIER_N)
                break;
            Delayms(1);
        }
        if (count == 0)
            left = 1;
    }

    if (VOID_R_IO == BARRIER_Y)
    {
        count = 2;
        while (--count) // 10ms 采集2次均要采集到前面障碍物信息，滤波
        {
            if (VOID_R_IO == BARRIER_N)
                break;
            Delayms(1);
        }
        if (count == 0)
            right = 2;
    }

    return left + right;
}

// 延时的同时检测红外，一旦发生障碍物，就停止并跳出延时
void DelayCheck(int ms)
{
    while (ms--)
    {
        Delayms(1);
        if (VOID_NONE != GetVoidStatus())
        {
            CarStop();
            return;
        }
    }
}

// 红外避障处理
// 处理方式：左边检测到  后退500ms 右转500ms
//			右边检测到  后退500ms 左转500ms
//			两边检测到  后退800ms 右转500ms
//           没检测到    直行
void VoidRun(void)
{
    char status = GetVoidStatus(); // 获取避障状态

    switch (status)
    {
    case VOID_NONE:
        // 没有障碍，直行
        CarGo();
        break;

    case VOID_LEFT:
        // 左侧检测到障碍：后退500ms，再右转500ms
        CarBack();
        DelayCheck(500);
        CarRight();
        DelayCheck(500);
        // 避障完成后，再次直行
        CarGo();
        break;

    case VOID_RIGHT:
        // 右侧检测到障碍：后退500ms，再左转500ms
        CarBack();
        DelayCheck(500);
        CarLeft();
        DelayCheck(500);
        // 避障完成后，再次直行
        CarGo();
        break;

    case VOID_BOTH:
        // 两侧都检测到障碍：后退800ms，再右转500ms
        CarBack();
        DelayCheck(800);
        CarRight();
        DelayCheck(500);
        // 避障完成后，再次直行
        CarGo();
        break;

    default:
        // 异常情况也直接停车
        CarStop();
        break;
    }
}
