// 菜品结构体（保留，用于菜品管理）
typedef struct {
    char id[10];
    char name[30];
    float price;
    char type[20];
    char merchantId[5];
} Dish;


//函数声明
void DishModify(int merchantId);

