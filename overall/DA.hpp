#pragma once

#include "const_v.hpp"

struct __DA { // umol
    double __v, I;

    double rest() { return 0.05; }

    __DA() : __v(rest()) {}

    void float_v(double k) { 
        I += 0.045 * k;
    }

    double v() { return __v; } // 获取实时多巴胺浓度

    double rare_f() {
        if (v() < 0.045) return v() - 0.045;      // 削弱
        else if (v() > 0.055) return v() - 0.055; // 强化
        else return 0;                            // 不改变
    }

    double f() { // 1 ms 内
        return rare_f() * 100; 
    }

    void t_run() { // 时间步 1 ms
        __v = __v + (rest() - v()) * (0.00011 / min_dt); 
        __v = std::max(0.0, std::min(0.2, __v + I));
        I *= (0.01 / min_dt);
    }

    __DA() {
        __v = rest();
        I = 0;
    }

} DA;




