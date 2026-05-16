#include <iostream>
#include<cstdio>
using namespace std;

class Time{
private:
    char hours[3], minutes[3], seconds[3];
public:
    friend ostream& operator<<(ostream& os, const Time& op);
    friend istream& operator>>(istream& is, Time& op);
};



ostream& operator<<(ostream& os, const Time& op){
    os << op.hours << "h " << op.minutes << "m " << op.seconds << "s ";
    return os;
}

istream& operator>>(istream& is, Time& op){
    is >> op.hours[0] >> op.hours[1];
    op.hours[2] = '\0';
    is.ignore();
    is >> op.minutes[0] >> op.minutes[1];
    op.minutes[2] = '\0';
    is.ignore();
    is >> op.seconds[0] >> op.seconds[1];
    op.seconds[2] = '\0';
    return is;
}

int main(){
Time i;
cin >> i;
Time pipi = i;
cout<<i<< endl;
cin >> i;
cout<<pipi<< endl;

return 0;
}