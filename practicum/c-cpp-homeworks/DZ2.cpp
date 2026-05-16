#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using std::cout, std::cin, std::endl, std::ostream, std::istream;
enum {INCREMENT = 64};

class mstring{
    char* string;
    unsigned int mem_sz;

public:
    mstring(){
        string = new char[0];
        string[0]=0;
        mem_sz=0;
    }
    mstring(const char* str) {
        string = new char[strlen(str) + 1];
        strcpy(string, str);
        mem_sz = strlen(str)+1;

    }
    mstring(const mstring & other){
        string = new char[strlen(other.string) + 1];
        strcpy(string, other.string);
        mem_sz = other.mem_sz;
    }
    ~mstring(){
        delete[] string;
    }

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
};

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