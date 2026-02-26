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
    }

    void build();

    void get_input(std::vector<double> v) { // 请保证输入数据在 [0, 1) 间
        /*  持续输入电流表
            I = 20    20 ms
            I = 25    16 ms
            I = 50     7 ms 
            I = 75     5 ms
            I = 100    4 ms
            I = 150  2.5 ms
            I = 200    2 ms  
            void view() { 
                const double I = 20; 
                PN_Neuron neu;
                // neu.I += I;
                for ( ; time() < 2000; next_time()) {
                    neu.I += I;
                    neu.t_run();
                }
            }
        */
        std::list<Neuron*>::iterator it = input_ly.begin();
        for (double _v : v) { // 由于模仿视神经, 我们可以不用泊松分布
            (*it)->I += 200 * _v + 24;
            ++it;
        }
    }

    

};

void Brain::build() { // 累了, 皮层等会再实现
    for (int i = 0; i < 2; ++i) { // input
        Neuron *p = new PN_Neuron;
        neuron.push_back(p), input_ly.push_back(p);
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

