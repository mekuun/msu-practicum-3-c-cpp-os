#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <cstdio>
#include <cstring>
#include<map>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::string, std::list, std::stoi, std::map;
enum commands{AF = 0, AE = 1, IB = 2, IA = 3, D = 4, SA = 5, SD = 6, MF = 7, ME = 8, UNKNOWN_COMMAND = 9};

void Print(list<int> & list_inp){
    for(list<int>::iterator it = list_inp.begin(); it != list_inp.end(); ++it ){
        cout << *it << " ";
    }
    cout << endl;
}
int main(int argc, char *argv[]){
    list<int> numbers;
    int val = 0;
    while (scanf("%d", &val) > 0) {
        numbers.list::push_back(val);
    }
    char* cmd = argv[1];
    int cmd_n;

    if(strcmp(cmd, "-af")==0) cmd_n =  AF;
    else if(strcmp(cmd, "-ae")==0) cmd_n =  AE;
    else if(strcmp(cmd, "-ib")==0) cmd_n =  IB;
    else if(strcmp(cmd, "-ia")==0) cmd_n =  IA;
    else if(strcmp(cmd, "-d")==0) cmd_n =  D;
    else if(strcmp(cmd, "-sa")==0) cmd_n =  SA;
    else if(strcmp(cmd, "-sd")==0) cmd_n =  SD;
    else if(strcmp(cmd, "-mf")==0) cmd_n =  MF;
    else if(strcmp(cmd, "-me")==0) cmd_n =  ME;
    else cmd_n = UNKNOWN_COMMAND;

    switch(cmd_n){
        case AF: {
            if (argc != 3) {
                Print(numbers);
                break;
            }
            numbers.push_front(stoi(argv[2]));
            Print(numbers);
            break;
        }
        case AE: {
            if (argc != 3) {
                Print(numbers);
                break;
            }
            numbers.push_back(stoi(argv[2]));
            Print(numbers);
            break;
        }
        case IB: {
            if (argc != 4) {
                Print(numbers);
                break;
            }
            for(list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
                if(*it == stoi(argv[3])) {
                    numbers.insert(it, stoi(argv[2]));
                    break;
                }
            }
            Print(numbers);
            break;
        }
        case IA: {
            if (argc != 4) {
                Print(numbers);
                break;
            }
            for(list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
                if(*it == stoi(argv[3])) {
                    numbers.insert(++it, stoi(argv[2]));
                    break;
                }
            }
            Print(numbers);
            break;
        }
        case D:{
            if (argc != 3) {
                Print(numbers);
                break;
            }
            for(list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
                if(*it == stoi(argv[2])) {
                    numbers.erase(it);
                    break;
                }
            }
            Print(numbers);
            break;
        }
        case SA: {
            if(argc != 2) {
                Print(numbers);
                break;
            }
            numbers.sort();
            Print(numbers);
            break;
        }
        case SD: {
            if(argc != 2) {
                Print(numbers);
                break;
            }
            numbers.reverse();
            numbers.sort();
            numbers.reverse();
            Print(numbers);
            break;
        }
        case MF: {
            if(argc != 2) {
                Print(numbers);
                break;
            }
            list<int>::iterator max_elem;
            int max;
            if(!numbers.empty()) {
                max_elem = (numbers.begin());
                max = *max_elem;
            }
            for(list<int>::iterator it = numbers.begin(); it != numbers.end(); it++){
                if(*it > max) {
                    max_elem = it;
                    max=*it;
                }
            }
            numbers.erase(max_elem);
            numbers.push_front(max);
            Print(numbers);
            break;
        }
        case ME: {
            if(argc!=2) {
                Print(numbers);
                break;
            }
            list<int>::iterator max_it;
            int max;
            if(!numbers.empty()) {
                max_it = (numbers.begin());
                max = *max_it;
            }
            for(list<int>::iterator it=numbers.begin(); it!=numbers.end(); it++){
                if(*it>max) {
                    max_it=it;
                    max=*it;
                }
            }
            numbers.erase(max_it);
            numbers.push_back(max);
            Print(numbers);
            break;
        }
        default: Print(numbers); break;
    }
}

