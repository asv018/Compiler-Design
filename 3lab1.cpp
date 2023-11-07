// Write a program to check whether a string belongs to the grammer or not
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
    char str[10];
    cout << "\nThe grammar is as follows:\nS -> aS\nS -> Sb\nS -> ab\n";
    cout << "Enter a string: ";
    cin >> str;
    if (str[0] != 'a')
    {
        cout << "String is invalid because of incorrect first character";
        exit(0);
    }
    int n = 1;
    while (str[n] == 'a')
        n++;
    if (str[n] != 'b')
    {
        cout << "string does not belong to grammar";
        exit(0);
    }
    n++;
    while (str[n] == 'b')
        n++;
    if (str[n] != '\0')
    {
        cout << "String does not belong to grammar";
        exit(0);
    }

    cout << "string is valid";
    getch();
}