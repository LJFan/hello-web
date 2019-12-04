#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include "tab.h"
using namespace std;
using ll = long long;

const int COL = 11;
const int COL2 = COL * COL;
const ll inf = 1e14;

class Renju {
    int Map2[COL][COL];
    int *const Map;
    int turn;
    bool error;

   public:
    Renju(const char *str) : Map(Map2[0]) {
        error = 0;
        set_turn(str);
        set_Map(str + 1);
    }

    int put() {
        if (error) return -1;
        int ret = -1;
        auto ret_eval = -inf;
        for (int num = 0; num < COL2; num++) {
            if (!shouldSearch(num, 3)) continue;
            Map[num] = 1;
            // printf("%d:", num);
            auto now_eval = AlphaBeta(3, 1);
            // printf("%d: %lld\n", num, now_eval);
            if (now_eval > ret_eval) {
                ret_eval = now_eval;
                ret = num;
            }
            Map[num] = 0;
        }
        return ret;
    }

   private:
    bool shouldSearch(int num, int deep) {
        if (Map[num]) return 0;
        int x0 = num / COL, y0 = num % COL;
        for (int x = max(0, x0 - (deep + 2) / 2);
             x <= min(COL - 1, x0 + (deep + 2) / 2); x++) {
            for (int y = max(0, y0 - (deep + 2) / 2);
                 y <= min(COL - 1, y0 + (deep + 2) / 2); y++) {
                if (x == x0 && y == y0) continue;
                if (Map2[x][y]) return 1;
            }
        }
        return 0;
    }
    ll AlphaBeta(int deep, int player, ll alpha = -inf, ll beta = inf) {
        if (deep == 0) return eval(player);
        if (player == 0) {
            for (int num = 0; num < COL2; num++) {
                if (!shouldSearch(num, deep)) continue;
                Map[num] = 1;
                alpha = max(alpha, AlphaBeta(deep - 1, !player, alpha, beta));
                Map[num] = 0;
                if (beta <= alpha) return alpha;
            }
        } else {
            for (int num = 0; num < COL2; num++) {
                if (!shouldSearch(num, deep)) continue;
                Map[num] = 2;
                beta = min(beta, AlphaBeta(deep - 1, !player, alpha, beta));
                Map[num] = 0;
                if (beta <= alpha) return beta;
            }
        }
        return (alpha + beta) / 2;
    }
    ll eval(int player) const {
        ll ret = 0;
        const static int mod = 3 * 3 * 3 * 3 * 3;
        for (int x = 0; x < COL; x++) {
            int code1 = 0, code2 = 0;
            for (int y = 0; y < N - 1; y++) {
                code1 = code1 * 3 + Map2[x][y];
                code2 = code2 * 3 + Map2[y][x];
            }
            for (int y = N - 1; y < COL; y++) {
                (code1 = code1 * 3 + Map2[x][y]) %= mod;
                (code2 = code2 * 3 + Map2[y][x]) %= mod;
                ret += TABLE[code1][player] + TABLE[code2][player];
            }
        }
        for (int x_ = 0; x_ < COL - N; x_++) {
            int x = x_, y = 0;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x++, y++;
            }
            for (; x < COL; x++, y++) {
                (code = code * 3 + Map2[x][y]) %= mod;
                ret += TABLE[code][player];
            }
        }
        for (int y_ = 1; y_ <= COL - N; y_++) {
            int x = 0, y = y_;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x++, y++;
            }
            for (; y < COL; x++, y++) {
                (code = code * 3 + Map2[x][y]) %= mod;
                ret += TABLE[code][player];
            }
        }
        for (int x_ = N; x_ < COL; x_++) {
            int x = x_, y = 0;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x--, y++;
            }
            for (; x >= 0; x--, y++) {
                (code = code * 3 + Map2[x][y]) %= mod;
                ret += TABLE[code][player];
            }
        }

        for (int y_ = 1; y_ <= COL - N; y_++) {
            int x = COL-1, y = y_;
            int code = 0;
            for (int i = 0; i < N - 1; i++) {
                code = code * 3 + Map2[x][y];
                x--, y++;
            }
            for (; y < COL; x--, y++) {
                (code = code * 3 + Map2[x][y]) %= mod;
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
        for (int i = 0; i < COL2; i++) {
            if (Map[i] != 0) Map[i] ^= 3;
        }
    }
};