#include <iostream>
#include <cstring>

using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream;

template<typename AAAAAA>
AAAAAA maxn( AAAAAA* a, int len){
    AAAAAA maxi = a[0];
    for (int i = 1; i < len; i ++){
        if (a[i] > maxi) maxi = a[i];
    }
    return maxi;
}


template<>
const char* maxn<const char*>(const char** a, int len){
    int maxi = strlen(a[0]), maxin = 0;
    for (int i = 1; i < len; i ++){
        if (strlen(a[i]) > maxi) {maxi = strlen(a[i]); maxin = i;}
    }
    return a[maxin];
}