#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            Bracket opener(next, position+1);
            opening_brackets_stack.push(opener);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            Bracket test = opening_brackets_stack.top();
            if (test.Matchc(next))
            {
                opening_brackets_stack.pop();
            }
            else
            {
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty())
    {
        std::cout << "Success" << std::endl;
    }
    else
    {
        Bracket nonmatching = opening_brackets_stack.top();
        std::cout << nonmatching.position << std::endl;
    }
    return 0;
}
