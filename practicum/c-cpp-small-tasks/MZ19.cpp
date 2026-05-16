#include <iostream>
#include <stack>
#include <sstream>
using std::stack, std::cout, std::endl, std::string, std::cin, std::stringstream;

class stack_element{
    int operand;
    char operatr;
public:
    bool op_flag;
    stack_element(int inp_operand): operand(inp_operand), op_flag(true) {}
    char oprtr() const {return operatr;}
    stack_element(char inp_operatr): operatr(inp_operatr), op_flag(false) {}
    int oprnd() const {return operand;}
    void print();
};

void stack_element ::  print() {
    cout << operand << endl;
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
        }
    }
}

int main()
{
    std::string s;
    getline(std::cin, s);
    enum states{OPERATOR, OPERATION};
    plz_stack stack;
    char c, cur_state;
    int x = 0;
    s += ' ';
    for(char op : s)
    {
        if (op == ' ') {
            if (cur_state == OPERATION){
                stack.push(stack_element(c));
            }
            else stack.push(stack_element(x));
            x = 0;
        }
        else if ('0' <= op && op <= '9') {
            x = x * 10 + op - '0';
            cur_state = OPERATOR;
        }
        else {
            c = op;
            cur_state = OPERATION;
        }
    }
    analyse(stack);
    stack.top().print();
    stack.pop();
}