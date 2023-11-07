// Write a program to convert expression from infix to postfix

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get precedence of an operator
int precedence(char c)
{
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    return 0;
}

// Function to convert infix expression to postfix expression
string infixToPostfix(string infix)
{
    stack<char> s;
    string postfix;

    for (char c : infix)
    {
        if (isalnum(c))
        {
            postfix.push_back(c);
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop(); // Pop the '('
        }
        else if (isOperator(c))
        {
            while (!s.empty() && precedence(c) <= precedence(s.top()))
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

int main()
{
    string infixExpression, postfixExpression;

    cout << "Enter the infix expression: ";
    getline(cin, infixExpression);

    postfixExpression = infixToPostfix(infixExpression);

    cout << "Postfix expression: " << postfixExpression << endl;

    return 0;
}
