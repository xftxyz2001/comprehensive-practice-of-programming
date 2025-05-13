#include "redvoid.h"
#include "interface.h"
#include "motor.h"

extern char ctrl_comm;

// ��ȡ�������ģ��״̬
char GetVoidStatus(void)
{
    char left = 0, right = 0;
    char count;
    if (VOID_L_IO == BARRIER_Y)
    {
        count = 2;
        while (--count) // 10ms �ɼ�2�ξ�Ҫ�ɼ���ǰ���ϰ�����Ϣ���˲�
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
        while (--count) // 10ms �ɼ�2�ξ�Ҫ�ɼ���ǰ���ϰ�����Ϣ���˲�
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

// ��ʱ��ͬʱ�����⣬һ�������ϰ����ֹͣ��������ʱ
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

// ������ϴ���
// ����ʽ����߼�⵽  ����500ms ��ת500ms
//			�ұ߼�⵽  ����500ms ��ת500ms
//			���߼�⵽  ����800ms ��ת500ms
//           û��⵽    ֱ��
void VoidRun(void)
{
    char status = GetVoidStatus(); // ��ȡ����״̬

    switch (status)
    {
    case VOID_NONE:
        // û���ϰ���ֱ��
        CarGo();
        break;

    case VOID_LEFT:
        // ����⵽�ϰ�������500ms������ת500ms
        CarBack();
        DelayCheck(500);
        CarRight();
        DelayCheck(500);
        // ������ɺ��ٴ�ֱ��
        CarGo();
        break;

    case VOID_RIGHT:
        // �Ҳ��⵽�ϰ�������500ms������ת500ms
        CarBack();
        DelayCheck(500);
        CarLeft();
        DelayCheck(500);
        // ������ɺ��ٴ�ֱ��
        CarGo();
        break;

    case VOID_BOTH:
        // ���඼��⵽�ϰ�������800ms������ת500ms
        CarBack();
        DelayCheck(800);
        CarRight();
        DelayCheck(500);
        // ������ɺ��ٴ�ֱ��
        CarGo();
        break;

    default:
        // �쳣���Ҳֱ��ͣ��
        CarStop();
        break;
    }
}
