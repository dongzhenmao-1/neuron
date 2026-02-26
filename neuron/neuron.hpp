#pragma once

#include <stdio.h>
#include <vector> 
#include <math.h>
#include <list>
#include <random>

#include "../my_algorithm.hpp"
#include "../overall/overall.hpp"

struct Neuron;

struct Neuron {

    struct Dendrite;
    struct Axon;

    struct Dendrite {
        static double Ca_f(double x);

        double Ca_rest() { return 0.05; };

        Neuron *from;
        Axon *link;

        double w; 
        double Ca_v;
        double h; // 已激活的 NMDA 受体占比

        // Dendrite() = default;
        Dendrite(double l, double r);

        void get_release();
        void get_bap();
        void t_run();

    };

    struct Axon {
        Neuron *from;
        std::list<Dendrite*> to; // 防止地址变动
        void release();
    };    

    virtual double a() = 0;
    virtual double b() = 0;
    virtual double c() = 0; // 复极化电位
    virtual double d() = 0; // 
    virtual int type() = 0;

    std::list<Dendrite> den;
    Axon ax;

    double v; // 电位
    double u; // 疲劳度
    double I; // 输入电流

    void release();
    void t_run();

    Dendrite *build_a_den(int pre_type);

    Neuron() { 
        ax.from = this; 
    }
    
};

double Neuron::Dendrite::Ca_f(double x) { // 1 ms 为单位
    return x < 0.1 ? 0 : 0.006 * (x - 0.1) * (x - 0.8) / (x * x + 0.3);
}

Neuron::Dendrite::Dendrite(double l, double r) { 
    h = 0, Ca_v = Ca_rest();
    w = rand_double(l, r);
}

void Neuron::Dendrite::get_release() {
    from->I += 100 * w;
    h += (1 - h) * 0.5;
}

void Neuron::Dendrite::get_bap() {
    Ca_v += 4.5 * h + 0.3;
}

void Neuron::Dendrite::t_run() {              // 随时间 min_dt 的自然损失
    // Ca_v = std::max(Ca_rest(), Ca_v + 0.003 * (Ca_rest() - Ca_v) - 0.003); // 前面是树突棘颈流出, 后面是离子泵
    Ca_v = Ca_v + (0.0004 / min_dt) * (Ca_rest() - Ca_v); // 树突棘颈流出

    h *= (0.0994 / min_dt);
    w += (min_dt * Neuron::Dendrite::Ca_f(Ca_v)) * (min_dt * DA.f());

    if (link->from->type() == 1) {            // 突触前神经元是兴奋性
        w = std::max(std::min(w, 2.0), 0.0);
    } else {                                  // 突触前神经元是抑制性
        w = std::max(std::min(w, 0.0), -2.0);
    }
}

Neuron::Dendrite *Neuron::build_a_den(int pre_type) {
    if (pre_type == 1) {
        den.push_back(Neuron::Dendrite(0.2, 0.8));
    } else {
        den.push_back(Neuron::Dendrite(-0.8, 0.2));
    }
    den.back().from = this;
    return &den.back();
}

void link_random(Neuron *pre, Neuron *post) {
    Neuron::Dendrite *den = post->build_a_den(pre->type());
    pre->ax.to.push_back(den);
    den->link = &pre->ax;
}

void Neuron::Axon::release() {
    for (Dendrite *den : to) {
        den->get_release();
    }
}

void Neuron::release() {
    // printf("sp!\n");

    ax.release();
    for (Dendrite &d : den) d.get_bap();
    
    v = c();
    u = u + d();
}

void Neuron::t_run() {
    for (Dendrite &d : den) d.t_run();

    double _v = v;
    v += min_dt * (0.04 * v * v + 5 * v + 140 - u + I);
    u += min_dt * a() * (b() * _v - u);
    I *= (0.01 / min_dt);

    if (v > 30.0) release();
}

struct PN_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return 1; }
    PN_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};

struct SST_Neuron : Neuron {
    double a() override { return 0.02; }
    double b() override { return 0.2; }
    double c() override { return -70.0; }
    double d() override { return 8.0; }
    int type() override { return -1; }
    SST_Neuron() : Neuron() {
        v = c();
        u = c() * b();
        I = 0;
    }
};