#pragma once

#include <random>

static std::mt19937 gen(713);

int rand_int(int l, int r) { // [l, r)
    return std::uniform_int_distribution<int>(l, r - 1)(gen);
}

double rand_double(double l, double r) {
    return std::uniform_real_distribution<double>(l, r)(gen);
}