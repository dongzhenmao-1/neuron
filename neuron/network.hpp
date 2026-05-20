#pragma once

#include "neuron.hpp"
#include <list>
#include <unordered_map>

namespace mtd {
    
    struct gene {
        int type; /*
            0 create neuron
            1 create edge
            * 2 delete neuron
            * 3 delete edge
            * 4 move neuron
        */
        union {
            struct {
                point3<int> pos;
                int type;
            } neuron;
            struct {
                int idx, idy, w;
            } link;
        };
    };

    struct network {
        static const int n = 10, max_num = n * n * n / 3; // keep the space for neuron 
        std::list<gene> gen;
        std::list<neuron> nrn;
        std::unordered_map<int, neuron*> itnrn; // id to neuron
        std::unordered_map<mtd::point3<int>, neuron*> ptnrn; // pos to neuron

        neuron *create_neuron(point3<int> pos, int type) {
            nrn.push_back(neuron(pos, type));
            itnrn[int(nrn.size()) + 1] = &nrn.back();
            ptnrn[pos] = &nrn.back();
            return &nrn.back();
        }

        neuron *create_neuron_normal() {
            while (nrn.size() < max_num) {
                point3<int> pos = rand_int_point3(n);
                if (ptnrn.find(pos) == ptnrn.end()) continue;
                return create_neuron(pos, rand_int(0, 4));
            }
        }
        
        void build() { // you can only use this network after you call this function.
            for (const gene &_gen : gen) {
                if (_gen.type == 0) {
                    create_neuron(_gen.neuron.pos, _gen.neuron.type);
                } else if (_gen.type == 1) {
                    itnrn[_gen.link.idx]->link(itnrn[_gen.link.idx], _gen.link.w);
                }
            }

        }

        network mutate() {
            network new_network;

            int change_type = rand_int(0, 5);
            if (change_type == 0) {
                create_neuron_normal();
            } else if (change_type == 1) {
                
            } else if (change_type == 2) {

            } else if (change_type == 3) {

            } else if (change_type == 4) {

            }



        }


    };


















}

