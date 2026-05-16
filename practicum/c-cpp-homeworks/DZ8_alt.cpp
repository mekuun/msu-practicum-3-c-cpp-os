#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::string,std::vector, std::stoi;
enum commands{IRB, IRA, ICB, ICA, DR, DC, SR, SC, T, ERR, b, a};

class Matrix
{
    vector <int> v;
    int n, m;
public:
    Matrix(int x, int y);
    void trans();
    void insert_row(int num, char pos);
    void insert_column(int num, char pos);
    void delete_row(int num);
    void delete_column(int num);
    void swap_rows(int num1, int num2);
    void swap_columns(int num1, int num2);
    void print() const;
};

Matrix::Matrix(int x, int y)
{
    int tmp;
    n = x;
    m = y;
    for(int i=0; i < x * y; i++) {
        scanf("%d", &tmp);
        v.push_back(tmp);
    }
}

void Matrix::trans()
{
    vector <int> tmp;
    for (int j=0; j < m; j++) for (int i=0; i < n; i++) tmp.push_back(v[i * m + j]);
    v = tmp;
    int x = n;
    n = m;
    m = x;
}

void Matrix::insert_row(int num, char pos)
{
    if (num > 0 && num <= n)
    {
        if (pos == b) num--;
        int x;
        for(int j=0; j < m; j++)
        {
            scanf("%d", &x);
            v.insert(v.begin() + num * m + j, x);
        }
        n++;
    }
}

void Matrix::insert_column(int num, char pos)
{
    if (num > 0 && num <= m)
    {
        if (pos == b) num--;
        int x;
        for(int i=0; i < n; i++)
        {
            scanf("%d", &x);
            v.insert(v.begin() + num + i * m + i, x);
        }
        m++;
    }
}

void Matrix::delete_row(int num)
{
    if (num > 0 && num <= n)
    {
        num--;
        for(int j=0; j < m; j++) v.erase(v.begin() + num * m);
        n--;
    }
}

void Matrix::delete_column(int num)
{
    if (num > 0 && num <= m)
    {
        num--;
        for(int i=n-1; i >= 0; i--) v.erase(v.begin() + num + m * i);
        m--;
    }
}

void Matrix::swap_rows(int num1, int num2)
{
    if (num1 > 0 && num1 <= n && num2 > 0 && num2 <= n && (num1 != num2)) {
        int tmp;
        num1--;
        num2--;
        for(int j=0; j < m; j++)
        {
            tmp = v[num1 * m + j];
            v[num1 * m + j] = v[num2 * m + j];
            v[num2 * m + j] = tmp;
        }
    }
}

void Matrix::swap_columns(int num1, int num2)
{
    if (num1 > 0 && num1 <= m && num2 > 0 && num2 <= m && (num1 != num2)) {
        int tmp;
        num1--;
        num2--;
        for(int i=0; i < n; i++)
        {
            tmp = v[num2 + m * i];
            v[num2 + m * i] = v[num1 + m * i];
            v[num1 + m * i] = tmp;
        }
    }
}

void Matrix::print() const
{
    for(int i=0; i < n; i++) {
        for(int j=0; j < m; j++)
        {
            cout << v[m * i + j] << " ";
        }
        cout << endl;
    }
}

int parse(int argc, char **argv){
    if(argc==2 && !strcmp(argv[1], "-t")) return T;
    if(argc==3){
        if(!strcmp(argv[1], "-irb")) return IRB;
        else if(!strcmp(argv[1], "-ira")) return IRA;
        else if(!strcmp(argv[1], "-icb")) return ICB;
        else if(!strcmp(argv[1], "-ica")) return ICA;
        else if(!strcmp(argv[1], "-dr")) return DR;
        else if(!strcmp(argv[1], "-dc")) return DC;
        return ERR;
    }
    if(argc==4){
        if(!strcmp(argv[1], "-sr")) return SR;
        else if(!strcmp(argv[1], "-sc")) return SC;
        return ERR;
    }
    return ERR;
}

int main(int argc, char ** argv){
    int n, m;
    cin >> n >> m;
    Matrix mat(n,m);
    int mode = parse(argc, argv);
    switch (mode){
        case T: {mat.trans(); break;}
        case IRB: {mat.insert_row(atoi(argv[2]), b); break;}
        case IRA: {mat.insert_row(atoi(argv[2]), a); break;}
        case ICB: {mat.insert_column(atoi(argv[2]), b); break;}
        case ICA: {mat.insert_column(atoi(argv[2]), a); break;}
        case DR: {mat.delete_row(atoi(argv[2])); break;}
        case DC: {mat.delete_column(atoi(argv[2])); break;}
        case SR: {mat.swap_rows(atoi(argv[2]), atoi(argv[3])); break;}
        case SC: {mat.swap_columns(atoi(argv[2]), atoi(argv[3])); break;}
        default: break;
    }
    mat.print();
}