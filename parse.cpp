#include <iostream>
#include <stack>
#include <cctype>

struct TreeNode
{
    char value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isParenthesis(char c)
{
    return (c == '(' || c == ')');
}

int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

TreeNode *buildParseTree(const std::string &expression)
{
    std::stack<TreeNode *> nodeStack;
    std::stack<char> opStack;

    for (char c : expression)
    {
        if (std::isspace(c))
        {
            continue;
        }
        else if (std::isdigit(c))
        {
            TreeNode *operandNode = new TreeNode(c);
            nodeStack.push(operandNode);
        }
        else if (isOperator(c))
        {
            while (!opStack.empty() && isOperator(opStack.top()) &&
                   getPrecedence(c) <= getPrecedence(opStack.top()))
            {
                TreeNode *operatorNode = new TreeNode(opStack.top());
                opStack.pop();
                operatorNode->right = nodeStack.top();
                nodeStack.pop();
                operatorNode->left = nodeStack.top();
                nodeStack.pop();
                nodeStack.push(operatorNode);
            }
            opStack.push(c);
        }
        else if (isParenthesis(c))
        {
            if (c == '(')
            {
                opStack.push(c);
            }
            else if (c == ')')
            {
                while (!opStack.empty() && opStack.top() != '(')
                {
                    TreeNode *operatorNode = new TreeNode(opStack.top());
                    opStack.pop();
                    operatorNode->right = nodeStack.top();
                    nodeStack.pop();
                    operatorNode->left = nodeStack.top();
                    nodeStack.pop();
                    nodeStack.push(operatorNode);
                }
                opStack.pop(); // Pop '('
            }
        }
    }

    while (!opStack.empty())
    {
        TreeNode *operatorNode = new TreeNode(opStack.top());
        opStack.pop();
        operatorNode->right = nodeStack.top();
        nodeStack.pop();
        operatorNode->left = nodeStack.top();
        nodeStack.pop();
        nodeStack.push(operatorNode);
    }

    return nodeStack.top();
}

void printParseTree(TreeNode *node, int indent = 0)
{
    if (node)
    {
        printParseTree(node->right, indent + 4);
        std::cout << std::string(indent, ' ') << node->value << std::endl;
        printParseTree(node->left, indent + 4);
    }
}

int main()
{
    std::string infixExpression = "3 + 4 * (5 - 2)";
    TreeNode *root = buildParseTree(infixExpression);

    std::cout << "Parse Tree:" << std::endl;
    printParseTree(root);

    // TODO: Clean up memory by deleting the nodes in the parse tree

    return 0;
}