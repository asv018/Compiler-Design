// Write a program to check the identifier in the given source program
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

bool isValidIdentifier(const std::string &identifier)
{

    if (!isalpha(identifier[0]) && identifier[0] != '_')
        return false;

    for (char ch : identifier)
    {
        if (!isalnum(ch) && ch != '_')
            return false;
    }

    static const std::vector<std::string> reservedKeywords = {
        "int", "double", "char", "float", "if", "else", "for", "while", "class", "return", "void"

    };

    return std::find(reservedKeywords.begin(), reservedKeywords.end(), identifier) == reservedKeywords.end();
}

int main()
{
    std::string filename;
    std::cout << "Enter the filename of the source code: ";
    std::cin >> filename;

    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> identifiers;

    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

            if (!word.empty() && isValidIdentifier(word) && std::find(identifiers.begin(), identifiers.end(), word) == identifiers.end())
                identifiers.push_back(word);
        }
    }

    inFile.close();

    if (identifiers.empty())
    {
        std::cout << "No valid identifiers found in the source code." << std::endl;
    }
    else
    {
        std::cout << "Valid identifiers in the source code:" << std::endl;
        for (const std::string &identifier : identifiers)
        {
            std::cout << identifier << std::endl;
        }
    }

    return 0;
}
