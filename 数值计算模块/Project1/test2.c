#include <stdio.h>
#include <stdlib.h>

// 求最大公约数
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 求最小公倍数
int lcm(int a, int b)
{
    return abs(a * b) / gcd(a, b);
}

int main(int argc, char *argv[])
{
    int a = 36, b = 60;
    printf("GCD of %d and %d is %d\n", a, b, gcd(a, b));
    printf("LCM of %d and %d is %d\n", a, b, lcm(a, b));
    return 0;
}