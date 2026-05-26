#pragma once

#include "network.hpp"

namespace mtd {
    struct Test {
        std::list<gene> orig_gene = {
            gene::create_neuron({0, 2, 2}, 0, neuron::macro_type::positive, -1),
            gene::create_neuron({0, 7, 2}, 1, neuron::macro_type::positive, -1),
            gene::create_neuron({0, 2, 7}, 2, neuron::macro_type::positive, -1),
            gene::create_neuron({0, 7, 7}, 3, neuron::macro_type::positive, -1),
            gene::create_neuron({9, 5, 5}, 4, neuron::macro_type::positive, -1),
        };
        
        network net[25];

        void init() {
            for (int i = 0; i < 5; ++i) {
                net[i].gen = orig_gene;
            }
        }

        void mutate() {
            std::sort(net, net + 25, [](const network &a, const network &b) {
                return a.score > b.score;
            });

            network new_net[25];

            for (int i = 0; i < 5; ++i) {
                for (int e = 0; e < 5; ++e) {
                    new_net[i * 5 + e] = net[i].mutate();
                }
            }

            std::swap(net, new_net);

            for (network &_net : net) {
                _net.build();
                _net.score = 0;
                _net.cnt = 0;
                _net.ok_time = 300;
            }
        }
    
        int i0, i1, o0;

        void create_example() {
            i0 = rand_bool(), i1 = rand_bool();
            o0 = i0 ^ i1;
        }

        void run0() {
            for (int i = 0; i < 300; ++i) {
                mutate();
                run1();
            }
        }

        void run1() {
            for (int step = 0; step < 300; ++step) {
                run2(step >= 100);
                if (step > 200) {
                    for (network &_net : net) {
                        if (_net.cnt / (step - 99) > 0.8) {
                            _net.ok_time = std::min(step, _net.ok_time);
                        }
                    }
                }
            }

            for (network &_net : net) {
                _net.score = 0.5 * _net.cnt / 200 + 0.5 * (1 - (_net.ok_time - 200) / 100.0);
            }
        }

        void run2(double is_in) {
            create_example();
            for (int step = 0; step < 150; ++step) {
                for (network &_net : net) {
                    _net.set_special_input(0, i0);
                    _net.set_special_input(1, i1);
                    if (step > 100) {
                        int _o0 = _net.get_special_output(0);
                        if (abs(_o0 - o0) < 0.5) {
                            _net.set_special_input(2, 1);
                            _net.set_special_input(3, 0);
                            _net.cnt += is_in * 1.0 / 50;
                        } else {
                            _net.set_special_input(2, 0);
                            _net.set_special_input(3, 1);
                        }
                    }
                }
            }
        }




    };















}

