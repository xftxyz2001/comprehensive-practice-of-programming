
// �����ṹ��
typedef struct {
    int id;         // ������ţ��Զ�����
    int studentId;  // ѧ��ID
    int merchantId; // �̼�ID
    char problem[150]; // ��������
    char reply[100];    // �ظ�����
    char time[20];      // �ύʱ��
} Feedback;

#define MAX_FEEDBACKS 100

extern Feedback feedbacks[MAX_FEEDBACKS];
extern int feedbackCount;

// ��������
void merchantMenu(int merchantId);
void marchantFeedback(int merchantId);
void replyToFeedback();