#include <iostream>
#include <cstring>

using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream;

class Vector_2d_exc{
public:
     void print() const {cout << "Exception: one coordinate" << endl;};
};

class Vector_2d_exc_neg : public Vector_2d_exc{
    int coord;
public:
    Vector_2d_exc_neg(int coord_inp): coord(coord_inp){};
    Vector_2d_exc_neg(const Vector_2d_exc_neg& op): coord(op.coord){};
    void print() const {cout << "Exception: negative coordinate:" << coord << endl;};
};


class Vector_2d{
private:
    int x, y;
public:
    Vector_2d(int x_inp, int y_inp);
    Vector_2d(): x(0), y(0) {};
    Vector_2d(const Vector_2d& op): x(op.x), y(op.y){};
    friend ostream& operator<<(ostream& os, const Vector_2d& vec);
    friend istream& operator>>(istream& is, Vector_2d& vec);
};

Vector_2d::Vector_2d(int x_inp, int y_inp) {
    if (x_inp < 0) throw Vector_2d_exc_neg(x_inp);
    if (y_inp < 0) throw Vector_2d_exc_neg(y_inp);
    x = x_inp; y = y_inp;
}

ostream& operator<<(ostream& os, const Vector_2d& vector_inp)
{
    os << "(" << vector_inp.x << "," << vector_inp.y << ")";
    return os;
}

istream& operator>>(istream& is, Vector_2d& vector_inp) {
    int cnt = scanf("%d %d", &vector_inp.x, &vector_inp.y);
    if (cnt == 1) {
        throw Vector_2d_exc();
    }
    else if (vector_inp.x < 0) throw Vector_2d_exc_neg(vector_inp.x);
    else if (vector_inp.y < 0) throw Vector_2d_exc_neg(vector_inp.y);
    return is;
}

int main()
{
    try {
        Vector_2d vector;
        cin >> vector;
        cout << vector << endl;
    }
    catch(Vector_2d_exc_neg &e) {e.print();}
    catch(Vector_2d_exc &e) {e.print();}
    catch(...) {std::cout << "Unknown_Error\n";}
    return 0;
}

