#pragma once

#include "../my_algorithm/my_algorithm.hpp"
#include <list>

namespace mtd {

struct neuron;
struct axon;
struct synapse;

struct axon {
    std::list<synapse*> syn;
    neuron *nrn;

    void release();
};

struct synapse {
    double w, pw; // w, potential weight
    axon *ax;
    neuron *nrn;

    void get_pulse();
    void get_bap();
};

struct neuron {
    int type;
    exdouble v;
    exint t;

    std::list<synapse> syn;
    axon ax;
    
    void release() { 
        ax.release(); 
        for (synapse &_syn : syn) _syn.get_bap();
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