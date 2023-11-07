// Write a program to count the number of characters , words , space and lines in the given input file.
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Function to count characters, words, spaces, and lines in the given input file
void countFileStats(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    int charCount = 0;
    int wordCount = 0;
    int spaceCount = 0;
    int lineCount = 0;
    string line;

    while (getline(inputFile, line))
    {
        charCount += line.length();                         // Count characters
        spaceCount += count(line.begin(), line.end(), ' '); // Count spaces
        lineCount++;                                        // Count lines

        // Count words by iterating through each character in the line
        bool inWord = false;
        for (char c : line)
        {
            if (c != ' ' && !inWord)
            {
                inWord = true;
                wordCount++;
            }
            if (c == ' ')
            {
                inWord = false;
            }
        }
    }

    inputFile.close();

    cout << "Character count: " << charCount << endl;
    cout << "Word count: " << wordCount << endl;
    cout << "Space count: " << spaceCount << endl;
    cout << "Line count: " << lineCount << endl;
}

int main()
{
    string filename;
    cout << "Enter the input file name: ";
    getline(cin, filename);

    countFileStats(filename);

    return 0;
}
