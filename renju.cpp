
//g++ renju.cpp -std=c++14 -O3 -Wall -shared -o renju.so
//g++ renju.cpp -std=c++14 -O3 -Wall -o renju.exe && renju.exe
#include "renju.h"

extern "C" int solve(const char *str) {
    Renju renju(str);
    return renju.put();
}

int main() {
    printf("%d\n",solve(
        "W0000000000000000000000000000000000000000000000000000000000021111000000020000000002000000000000000000000000000000000000000"
    ));
}