#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using std::cout, std::cin, std::endl, std::ostream, std::istream, std::strcpy;
enum {INCREMENT = 64};

class mstring{
    char* string;
    unsigned int mem_sz;

public:
    mstring(){
        string = new char[1];
        string[0]=0;
        mem_sz=0;
    }
    mstring(const char* str) {mem_sz = strlen(str) + 1; string = new char[mem_sz]; strcpy(string, str);}
    mstring(const mstring & op){mem_sz = strlen(op.string) + 1; string = new char[mem_sz]; strcpy(string, op.string);}
    ~mstring(){
        delete[] string;
    }

    //functions
    int length() const; //OK
    bool isempty() const; //OK
    void add(char c); //OK
    void add(const char* c); //OK
    void insert(char c,int i); //OK
    void insert(const char* c,int i); // OK
    void print() const; //OK
    void del(int i); //OK
    void del(int i, int j);//OK
    int search(const char* str) const; //OK
    void replace(const char* sub_str, const char *new_str); //OK

    //operators
    mstring operator+(const mstring& op) const;
    friend mstring operator+(const char* x, const mstring& op);
    mstring operator*(int x) const;
    friend mstring operator*(int x, const mstring& op);
    const mstring& operator=(const mstring& op);
    bool operator>(const mstring& op) const;
    bool operator<(const mstring& op) const;
    bool operator>=(const mstring& op) const;
    bool operator<=(const mstring& op) const;
    bool operator==(const mstring& op) const;
    char& operator[](int index);
    friend ostream& operator<<(ostream& os, const mstring& op);
    friend istream& operator>>(istream& is, mstring& op);
};
//functions
int mstring::length() const{
    return strlen(string);
}

bool mstring::isempty() const{
    return !strlen(string);
}

void mstring::add(char c){
    if (mem_sz == strlen(string)){
        char *temp = new char[mem_sz + INCREMENT];
        mem_sz += INCREMENT;
        delete[] string;
        string = temp;
    }
    string[strlen(string) + 1 ] = '\0';
    string[strlen(string)] = c;

}

void mstring::add(const char* c){
    char* temp = new char[strlen(string) + strlen(c) + 1];
    mem_sz = strlen(string) + strlen(c) + 1;
    strcpy(temp, string);
    strcat(temp, c);
    delete[] string;
    string = temp;
}

void mstring::insert(char c, int i){
    char* temp = new char[strlen(string) - i + 1];
    strcpy(temp, string + i);
    string[i]='\0';
    (*this).add(c);
    (*this).add(temp);
    delete[] temp;
}
void mstring::insert(const char *c, int i){
    char *temp = new char[strlen(string) - i + 1];
    strcpy(temp, string + i);
    string[i]='\0';
    (*this).add(c);
    (*this).add(temp);
    delete[] temp;
}

void mstring::del(int i){
    char *temp = new char[strlen(string) + 1];
    strncpy(temp, string, i);
    temp[i] = '\0';
    strcat(temp, &string[i + 1]);
    delete[] string;
    string = temp;
}

void mstring::del(int i, int j){
    char *temp = new char[strlen(string) + 1];
    strncpy(temp, string, i);
    temp[i] = '\0';
    strcat(temp, &string[j + 1]);
    delete[] string;
    string = temp;
}

int mstring::search(const char* str) const{
    return strstr (string,str) == nullptr? -1:strstr (string,str) - string;
}

void mstring::replace(const char* sub_str, const char *new_str){
    int res = strstr (string,sub_str) == nullptr? -1:strstr (string,sub_str) - string;
    if (res == -1) return;
    char *temp = new char[strlen(string) + strlen(new_str) - strlen(string) + 1];
    strcpy(temp, string);
    temp[res] = '\0';
    strcat(temp, new_str);
    temp[res + strlen(new_str)] = '\0';
    if (strlen(temp) < strlen(string)) {
        strcat(temp, &string[res + strlen(sub_str)]);
    }
    delete[] string;
    string = temp;
}

void mstring::print() const{
    cout << string << endl;
}

//operators

mstring mstring :: operator+(const mstring & op) const{
    mstring tmp = *this;
    tmp.add(op.string);
    return tmp;
}

mstring operator+(const char* x, const mstring& op)
{
    mstring ans(x);
    ans.add(op.string);
    return ans;
}

mstring mstring::operator*(int x) const
{
    mstring ans;
    if (x == 0) return ans;
    for(int i=0; i < x; i++) ans.add(string);
    return ans;
}
mstring operator*(int x, const mstring& op)
{
    mstring ans;
    ans = op;
    return ans * x;
}

const mstring& mstring :: operator=(const mstring& op){
    if (&op == this) return *this;
    delete []string;
    mem_sz = op.mem_sz;
    string = new char[mem_sz];
    strcpy(string, op.string);
    return *this;
}

bool mstring :: operator>(const mstring& op) const{
    if (strcmp(op.string, this->string) < 0) return true;
    return false;
}

bool mstring :: operator<(const mstring& op) const{
    if (strcmp(op.string, this->string) > 0) return true;
    return false;
}

bool mstring :: operator>=(const mstring& op) const{
    return (!(*this < op));
}

bool mstring :: operator<=(const mstring& op) const{
    return (!(*this > op));
}

bool mstring :: operator==(const mstring& op) const{
    return ((*this <= op) && (*this >= op));
}

char& mstring :: operator[](int index){
    return this->string[index];
}

ostream& operator<<(ostream& os, const mstring& op){
    os << op.string;
    return os;
}

istream& operator>>(istream& is, mstring& op) {
    char c;
    delete[] op.string;
    op.string = new char[INCREMENT];
    int count = 0;
    while (cin.get(c) && (c != '\n') && (!is.eof())) {
        op.string[count] = c;
        count++;
        if (count >= op.mem_sz) {
            char* tmp = new char[count];
            strcpy(tmp, op.string);
            delete[] op.string;
            op.string = new char[count + INCREMENT];
            op.mem_sz += INCREMENT;
            strcpy(op.string, tmp);
            delete[] tmp;
        }
    }
    op.string[count] = '\0';
    return is;
}

