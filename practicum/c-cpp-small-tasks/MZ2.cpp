#include<iostream>
using std::cout; using std::endl;

class Rect {
    int x, y;
    unsigned int wd, hd;

public:
    Rect() {
        x = 0;
        y = 0;
        wd = 1;
        hd = 1;
    }

    Rect(int x, int y, unsigned int wd, unsigned int hd) {
        this->x = x;
        this->y = y;
        this->wd = wd;
        this->hd = hd;
    }

    Rect(unsigned int w) {
        this->x = 0;
        this->y = 0;
        this->wd = w;
        this->hd = w;
    }

    void print_corner() {
        cout << '(' << x << ',' << y << ')' << endl;
    }

    void print_sz() {
        cout << "wd=" << wd << " hd=" << hd << endl;
    }

    int area() {
        return wd * hd;
    }

    int perimeter() {
        return 2 * wd + 2 * hd;
    }

    bool intersect(Rect r) {
        int x1 = x + wd;
        int y1 = y + hd;
        int r_x = r.x;
        int r_y = r.y;
        int r_x1 = r_x + r.wd;
        int r_y1 = r_y + r.hd;
        return ((x <= r_x1) && (x1 >= r_x) && (y1 >= r_y) && (y <= r_y1));
    }
};
