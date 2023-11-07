#include <iostream>
#include <functional>

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

int main()
{
    std::function<void()> S1 = []()
    {
        std::cout << "Executing statement S1" << std::endl;
    };

    std::function<void()> S2 = []()
    {
        std::cout << "Executing statement S2" << std::endl;
    };

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
