#pragma once

#include "neuron.hpp"
#include "overall/overall.hpp"

struct Brain {
    std::list<Neuron*> neuron; // 纯虚类不能实例化
    std::list<Neuron*> input_ly;
    std::list<Neuron*> hide_ly;
    std::list<Neuron*> output_ly;

    void t_run() {
        for (Neuron *n : neuron) n->t_run();
        DA.t_run();
        next_time();
    }

    void build();

} brain;

void Brain::build() { // 累了, 皮层等会再实现
    for (int i = 0; i < 2; ++i) { // input
        Neuron *p = new PN_Neuron;
        neuron.push_back(p);
        output_ly.push_back(p);
    }

    for (int i = 0; i < 40; ++i) { // hide
        Neuron *p = new PN_Neuron;
        neuron.push_back(p);
        hide_ly.push_back(p);
    }
    for (int i = 0; i < 10; ++i) { // hide
        Neuron *p = new SST_Neuron;
        neuron.push_back(p);
        hide_ly.push_back(p);
    }

    for (int i = 0; i < 1; ++i) { // output
        Neuron *p = new PN_Neuron;
        neuron.push_back(p);
        output_ly.push_back(p);
    }

    for (Neuron *pre : input_ly) {
        for (Neuron *post : hide_ly) {
            link_random(pre, post);
        }
    }


}