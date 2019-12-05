
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
    Renju renju(
          "B0000000000000000000000000000000000000000201010002010200021211020002111122000000010200000002010000000000020000000000000000" //81
        //   "B0000000000000000000000000000000000000000201010002010200021211020002111122000000011200000002010000000000220000000000000000" //93
        // "B0000000000000000000000000000000000000000201010002010200021211020002111122000000011200000002011000000000222000000000000000" //45
    );
    for (int i = 0; i < 1; i++) printf("%d\n", renju.put());
        cout << "time used: " <<  (clock() - start)/1000. << "sec" << endl;
}