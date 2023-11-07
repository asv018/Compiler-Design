// Write a program to implement CLR parser and LLR parsing table.

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Define the grammar rules
vector<pair<char, string>> productions = {
    {'E', "E+T"},
    {'E', "T"},
    {'T', "T*F"},
    {'T', "F"},
    {'F', "(E)"},
    {'F', "id"}};

// Define the LR(0) parsing table
map<pair<int, char>, string> parsingTable = {
    {{0, 'id'}, "S5"},
    {{0, '('}, "S4"},
    {{1, '+'}, "S6"},
    {{2, '*'}, "S7"},
    {{3, ')'}, "R2"},
    {{3, '$'}, "R2"},
    {{4, 'id'}, "S5"},
    {{4, '('}, "S4"},
    {{5, '+'}, "R4"},
    {{5, '*'}, "R4"},
    {{5, ')'}, "R4"},
    {{5, '$'}, "R4"},
    {{6, 'id'}, "S5"},
    {{6, '('}, "S4"},
    {{7, 'id'}, "S5"},
    {{7, '('}, "S4"},
    {{8, '+'}, "S6"},
    {{8, ')'}, "R1"},
    {{8, '$'}, "R1"},
    {{9, '+'}, "R3"},
    {{9, '*'}, "S7"},
    {{9, ')'}, "R3"},
    {{9, '$'}, "R3"}};
// {{10 , '$' , "Accept"}}

stack<int> stateStack;
stack<char> symbolStack;

bool parse(string input)
{
    stateStack.push(0);

    for (size_t i = 0; i < input.size(); i++)
    {
        char symbol = input[i];
        int currentState = stateStack.top();

        if (parsingTable.find({currentState, symbol}) != parsingTable.end())
        {
            string action = parsingTable[{currentState, symbol}];

            if (action[0] == 'S')
            {

                stateStack.push(stoi(action.substr(1)));
                symbolStack.push(symbol);
            }
            else if (action[0] == 'R')
            {

                int ruleIndex = stoi(action.substr(1)) - 1;
                pair<char, string> production = productions[ruleIndex];
                int popCount = production.second.size();
                for (int j = 0; j < popCount; j++)
                {
                    stateStack.pop();
                    symbolStack.pop();
                }
                char nonTerminal = production.first;
                symbolStack.push(nonTerminal);
                int newState = stateStack.top();
                stateStack.push(newState);
            }
            else if (action == "Accept")
            {

                return true;
            }
        }
        else
        {

            return false;
        }
    }
    return false;
}

int main()
{
    string input;
    cout << "Enter an arithmetic expression: ";
    cin >> input;

    input += '$'; // Append end marker
    if (parse(input))
    {
        cout << "Parsing successful." << endl;
    }
    else
    {
        cout << "Parsing failed." << endl;
    }

    return 0;
}
