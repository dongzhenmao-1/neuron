#include <array>

namespace mtd {
    const double e = 2.7182818;
    // const double esqrt5 = 1.221403;
    // const double esqrt7 = 1.153565;
    const double esqrt10 = 1.105171;
    const double iesqrt10 = 1 / esqrt10;
    const double pi = 3.1415927;

    inline const std::array<double, 100> _iexp10 = []() {
        std::array<double, 100> arr;
        arr[0] = 1;
        for (int i = 1; i < 100; ++i) 
            arr[i] = arr[i - 1] * iesqrt10;
        return arr;
    }();

    double iexp10(int x) {
        if (x < 0) return 0;
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
    template<typename tnt>
    bool operator ==(const point2<tnt> &a, const point2<tnt> &b) {
        return a.x == b.x && a.y == b.y;
    }
    template<typename tnt>
    point2<tnt> operator +(const point2<tnt> &a, const point2<tnt> &b) {
        return point2<tnt>{a.x + b.x, a.y + b.y};
    }   

    template<typename tnt> struct point3 {
        tnt x, y, z;
    };
    template<typename tnt>
    bool operator <(const point3<tnt> &a, const point3<tnt> &b) {
        return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x < b.x;
    }
    template<typename tnt>
    bool operator ==(const point3<tnt> &a, const point3<tnt> &b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
    template<typename tnt>
    point3<tnt> operator +(const point3<tnt> &a, const point3<tnt> &b) {
        return point3<tnt>{a.x + b.x, a.y + b.y, a.z + b.z};
    }   

}

#include <unordered_map>

namespace std {
    template <>
    struct hash<mtd::point2<int>> {
        size_t operator()(const mtd::point2<int> &p) const {
            size_t hx = std::hash<int>{}(p.x);
            size_t hy = std::hash<int>{}(p.y);
            size_t seed = 0;
            seed ^= hx + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hy + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };

    template <>
    struct hash<mtd::point3<int>> {
        size_t operator()(const mtd::point3<int> &p) const {
            size_t hx = std::hash<int>{}(p.x);
            size_t hy = std::hash<int>{}(p.y);
            size_t hz = std::hash<int>{}(p.z);
            size_t seed = 0;
            seed ^= hx + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hy + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hz + 0x9e3779b9 + (seed << 6) + (seed >> 2);

            return seed;
        }
    };
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

    point2<int> rand_int_point2(int l, int r) {
        return {rand_int(l, r), rand_int(l, r)};
    }
    point3<int> rand_int_point3(int l, int r) {
        return {rand_int(l, r), rand_int(l, r), rand_int(l, r)};
    }

}

namespace mtd {
    template<typename tnt> struct extnt {
        tnt _v, _lv;
        tnt &v() { return _v; }
        tnt &lv() { return _lv;}
        void bp() { _lv = _v; }
        extnt(double f = 0) : _v(f), _lv(f) {}
    };

    using exint = extnt<int>;
    using exdouble = extnt<double>;
}

#include <list>

namespace mtd {
   
    
}