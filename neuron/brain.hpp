#pragma once

#include "neuron.hpp"
#include "overall/overall.hpp"
#include "../my_algorithm.hpp"

struct Brain {
    std::list<Neuron*> neuron; // 纯虚类不能实例化
    std::list<Neuron*> input_ly;
    std::list<Neuron*> hide_ly;
    std::list<Neuron*> output_ly;

    void give_DA(double k) {
        DA.float_v(k);
    }

    void t_run() {
        for (Neuron *n : neuron) n->t_run();
        DA.t_run();
        next_time();
    }

    void build();

};

void Brain::build() { // 累了, 皮层等会再实现
    for (int i = 0; i < 2; ++i) { // input
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), output_ly.push_back(p);
    }

    for (int i = 0; i < 40; ++i) { // hide
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), hide_ly.push_back(p);
    }
    for (int i = 0; i < 10; ++i) { // hide
        Neuron *p = new SST_Neuron;
        neuron.push_back(p), hide_ly.push_back(p);
    }

    for (int i = 0; i < 1; ++i) { // output
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), output_ly.push_back(p);
    }

    for (Neuron *pre : input_ly) {
        for (Neuron *post : hide_ly) {
            if (!rand_bool(0.3) || pre == post) continue;
            link_random(pre, post);
        }
    }

    for (Neuron *pre : hide_ly) {
        for (Neuron *post : hide_ly) {
            if (!rand_bool(0.1) || pre == post) continue;
            link_random(pre, post);
        }
    }

    for (Neuron *pre : hide_ly) {
        for (Neuron *post : output_ly) {
            if (!rand_bool(0.3) || pre == post) continue;
            link_random(pre, post);
        }
    }

}

