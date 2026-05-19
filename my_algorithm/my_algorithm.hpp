#include <array>

namespace mtd {
    const double e = 2.7182818;
    // const double ie5 = 1.221403;
    // const double ie7 = 1.153565;
    const double ie10 = 1.105171;
    const double pi = 3.1415927;

    inline const std::array<double, 100> _iexp10 = []() {
        std::array<double, 100> arr;
        arr[0] = 1;
        for (int i = 1; i < 100; ++i) 
            arr[i] = arr[i - 1] / ie10;
        return arr;
    }();

    double iexp10(int x) {
        return x >= 100 ? 0 : _iexp10[x];
    }

}

namespace mtd { 
    template<typename tnt> struct point2 {
        tnt x, y;
    };

    template<typename tnt>
    bool operator <(const point2<tnt> &a, const point2<tnt> &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    template<typename tnt> struct point3 {
        tnt x, y, z;
    };

    template<typename tnt>
    bool operator <(const point3<tnt> &a, const point3<tnt> &b) {
        return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x < b.x;
    }
}

#include <random>

namespace mtd {
    std::random_device rand;
    std::mt19937 gen(rand());

    bool rand_bool(double k = 0.5) {
        return std::bernoulli_distribution(k)(gen);
    }
    double rand_double(double l, double r) { // [l, r)
        return std::uniform_real_distribution<double>(l, r)(gen);
    }
    int rand_int(int l, int r) { // [l, r)
        return std::uniform_int_distribution<int>(l, r - 1)(gen);
    }

}

namespace mtd {
    template<typename tnt> struct extnt {
        tnt _v, _lv;
        tnt &v() { return _v; }
        tnt &lv() { return _lv;}
        void bp() { _lv = _v; }
    };

    using exint = extnt<int>;
    using exdouble = extnt<double>;
}