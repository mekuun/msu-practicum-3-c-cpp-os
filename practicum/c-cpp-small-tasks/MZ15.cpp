#include <iostream>
using std::cout, std::cin, std::endl, std::cerr, std::string;
char c;

void gc()
{
    c = cin.get();
}


string Parser(){
    enum states {H, AC, B};
    char state = H;
    string ans = "";
    gc();

    do{
        switch (state) {
            case H:
                if (c == 'a') {
                    state = AC;
                    ans += 'a';
                    gc();
                } else throw c;
                break;
            case B:
                if (c == 'a'){
                    state = AC;
                    ans += 'a';
                    gc();
                }
                else if (c == '\n'){
                    return ans;
                }
                else throw c; break;
            case AC:
                if (c == 'd'){
                    ans += 'd';
                    gc();
                }
                else if (c == 'a'){
                    state = B;
                    ans += 'a';
                    gc();
                }
                else throw c;
                break;

        };
    }while(true);
}

int main()
{
    string aaaaa = "";
    try{
        aaaaa = Parser();
        cout << aaaaa << endl;
    }
    catch(char c)
    {
        cerr << "Error in Lexcem: " << c << endl;
    }
    return 0;
}