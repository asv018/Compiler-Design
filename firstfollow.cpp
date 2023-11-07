#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map<string, vector<string>> grammar = {
    {"S", {"AB"}},
    {"A", {"aA", ""}},
    {"B", {"bB", "c"}}};

unordered_map<string, unordered_set<char>> first;
unordered_map<string, unordered_set<char>> follow;

unordered_set<char> calculateFirst(const string &symbol);
void calculateFollow(const string &symbol, unordered_set<char> &result);

void calculateFirstForSymbol(const string &symbol)
{
    first[symbol] = calculateFirst(symbol);
}

unordered_set<char> calculateFirst(const string &symbol)
{
    unordered_set<char> result;

    if (!isupper(symbol[0]))
    {
        result.insert(symbol[0]);
    }
    else
    {
        for (const string &production : grammar[symbol])
        {
            for (char ch : production)
            {
                if (!isupper(ch))
                {
                    result.insert(ch);
                    break;
                }
                unordered_set<char> subFirst = calculateFirst(string(1, ch));
                result.insert(subFirst.begin(), subFirst.end());
                if (subFirst.find('e') == subFirst.end())
                {
                    break;
                }
            }
        }
    }

    return result;
}

void calculateFollowForSymbol(const string &symbol)
{
    calculateFollow(symbol, follow[symbol]);
}

void calculateFollow(const string &symbol, unordered_set<char> &result)
{
    if (symbol == "S")
    {
        result.insert('$');
    }

    for (const auto &entry : grammar)
    {
        const string &nonTerminal = entry.first;
        for (const string &production : entry.second)
        {
            size_t pos = production.find(symbol);
            while (pos != string::npos)
            {
                if (pos + symbol.size() < production.size())
                {
                    unordered_set<char> subFirst = calculateFirst(production.substr(pos + symbol.size(), 1));
                    result.insert(subFirst.begin(), subFirst.end());
                    if (subFirst.find('e') == subFirst.end())
                    {
                        break;
                    }
                }
                else if (pos + symbol.size() == production.size() && nonTerminal != symbol)
                {
                    calculateFollowForSymbol(nonTerminal);
                    unordered_set<char> subFollow = follow[nonTerminal];
                    result.insert(subFollow.begin(), subFollow.end());
                }
                pos = production.find(symbol, pos + 1);
            }
        }
    }
}

int main()
{
    for (const auto &entry : grammar)
    {
        calculateFirstForSymbol(entry.first);
    }

    for (const auto &entry : grammar)
    {
        calculateFollowForSymbol(entry.first);
    }

    cout << "First sets:" << endl;
    for (const auto &entry : first)
    {
        cout << "First(" << entry.first << ") = { ";
        for (char ch : entry.second)
        {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }

    cout << "Follow sets:" << endl;
    for (const auto &entry : follow)
    {
        cout << "Follow(" << entry.first << ") = { ";
        for (char ch : entry.second)
        {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}