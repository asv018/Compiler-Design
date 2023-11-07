#include <stdio.h>

int E()
{
    int a = 20;
    int b = 25;

    if (a > b)
    {
        return 1; // Condition is true
    }
    else
    {
        return 0; // Condition is false
    }
}

void S1()
{
    printf("Executing statement S1\n");
}

void S2()
{

    printf("Executing statement S2\n");
}

int main()
{
    int conditionResult = E();
    if (conditionResult)
    {
        S1();
    }
    else
    {
        S2();
    }

    return 0;
}