
//g++ renju.cpp -std=c++14 -O3 -Wall -shared -o renju.so
//g++ renju.cpp -std=c++14 -O3 -Wall -o renju.exe && renju.exe
#include "renju.h"

extern "C" int solve(const char *str) {
    Renju renju(str);
    return renju.put();
}

int main() {
    for (int i = 0; i < 5; i++)
        printf("%d\n", solve("W000000000000000000000000000000000000000000000000"
                             "0000000000021111000000020000000002000000000000000"
                             "000000000000000000000000"));
}