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

    std::stack <Bracket> brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char current_bracket = text[position];

        if (current_bracket == '(' || current_bracket == '[' || current_bracket == '{') {
            Bracket opener(current_bracket, position+1);
            brackets_stack.push(opener);
        } else if (current_bracket == ')' || current_bracket == ']' || current_bracket == '}') {

            // This is an error, push the non-matching "closer" element and break
            if (brackets_stack.empty())
            {
              Bracket closer(current_bracket, position+1);
              brackets_stack.push(closer);
              break;
            }

            Bracket test = brackets_stack.top();
            if (test.Matchc(current_bracket))
            {
                brackets_stack.pop();
            }
            else
            {
                // This is an error, push the non-matching "closer" and then break
                Bracket closer(current_bracket, position+1);
                brackets_stack.push(closer);
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (brackets_stack.empty())
    {
        std::cout << "Success" << std::endl;
    }
    else
    {
        Bracket nonmatching = brackets_stack.top();
        std::cout << nonmatching.position << std::endl;
    }
    return 0;
}
