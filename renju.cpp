
#include "renju.h"

extern "C" int solve(const char *str) {
    Renju renju(str);
    return renju.put();
}
