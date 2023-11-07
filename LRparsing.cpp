#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Define your LR parsing table here
map<pair<int, string>, string> parsingTable = {
    {{0, "id"}, "S5"},
    {{0, "("}, "S4"},
    {{1, "+"}, "S6"},
    {{1, "$"}, "Accept"},
    {{2, "+"}, "R2"},
    {{2, "*"}, "S7"},
    {{2, ")"}, "R2"},
    {{3, "+"}, "R4"},
    {{3, "*"}, "R4"},
    {{3, ")"}, "R4"},
    {{3, "$"}, "R4"},
    {{4, "id"}, "S5"},
    {{4, "("}, "S4"},
    {{5, "+"}, "R6"},
    {{5, "*"}, "R6"},
    {{5, ")"}, "R6"},
    {{5, "$"}, "R6"},
    {{6, "id"}, "S5"},
    {{6, "("}, "S4"},
    {{7, "id"}, "S5"},
    {{7, "("}, "S4"},
};

// Define your grammar production rules here
map<int, pair<string, string>> grammar = {
    {1, {"E", "E+T"}},
    {2, {"E", "T"}},
    {3, {"T", "T*F"}},
    {4, {"T", "F"}},
    {5, {"F", "(E)"}},
    {6, {"F", "id"}}};

// Tokenize input string
vector<string> tokenize(string input)
{
    vector<string> tokens;
    string token;
    for (char c : input)
    {
        if (c == ' ' || c == '\t')
        {
            continue;
        }
        else if (c == '+' || c == '*' || c == '(' || c == ')' || c == '$')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        }
        else
        {
            token += c;
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
    tokens.push_back("$"); // Add end-of-input marker
    return tokens;
}

int main()
{
    string input;
    cout << "Enter input string: ";
    getline(cin, input);
    vector<string> tokens = tokenize(input);

    stack<int> stateStack;
    stack<string> symbolStack;

    stateStack.push(0);
    symbolStack.push("$");

    int index = 0;
    while (true)
    {
        int state = stateStack.top();
        string token = tokens[index];
        string action = parsingTable[{state, token}];

        if (action == "Accept")
        {
            cout << "Input accepted." << endl;
            break;
        }
        else if (action.empty() || action == "Error")
        {
            cout << "Error: Parsing failed." << endl;
            break;
        }
        else if (action[0] == 'S')
        {
            // Shift action
            int nextState = stoi(action.substr(1));
            stateStack.push(nextState);
            symbolStack.push(token);
            index++;
        }
        else if (action[0] == 'R')
        {
            // Reduce action
            int productionNumber = stoi(action.substr(1));
            // Perform reduction
            int numSymbolsToPop = 2 * grammar[productionNumber].second.length();
            for (int i = 0; i < numSymbolsToPop; i++)
            {
                stateStack.pop();
                symbolStack.pop();
            }
            // Find the non-terminal to push onto the stack
            string nonTerminal = grammar[productionNumber].first;
            symbolStack.push(nonTerminal);
            int newState = stateStack.top();
            // Look up the state transition after the reduction
            string goTo = parsingTable[{newState, nonTerminal}];
            stateStack.push(stoi(goTo));
        }
    }

    return 0;
}
