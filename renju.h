#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <utility>
#include <vector>
#include "tab.h"
using namespace std;
using ll = long long;
using Scr_Pos = pair<ll, int>;

const int COL = 11;
const int COL2 = COL * COL;
const ll inf = 1e14;

template <class T, int N>
struct Vector {
    T a[N];
    int n = 0;
    T *begin() { return a; }
    T *end() { return a + n; }
    void push_back(const T &t) { a[n++] = t; }
};

class Renju {
    int Map2[COL][COL];
    int *const Map = Map2[0];
    int turn;
    bool error = 0;

   public:
    Renju(const char *str) {
        set_turn(str);
        set_Map(str + 1);
    }

    int put() {
        if (error) return -1;

        const int max_deep = 5;
        int ret = -1;
        auto ret_eval = -inf - 1;
        Vector<Scr_Pos, COL2> childlist;
        for (int num = 0; num < COL2; num++) {
            if (!shouldSearch(num, max_deep + 1)) continue;
            Map[num] = 1;
            childlist.push_back({eval(0), num});
            Map[num] = 0;
        }
        sort(childlist.begin(), childlist.end(), greater<Scr_Pos>());

        for (auto &&child : childlist) {
            auto &&num = child.second;
            Map[num] = 1;
            auto now_eval = AlphaBeta(max_deep, 1, ret_eval, inf);
            // printf("%3d:%10lld\n", num, now_eval);
            Map[num] = 0;
            if (now_eval > ret_eval) {
                ret_eval = now_eval;
                ret = num;
            }
        }
        printf("eval = %lld, ", ret_eval);
        fflush(stdout);
        return ret;
    }

   private:
    bool shouldSearch(int num, int deep) const {
        const static int deep2level[] = {0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
        if (Map[num]) return 0;
        int x0 = num / COL, y0 = num % COL;
        for (int x = max(0, x0 - deep2level[deep]);
             x <= min(COL - 1, x0 + deep2level[deep]); x++) {
            for (int y = max(0, y0 - deep2level[deep]);
                 y <= min(COL - 1, y0 + deep2level[deep]); y++) {
                if (x == x0 && y == y0) continue;
                if (Map2[x][y]) return 1;
            }
        }
        return 0;
    }

    ll AlphaBeta(int deep, int player, ll alpha, ll beta) {
        {
            static const ll WIN = 1ll << 31;
            auto e = eval(player);
            if (deep == 0 || e <= -WIN || e >= WIN) return e;
        }
        // const static int max_width[] = {0, 50, 50, 50, 60, 70, 80, 90};
        Vector<Scr_Pos, COL2> childlist;
        for (int num = 0; num < COL2; num++) {
            if (!shouldSearch(num, deep)) continue;
            if (deep > 1) {
                Map[num] = player + 1;
                childlist.push_back({eval(player), num});
                Map[num] = 0;
            } else {
                childlist.push_back({0, num});
            }
        }
        if (player == 0) {
            sort(childlist.begin(), childlist.end(), greater<Scr_Pos>());
            // childlist.n=min(childlist.n,max_width[deep]);
            for (auto &&child : childlist) {
                auto &&num = child.second;
                Map[num] = 1;
                alpha = max(alpha, AlphaBeta(deep - 1, !player, alpha, beta));
                Map[num] = 0;
                if (beta <= alpha) break;
            }
            return alpha;
        } else {
            sort(childlist.begin(), childlist.end(), less<Scr_Pos>());
            // childlist.n=min(childlist.n,max_width[deep]);
            for (auto &&child : childlist) {
                auto &&num = child.second;
                Map[num] = 2;
                beta = min(beta, AlphaBeta(deep - 1, !player, alpha, beta));
                Map[num] = 0;
                if (beta <= alpha) break;
            }
            return beta;
        }
    }

    ll eval(int player) const {
        ll ret = 0;
        if (ret) return ret;
        // 计算横竖的得分
        for (int x = 0; x < COL; x++) {
            int code1 = 0, code2 = 0;
            for (int y = 0; y < N - 1; y++) {
                code1 = code1 * 3 + Map2[x][y];
                code2 = code2 * 3 + Map2[y][x];
            }
            for (int y = N - 1; y < COL; y++) {
                (code1 = code1 * 3 + Map2[x][y]) %= M;
                (code2 = code2 * 3 + Map2[y][x]) %= M;
                ret += TABLE[code1][player] + TABLE[code2][player];
            }
        }
        //计算斜向下的得分 y=0
        for (int x_ = 0; x_ < COL - N; x_++) {
            int x = x_, y = 0;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x++, y++;
            }
            for (; x < COL; x++, y++) {
                (code = code * 3 + Map2[x][y]) %= M;
                ret += TABLE[code][player];
            }
        }
        //计算斜向下的得分 x=0
        for (int y_ = 1; y_ <= COL - N; y_++) {
            int x = 0, y = y_;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x++, y++;
            }
            for (; y < COL; x++, y++) {
                (code = code * 3 + Map2[x][y]) %= M;
                ret += TABLE[code][player];
            }
        }
        //计算斜向上的得分 y=0
        for (int x_ = N - 1; x_ < COL; x_++) {
            int x = x_, y = 0;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x--, y++;
            }
            for (; x >= 0; x--, y++) {
                (code = code * 3 + Map2[x][y]) %= M;
                ret += TABLE[code][player];
            }
        }
        //计算斜向上的得分 x=COL-1
        for (int y_ = 1; y_ <= COL - N; y_++) {
            int x = COL - 1, y = y_;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x--, y++;
            }
            for (; y < COL; x--, y++) {
                (code = code * 3 + Map2[x][y]) %= M;
                ret += TABLE[code][player];
            }
        }
        return ret;
    }

    void set_turn(const char *str) {
        if (str[0] == 'B')
            turn = 1;
        else if (str[0] == 'W')
            turn = 2;
        else
            error = 1;
    }

    void set_Map(const char *str) {
        if (strlen(str) != COL2) {
            error = 1;
            return;
        }
        for (int i = 0; i < COL2; i++) {
            if ('0' <= str[i] && str[i] <= '2') {
                Map[i] = str[i] - '0';
            } else {
                error = 1;
                return;
            }
        }
        if (turn == 2) {
            turn = 1;
            for (int i = 0; i < COL2; i++) {
                if (Map[i] != 0) Map[i] ^= 3;
            }
        }
    }
};