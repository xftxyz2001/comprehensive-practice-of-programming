#include <stdio.h>
#include "square.h"
#include "sqrt.h"

int main() {
    int num;
    printf("shuru zhengshu:");
    scanf("%d",&num);
    printf("Square of %d: %.2f\n", num, square(num));
    printf("Square root of %d: %.2f\n", num, my_sqrt(num));
    return 0;
}
