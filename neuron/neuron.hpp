#pragma once

#include "../my_algorithm/my_algorithm.hpp"
#include <list>
#include <algorithm>

namespace mtd {

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
        double w, pw; // w, potential weight
        axon *ax;
        neuron *nrn;

        std::list<synapse*>::iterator iter;

        void get_pulse();
        void get_bap();
        
        void fix() {
            static const double mx_w = 1.0, mn_w = -1.0;
            w = std::max(mn_w, std::min(mx_w, w));
        }

        synapse(neuron *_nrn, double _w) : nrn(_nrn), w(_w), pw(0) {

        }

    };

    struct neuron {
        point3<int> pos;
        int type;
        exdouble v;
        exint t;

        std::list<synapse> syn;
        axon ax;
        
        void release() { 
            ax.release(); 
            for (synapse &_syn : syn) _syn.get_bap();
        }

        synapse *add_synapse(double w) {
            syn.push_back(synapse(this, w));
            return &syn.back();
        }

        void link(neuron *post, double w) {
            synapse *_syn = post->add_synapse(w);
            ax.syn.push_back(_syn);
        }

        neuron(point3<int> _pos, int _type) : pos(_pos), type(_type), ax(this) {
            
        }

    };

    void axon::release() {
        for (synapse *_syn : syn) {
            _syn->get_pulse();
        }
    }

    void synapse::get_pulse() {
        nrn->v.v() += w;
    }

    void synapse::get_bap() {
        const double B = 0.1; // weakening constant
        pw += mtd::iexp10(nrn->t.v() - ax->nrn->t.lv()) - B;
    }





}