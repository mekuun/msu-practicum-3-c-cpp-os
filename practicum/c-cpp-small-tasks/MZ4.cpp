#include <iostream>
#include <cmath>
#include <cstring>

using std::cout, std::cin, std::endl;

char* left(char* str, int N) {//изменяет строку таким образом, что возвращаемый указатель, является указателем на N первых символов у строки str,
    if(N<=0) return nullptr;
    if (strlen(str) < (size_t)N) return str;
    str[N] = '\0';
    return str;
}

unsigned long left(unsigned long num, int N) {//возвращает число из N первых цифрр исходного числа num.
    int size = trunc(log10(num)) + 1; //длина числа
    if (size < N) return num;
    return num /= pow(10, size - N);

}


int main(){
    char str[20];
    char my_lovely_string[101];
    unsigned long my_lovely_number;
    int N;

    cin.getline(str, 8);
    if (!(strcmp(str, "string"))) {
        cin.getline(my_lovely_string, 101);
        cin >> N;
        cout << left(my_lovely_string, N) << endl;
        return 0;
    }
    if (!(strcmp(str, "number"))) {
        cin >> my_lovely_number;
        cin >> N;
        cout << left(my_lovely_number, N) << endl;
        return 0;
    }
}