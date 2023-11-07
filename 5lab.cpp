#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Represents a production rule
struct Production
{
    char nonTerminal;
    string production;
};

// Function to compute the First set for a given non-terminal
set<char> computeFirst(char nonTerminal, map<char, vector<string>> &productions, map<char, set<char>> &firstSets)
{
    if (firstSets.find(nonTerminal) != firstSets.end())
    {
        return firstSets[nonTerminal];
    }

    set<char> firstSet;

    for (string prod : productions[nonTerminal])
    {
        if (isupper(prod[0]))
        { // Non-terminal symbol
            set<char> subFirst = computeFirst(prod[0], productions, firstSets);
            firstSet.insert(subFirst.begin(), subFirst.end());
        }
        else
        {
            firstSet.insert(prod[0]); // Terminal symbol
        }
    }

    firstSets[nonTerminal] = firstSet;
    return firstSet;
}

int main()
{
    map<char, vector<string>> productions;
    map<char, set<char>> firstSets;

    // Add your grammar productions here
    productions['S'] = {"aB", "bA"};
    productions['A'] = {"a", "b"};
    productions['B'] = {"b", "c"};

    // Compute First sets for each non-terminal
    for (const auto &entry : productions)
    {
        computeFirst(entry.first, productions, firstSets);
    }

    // Check if the grammar is LL(1)
    bool isLL1 = true;
    for (const auto &entry : productions)
    {
        set<char> firstSet = firstSets[entry.first];
        for (char terminal : firstSet)
        {
            for (string prod : entry.second)
            {
                if (isupper(prod[0]) && firstSets[prod[0]].count(terminal) > 0)
                {
                    isLL1 = false;
                    break;
                }
                else if (!isupper(prod[0]) && prod[0] != terminal)
                {
                    isLL1 = false;
                    break;
                }
            }
        }
        if (!isLL1)
        {
            break;
        }
    }

    if (isLL1)
    {
        cout << "The grammar is LL(1)." << endl;
    }
    else
    {
        cout << "The grammar is not LL(1)." << endl;
    }

    return 0;
}