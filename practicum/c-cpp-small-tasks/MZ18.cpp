#include<iostream>
#include<stack>
using namespace std;

int main(){
    using cool_stack = stack<int>;
    cool_stack st;
    char c;
    int num = 0, num1 = 0;
    c = cin.get();
    while (c != '\n'){
        if (isdigit(c)){
            num = c - '0';
            c = cin.get();
            while(c != ' ' && c !='\n'){
                num = num* 10 + (c - '0');
                c = cin.get();
            }
            st.push(num);
        }
        else{
            num1 = st.top();
            st.pop();
            if (c == '+') {num = st.top() + num1; st.pop();}
            else if (c == '-') {num = st.top() - num1; st.pop();}
            else if (c == '*') {num = st.top() * num1; st.pop();}
            else if (c == '/') {num = st.top() / num1; st.pop();}
            else if (c == '@') num = -num1;
            st.push(num);
        }
        c = cin.get();
    }
    cout << st.top();
}