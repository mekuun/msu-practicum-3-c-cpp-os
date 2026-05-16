#include <iostream>
using std::cout, std::cin, std::endl, std::cerr, std::string;
class Parser
{
    char c;
public:
    void analyzer();
    void gc();
    void S();
};
void Parser::gc()
{
    cin.get(c);
}
void Parser::analyzer()
{
    try
    {
        gc();
        if (c == 'a') {
            cout << "2";
            gc();
            S();
            cout << "a";
        }
        else if (c == 'b') {
            gc();
            S();
            cout << "b";
        }
        else throw c;
    }
    catch(char c) {cerr << "Error in: " << c << endl;}
}
void Parser::S()
{
    if (c == 'a') {
        cout << "2";
        gc();
        S();
        cout << "a";
    }
    else if (c == 'b') {
        gc();
        S();
        cout << "b";
    }
    else if (c != '\n') throw c;
}
int main()
{
    Parser x;
    x.analyzer();
}