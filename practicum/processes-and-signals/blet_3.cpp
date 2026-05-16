#include <iostream>
#include<cstdio>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::stoi, std::string;

class Pair{
public:
    virtual void next() = 0;
    virtual ~Pair(){};
    virtual void Print() = 0;
};

class Date : public Pair{
private:
    int month, day;
    int dim;
public:
    virtual void next();
    virtual void Print();
    Date(int m, int d);
    virtual ~Date(){};
    void dim_checker() {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                dim = 31;
                break;
            case 2:
                dim = 28;
                break;
            default:
                dim = 30;
                break;
        }
    }
};

Date::Date(int m, int d) {
    month = m; day = d;
    dim_checker();
}

void Date::next(){
    day ++;
    month += (day / dim);
    month %= (13);
    if (month == 0) ++month;
    day %= (dim + 1);
    if (day == 0) ++day;
    dim_checker();
}

void Date::Print(){
    cout << month << " m " << day << " d " << endl;
}


class Time : public Pair{
private:
    int hour, minute;
public:
    virtual ~Time(){};
    virtual void next();
    virtual void Print();
    Time(int h, int m): hour(h), minute(m){};
};

void Time::next(){
    minute ++;
    hour += (minute / 60);
    minute %= 60;
    hour %= 24;
}

void Time::Print() {
    cout << hour << " h " << minute << " m " << endl;

}

int main(){
    Pair *P[5];
    P[0] = new Date(4, 23);
    P[1] = new Time(23, 59);
    P[2] = new Date(12, 31);
    P[3] = new Time(9, 59);
    P[4] = new Date(2, 28);
    for(int i = 0; i < 5; i ++){
        P[i]->Print();
    }
    for(int i = 0; i < 5; i++){
        P[i]->next();
    }
    cout<<endl;
    for(int i = 0; i < 5; i ++){
        P[i]->Print();
    }
    for(int i = 0; i < 5; i ++){
        delete P[i];
    }
    return 0;
}