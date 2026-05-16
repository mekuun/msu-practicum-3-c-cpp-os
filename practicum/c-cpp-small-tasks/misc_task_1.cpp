#include <iostream>
#include <stack>
#include <sstream>
using std::stack, std::cout, std::endl, std::string, std::cin, std::stringstream;

class stack_element {
    int operand;
    char operatr;
public:
    bool op_flag;
    stack_element(int inp_operand) : operand(inp_operand), op_flag(true) {}
    stack_element(char inp_operatr) : operatr(inp_operatr), op_flag(false) {}
    int oprnd() const { return operand; }
    char oprtr() const { return operatr; }
    void print() const;
};

void stack_element::print() const {
    if (op_flag) {
        cout << operand << endl;
    } else {
        cout << operatr << endl;
    }
}

using plz_stack = stack<stack_element>;

void analyse(plz_stack& inp) {
    char oper = inp.top().oprtr();
    inp.pop();

    if (!inp.top().op_flag) {
        analyse(inp);
    }
    int first_operand = inp.top().oprnd();
    inp.pop();

    if (oper == '@') {
        inp.push(stack_element(-first_operand));
    } else {
        if (!inp.top().op_flag) {
            analyse(inp);
        }
        int second_operand = inp.top().oprnd();
        inp.pop();

        switch (oper) {
            case '+': inp.push(stack_element(second_operand + first_operand)); break;
            case '-': inp.push(stack_element(second_operand - first_operand)); break;
            case '/': inp.push(stack_element(second_operand / first_operand)); break;
            case '*': inp.push(stack_element(second_operand * first_operand)); break;
            default: throw std::invalid_argument("Unknown operator");
        }
    }
}

int main() {
    string s;
    getline(cin, s);
    plz_stack stack;
    char c = 0;
    string numberString;
    bool readingNumber = false;

    s += ' ';  // Добавляем пробел для обработки последнего элемента
    for (char ch : s) {
        if (ch == ' ') {
            if (readingNumber) {
                int x;
                stringstream ss(numberString);
                ss >> x;
                stack.push(stack_element(x));
                numberString.clear();
                readingNumber = false;
            } else if (c != 0) {
                stack.push(stack_element(c));
                c = 0;
            }
        } else if ('0' <= ch && ch <= '9') {
            numberString += ch;
            readingNumber = true;
        } else {
            if (readingNumber) {
                int x;
                stringstream ss(numberString);
                ss >> x;
                stack.push(stack_element(x));
                numberString.clear();
                readingNumber = false;
            }
            c = ch;
        }
    }

        analyse(stack);
        stack.top().print();
        stack.pop();
}
