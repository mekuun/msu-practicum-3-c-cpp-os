#include <cstdio>
#include <iostream>
#include <cmath>
using std::cout, std::cin, std::endl;
class Quotient {
    int numerator;
    unsigned denominator;
public:
    Quotient(int n = 0, int dn = 1) {
        if (dn > 0) {
            numerator = n;
            denominator = dn;
        } else if (dn < 0) {
            numerator = -n;
            denominator = -dn;
        } else if (dn == 0) {
            numerator = n;
            denominator = 1;
        }
        int cd = common_div(abs(numerator), abs(int(denominator)));
        numerator /= cd;
        denominator /= cd;
    }

    int common_div (int numerator, unsigned denominator){
        if (denominator == 0)
            return numerator;
        else
            return common_div (denominator, numerator % denominator);
    }

    void print() {
        if (denominator == 1) {
            cout << numerator << endl;
            return;
        }
        cout << numerator << '/' << denominator << endl;
        return;
    }
};

