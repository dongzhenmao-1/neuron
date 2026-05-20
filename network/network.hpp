#pragma once

#include "../my_algorithm/my_algorithm.hpp"
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

namespace mtd {
    struct network;
    struct neuron;
    struct axon;
    struct synapse;

    struct axon {
        std::list<synapse*> syn;
        neuron *nrn;

        void release();

        axon(neuron *_nrn) : nrn(_nrn) {
            
        }
    };

    struct synapse {
        exdouble w, pw; // w, potential weight
        axon *ax;
        neuron *nrn;

        std::list<synapse*>::iterator iter;

        void get_pulse();
        void get_da_pulse(double w);
        void get_bap();
        
        void fix() {
            static const double mx_w = 1.0, mn_w = -1.0;
            w.v() = std::max(mn_w, std::min(mx_w, w.v()));
        }

        synapse(neuron *_nrn, double _w) : nrn(_nrn), w(_w), pw(0) {

        }

    };

    enum class macro_type {
        // input, 
        // reward,
        // output,
        positive,
        negative,
        positive_da,
        negative_da
    };

    struct neuron {
        network *outer;

        point3<int> pos;

        macro_type macro_t;

        exdouble v;
        exint t;

        std::list<synapse> syn;
        axon ax;

        void get_da(double w);
        
        void release() { 
            ax.release(); 
            for (synapse &_syn : syn) _syn.get_bap();
        }

        synapse *add_synapse(double w) {
            syn.push_back(synapse(this, w));
            return &syn.back();
        }

        void link(neuron *post, double w = 0) {
            if (w == 0) {
                if (this->macro_t == macro_type::positive) {
                    w = rand_double(0.2, 0.8);
                } else if (this->macro_t == macro_type::positive) {
                    w = rand_double(-0.8, -0.2);
                }
            }
            synapse *_syn = post->add_synapse(w);
            ax.syn.push_back(_syn);
        }

        neuron(network *_outer, point3<int> _pos, macro_type _macro_t) : 
            outer(_outer), pos(_pos), macro_t(_macro_t), ax(this) {
            
        }

    };

    void axon::release() {
        if (nrn->macro_t == macro_type::positive || nrn->macro_t == macro_type::negative) {
            for (synapse *_syn : syn) _syn->get_pulse();
        } else {
            for (synapse *_syn : syn) 
                _syn->get_da_pulse(nrn->macro_t == macro_type::positive ? 1 : -1);
        }
    }

    void synapse::get_pulse() {
        nrn->v.v() += w.lv();
    }

    void neuron::get_da(double w) {
        for (synapse &_syn : syn) {
            _syn.w.v() += _syn.pw.lv() * w;
        }
    }

    void synapse::get_bap() {
        const double B = 0.1; // weakening constant
        pw.v() += mtd::iexp10(nrn->t.v() - ax->nrn->t.lv()) - B;
    }

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
                macro_type type;
            } neuron;
            struct {
                int idx, idy, w;
            } link;
        };
    };

    struct network {
        static const int n = 10, max_nrn = n * n * n / 3;
        static const int max_edge = n * 2; // keep the space for neuron 

        std::list<gene> gen;
        std::list<neuron> nrn;
        std::unordered_map<int, neuron*> itnrn; // id to neuron
        std::unordered_map<mtd::point3<int>, neuron*> ptnrn; // pos to neuron

        void build();
        neuron *create_neuron(point3<int> pos, macro_type type);
        neuron *create_neuron_normal();
        void create_edge_normal();
        void delete_neuron_normal();
        void delete_edge_normal();
        void move_neuron_normal();
        
        network mutate();
    };

    void synapse::get_da_pulse(double w) {
        for (int dx = -2; dx <= 2; ++dx) {
            for (int dy = -2; dy <= 2; ++dy) {
                for (int dz = -2; dz <= 2; ++dz) {
                    point3<int> pos = nrn->pos + (point3<int>){dx, dy, dz};
                    if (nrn->outer->ptnrn.find(pos) != nrn->outer->ptnrn.end()) {
                        if (dx == 0 && dy == 0 && dz == 0) { w *= 0.8; }
                        else if (abs(dx) <= 1 && abs(dy) <= 1 && abs(dz) <= 1) { w *= 0.6; }
                        else if (abs(dx) <= 2 && abs(dy) <= 2 && abs(dz) <= 2) { w *= 0.4; }
                        (nrn->outer->ptnrn[pos])->get_da(w);
                    }
                }
            }
        }
    }

    void network::build() { // you can only use this network after you call this function.
        for (const gene &_gen : gen) {
            if (_gen.type == 0) {
                create_neuron(_gen.neuron.pos, _gen.neuron.type);
            } else if (_gen.type == 1) {
                itnrn[_gen.link.idx]->link(itnrn[_gen.link.idx], _gen.link.w);
            }
        }
    }

    neuron *network::create_neuron(point3<int> pos, macro_type type) {
        nrn.push_back(neuron(this, pos, type));
        itnrn[int(nrn.size()) + 1] = &nrn.back();
        ptnrn[pos] = &nrn.back();
        return &nrn.back();
    }

    neuron *network::create_neuron_normal() {
        point3<int> pos = rand_int_point3(n);
        if (ptnrn.find(pos) == ptnrn.end()) return nullptr;
        return create_neuron(pos, macro_type(rand_int(0, 4)));
    }

    void network::create_edge_normal() {
        std::unordered_set<point2<int>> mp;
        for (const gene &_gen : gen) {
            if (_gen.type == 1) mp.insert({_gen.link.idx, _gen.link.idy});
        }

        point2<int> edge = rand_int_point2(nrn.size());
        if (mp.find(edge) != mp.end()) return;
        if (itnrn[edge.x]->syn.size() >= max_edge) return;
        itnrn[edge.x]->link(itnrn[edge.y]);
    }

    void network::delete_neuron_normal() {
        int id = rand_int(0, nrn.size());
        // for (int i = 0; i < )

    }

    void network::move_neuron_normal() {

    }

    network network::mutate() {
        network new_network;

        while (true) {
            int change_type = rand_int(0, 5);
            if (change_type == 0) {
                create_neuron_normal();
                break;
            } else if (change_type == 1) {
                create_edge_normal();
                break;
            } else if (change_type == 2) {
                delete_neuron_normal();
                break;
            } else if (change_type == 3) {
                delete_edge_normal();
            } else if (change_type == 4) {
                move_neuron_normal();
            }
        }


    }



}