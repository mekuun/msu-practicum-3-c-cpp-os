#include <cstdio>
#include <iostream>
#include <cstring>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::endl;
#define SET_OX_OY oX = abs(start[0] - end[0]); oY = abs((start[1] - '0') - (end[1] - '0'))

class Figure {
public:
    virtual bool move(const char start[3], const char end[3]) = 0;
    bool isWithinBoardLimits(const char start[3], const char end[3]) const {
        return !(start[0] > 'h' || start[0] < 'a' || start[1] - '0' > 8 || start[1] - '0' < 1 ||
                 end[0] > 'h' || end[0] < 'a' || end[1] - '0' > 8 || end[1] - '0' < 1);
    }
};

class King : public Figure {
public:
    virtual bool move(const char start[3], const char end[3]);
};

class Queen : public Figure {
public:
    virtual bool move(const char start[3], const char end[3]);
};

class Knight : public Figure {
public:
    virtual bool move(const char start[3], const char end[3]);
};

class Bishop : public Figure {
public:
    virtual bool move(const char start[3], const char end[3]);
};

class Rook : public Figure {
public:
    virtual bool move(const char start[3], const char end[3]);
};

bool King::move(const char start[3], const char end[3]) {
    if (!isWithinBoardLimits(start, end)) return false;
    int oX, oY;
    SET_OX_OY;
    return (oX == 1 && oY == 0) || (oY == 1 && oX == 0) || (oY == 1 && oX == 1);
}

bool Queen::move(const char start[3], const char end[3]) {
    if (!isWithinBoardLimits(start, end)) return false;
    int oX, oY;
    SET_OX_OY;
    return (oX == 0 || oY == 0 || oX == oY);
}

bool Knight::move(const char start[3], const char end[3]) {
    if (!isWithinBoardLimits(start, end)) return false;
    int oX, oY;
    SET_OX_OY;
    return (oY == 2 && oX == 1) || (oX == 2 && oY == 1);
}

bool Bishop::move(const char start[3], const char end[3]) {
    if (!isWithinBoardLimits(start, end)) return false;
    return abs(start[0] - end[0]) == abs((start[1] - '0') - (end[1] - '0'));
}

bool Rook::move(const char start[3], const char end[3]) {
    if (!isWithinBoardLimits(start, end)) return false;
    int oX, oY;
    SET_OX_OY;
    return (oX == 0 || oY == 0);
}

class ChessChecker {
private:
    char figure, start[3], end[3];
    Figure *bro;
public:
    bool check() const;
    ChessChecker();
    ~ChessChecker();
};

bool ChessChecker::check() const {
    return bro->move(start, end);
}

ChessChecker::ChessChecker() {
    cin >> figure >> start[0] >> start[1] >> end[0] >> end[1];
    switch(figure) {
        case 'K': bro = new King; break;
        case 'Q': bro = new Queen; break;
        case 'N': bro = new Knight; break;
        case 'B': bro = new Bishop; break;
        case 'R': bro = new Rook; break;
    }
}

ChessChecker::~ChessChecker() {
    delete bro;
}

int main() {
    ChessChecker x;
    cout << (x.check() ? "YES" : "NO") << endl;
    return 0;
}
