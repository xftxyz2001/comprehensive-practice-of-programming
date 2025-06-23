
// 反馈结构体
typedef struct {
    int id;         // 反馈编号，自动生成
    int studentId;  // 学生ID
    int merchantId; // 商家ID
    char problem[150]; // 反馈内容
    char reply[100];    // 回复内容
    char time[20];      // 提交时间
} Feedback;

#define MAX_FEEDBACKS 100

extern Feedback feedbacks[MAX_FEEDBACKS];
extern int feedbackCount;

// 函数声明
void merchantMenu(int merchantId);
void marchantFeedback(int merchantId);
void replyToFeedback();