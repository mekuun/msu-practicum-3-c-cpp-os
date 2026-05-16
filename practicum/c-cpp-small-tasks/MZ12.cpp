#include <iostream>
#include <cmath>
#include <string>
#include <map>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::string;
class Flower{
private:
    string colour;
    int petal_cnt = 0;
    static int count_pink;
    static int count_white;
public:
    Flower(string colour_inp, int petal_cnt_inp = 10);
    Flower(int petal_cnt_inp = 10);
    Flower(Flower &other);
    ~Flower();
    void static Print_flowers();
};

int Flower::count_pink = 0;
int Flower::count_white = 0;


Flower::Flower(string colour_inp, int petal_cnt_inp) {
    colour = colour_inp;
    petal_cnt = petal_cnt_inp;
    if ((colour != "pink")&&(colour != "white")){
        count_pink < count_white ? colour = "pink":colour = "white";
        if (count_pink == count_white) petal_cnt % 2 == 0? colour = "pink":colour = "white";
    }
    colour == "pink"? ++count_pink:++count_white;
}
Flower::Flower(int petal_cnt_inp) {
    petal_cnt = petal_cnt_inp;
    count_pink < count_white ? colour = "pink":colour = "white";
    if (count_pink == count_white) petal_cnt % 2 == 0? colour = "pink":colour = "white";
    colour == "pink"? ++count_pink:++count_white;
}
Flower::Flower(Flower &other){
    colour = other.colour;
    petal_cnt = other.petal_cnt;
    colour == "pink"? ++count_pink:++count_white;
}
Flower::~Flower(){
    colour == "pink"? --count_pink:--count_white;
}
void Flower::Print_flowers(){
    cout<<"White: "<<count_white<<" "<<"Pink: "<<count_pink<<endl;
}