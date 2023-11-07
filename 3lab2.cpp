// Write a program to check whether a grammer is left recursive?
#include <iostream>
using namespace std;

int main()
{
    int a;
    cout << "Enter the no. of production in your grammer : ";
    cin >> a;
    bool flag = false;
    cout << "Enter the productions in formet A->A+B/a etc." << endl;
    for (int i = 0; i < a; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j < s.length(); j++)
        {
            if (s[j] == s[0] && (s[j - 1] == '>' || s[j - 1] == '/'))
            {
                flag = true;
            }
        }
    }
    if (flag)
    {
        cout << "The grammar is recursive !!" << endl;
    }
    else
        cout << "The grammar is not recursive !!" << endl;
    return 0;
}