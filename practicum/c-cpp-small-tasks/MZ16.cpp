#include <iostream>
using std::cout, std::cin, std::endl, std::cerr, std::string;


class Parser {
    void S();
    void A();
    void B();
    char c;
    void gc() {c = cin.get();}
public:
    bool analyzer();
};



void Parser::S(){
    if(c == 'a'){
        gc();
        A();
        B();
    }
    else if(c == 'b') {
        gc();
        B();
    }
    else throw c;
}
void Parser::A(){
    if(c == 'a'){
        gc();
        A();
    }
    else if(c == 'b') gc();
    else throw c;
}

void Parser::B(){
    if(c == 'b'){
        gc();
        B();
    }
}
bool Parser::analyzer(){
    try{
        gc();
        S();
        if(c != '\n'){
            return false;
        }
    }
    catch(char c){
        cerr << "Error in Lexcem: " << c << endl;
        return false;
    }
    return true;
}

int main(){
    Parser aaaa;
    if (aaaa.analyzer()){
        cout << "YES" << endl;
    }
    else cout << "NO" << endl;
    return 0;
}
