#include <iostream>
#include <stack>
using namespace std;
class item
{
    int x;
    char c;
    bool I_am_operand;
    public:
        item(int x_): x(x_), I_am_operand(true) {}
        item(char c_): c(c_), I_am_operand(false) {}
        bool is_operand() const {return I_am_operand;}
        char get_char() const {return c;}
        int get_int() const {return x;}
        void print() const {cout << ((I_am_operand) ? x : c) << endl;}
};

void do_poliz(stack<item> &stack)
{
    char oper = stack.top().get_char();
    stack.pop();
    int op1, op2;

    if (stack.top().is_operand()) op1 = stack.top().get_int();
    else {do_poliz(stack); op1 = stack.top().get_int();}
    stack.pop();

    if (oper == '@') stack.push(item(-op1));
    else {
        if (stack.top().is_operand()) op2 = stack.top().get_int();
        else {do_poliz(stack); op2 = stack.top().get_int();}
        stack.pop();

        if (oper == '+') stack.push(item(op2 + op1));
        if (oper == '-') stack.push(item(op2 - op1));
        if (oper == '/') stack.push(item(op2 / op1));
        if (oper == '*') stack.push(item(op2 * op1));
    }
}

int main()
{
    std::string s;
    getline(std::cin, s);
    enum states{NUMBER, OPERATION};
    stack<item> stack;
    char c, tmp, cur_state;
    int x = 0;
    s += ' ';
    for(char tmp : s) 
    {
        if (tmp == ' ') {
            stack.push((cur_state == OPERATION) ? item(c) : item(x));
            x = 0;
        }
        else if ('0' <= tmp && tmp <= '9') {x = x * 10 + tmp - '0'; cur_state = NUMBER;}
        else {c = tmp; cur_state = OPERATION;}
    }
    do_poliz(stack);
    stack.top().print();
    stack.pop();
}