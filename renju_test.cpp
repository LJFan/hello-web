
//g++ renju.cpp -std=c++14 -O3 -Wall -shared -o renju.so
//g++ renju_test.cpp -std=c++14 -O3 -Wall -o renju.exe && renju.exe
#include "renju.h"
#include<iostream>
#include<ctime>

extern "C" int solve(const char *str) {
    Renju renju(str);
    return renju.put();
}

int main() {
    auto start = clock();
    for (int i = 0; i < 1; i++)
        printf("%d\n", solve(
            "W0000000000000000021000000000120100002021220000022112110002111201000012210000000001120000000002000000000000000000000000000"
        ));
        cout << "time used: " <<  (clock() - start)/1000. << "sec" << endl;
}