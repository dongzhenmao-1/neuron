#pragma once

const double min_dt = 0.1; // 时间步

static double __time = 0;

double time() { return __time; }

double next_time() { return ++__time; }
