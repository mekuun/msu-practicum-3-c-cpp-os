#include <iostream>
#include<cstdio>
enum {HR_ERR = 1, MIN_ERR = 2, SEC_ERR = 3, INP_ERR = 4};
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::stoi, std::string;

class Time_exc{
    int exc_code;
public:
    Time_exc(int i) {exc_code = i;}
    void print() const;
};

void Time_exc :: print() const {
    switch (exc_code) {
        case HR_ERR:
            cerr << "ERROR: wrong hour format" << endl;
            break;
        case MIN_ERR:
            cerr << "ERROR: wrong minute format" << endl;
            break;
        case SEC_ERR:
            cerr << "ERROR: wrong second format" << endl;
            break;
        case INP_ERR:
            cerr << "ERROR: wrong input" << endl;
            break;
        default:
            cerr << "UNKNOWN ERROR" << endl;
    }
}

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
    char urmom;
    int sukaa;
    is >> op.hours[0] >> op.hours[1];
    if (!(isdigit(op.hours[0]) && isdigit(op.hours[1]))) {
        throw(Time_exc(INP_ERR));
    }
    else{
        sukaa = (op.hours[0] - '0') * 10 + (op.hours[1] - '0');
        if ((sukaa < 0) || (sukaa > 23)) {
            throw (Time_exc(HR_ERR));
        }
    }
    op.hours[2] = '\0';

    is >> urmom;
    if (urmom != ':') {
        throw(Time_exc(INP_ERR));
    }

    is >> op.minutes[0] >> op.minutes[1];
    if (!(isdigit(op.minutes[0]) && isdigit(op.minutes[1]))) {
        throw(Time_exc(INP_ERR));
    }
    else{
        sukaa = (op.minutes[0] - '0') * 10 + (op.minutes[1] - '0');
        if ((sukaa < 0) || (sukaa > 59)) {
            throw (Time_exc(MIN_ERR));
        }
    }
    op.minutes[2] = '\0';

    is >> urmom;
    if (urmom != ':') {
        throw(Time_exc(INP_ERR));
    }

    is >> op.seconds[0] >> op.seconds[1];
    if (!(isdigit(op.seconds[0]) && isdigit(op.seconds[1]))) {
        throw(Time_exc(INP_ERR));
    }
    else{
        sukaa = (op.seconds[0] - '0') * 10 + (op.seconds[1] - '0');
        if ((sukaa < 0) || (sukaa > 59)) {
            throw (Time_exc(SEC_ERR));
        }
    }
    op.seconds[2] = '\0';

    if (!(is.peek() == '\n' || is.peek() == EOF)) {
        throw(Time_exc(INP_ERR));
    }
    return is;
}


int main(){
    try{
        Time i;
        cin >> i;
        cout << i << endl;
    }
    catch(Time_exc &e){
        e.print();
    }
    return 0;
}