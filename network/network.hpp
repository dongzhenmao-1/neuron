#pragma once

#include "../my_algorithm/my_algorithm.hpp"
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace mtd {
    struct network;
    struct neuron;
    struct axon;
    struct synapse;

    struct axon {
        std::list<synapse*> syn;
        std::list<std::pair<neuron*, double>> da_target;

        neuron *nrn;

        void release();

        axon(neuron *_nrn) : nrn(_nrn) {
            
        }
    };

    struct synapse {
        int atype; // 

        exdouble w, pw; // w, potential weight
        axon *ax;
        neuron *nrn;

        void bp() { w.bp(), pw.bp(); } // 
        void run() { pw.v() *= 0.9891; } // 

        void get_pulse();
        void get_bap();

        synapse(neuron *_nrn, axon *_ax, double _w) : nrn(_nrn), ax(_ax), w(_w), pw(0) {

        }

    };

    enum class macro_type {
        positive,
        negative,
        positive_da,
        negative_da,
    };

    struct neuron {
        std::list<int> rtime;

        network *outer;

        point3<int> pos;
        int id;

        macro_type macro_t;
        int atype; // additonal type, if val < 0, this is a special neuron

        exdouble v;
        exint t;

        std::list<synapse> syn;
        axon ax;

        void get_da(double w);
        
        void release() { 
            t.v() = outer->time(), ax.release(); 
            rtime.push_back(outer->time());
            for (synapse &_syn : syn) _syn.get_bap();
        }

        void bp() {
            t.bp(), v.bp();
            for (synapse &_syn : syn) _syn.bp();
        }

        void run() {
            if (!rtime.empty() && rtime.front() < outer->time() - 50) {
                rtime.pop_front();
            }
            v.v() *= 0.91;
            for (synapse &_syn : syn) _syn.run();

            if (v.lv() > 1) { // more function will come soon
                v.v() -= 1, release();
            }
        }

        double get_val() {
            return double(rtime.size()) / 5.0;
        }

        synapse *add_synapse(axon *from_ax, double w) {
            syn.push_back(synapse(this, from_ax, w));
            return &syn.back();
        }

        void link(neuron *post, double w) {
            synapse *_syn = post->add_synapse(&this->ax, w);
            ax.syn.push_back(_syn);
        }

        bool is_link(neuron *post) {
            for (synapse *_syn : ax.syn) {
                if (_syn->nrn == post) return true;
            }
            return false;
        }

        neuron(network *_outer, point3<int> _pos, int _id, macro_type _macro_t, int _atype) : 
            outer(_outer), pos(_pos), id(_id), macro_t(_macro_t), ax(this), atype(_atype) {
            
        }

    };

    void axon::release() {
        if (nrn->macro_t == macro_type::positive || nrn->macro_t == macro_type::negative) {
            for (synapse *_syn : syn) _syn->get_pulse();
        } else {
            for (auto _nrn : da_target) {
                _nrn.first->get_da(_nrn.second);
            }
        }
    }

    void synapse::get_pulse() {
        nrn->v.v() += w.lv();
    }

    void neuron::get_da(double _da) {
        for (synapse &_syn : syn) {
            _syn.w.v() += _syn.pw.lv() * _da;
        }
    }

    void synapse::get_bap() {
        const double B = 0.1; // weakening constant
        macro_type pre = this->ax->nrn->macro_t;
        if (pre == macro_type::positive_da || pre == macro_type::negative_da) return;
        pw.v() += mtd::iexp10(nrn->t.v() - ax->nrn->t.lv()) - B;
        if (pre == macro_type::positive) {
            pw.v() = std::max(0.0, std::min(1.0, pw.v()));
        } else {
            pw.v() = std::max(-1.0, std::min(0.0, pw.v()));
        }
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
                int id;
                macro_type macro_t;
                int atype;
            } neuron;
            struct {
                point2<int> edge;
                int atype;
                double w;
            } edge;
        };
    };

    struct network {
        static const int n = 10, max_nrn = n * n * n / 3;
        static const int max_edge = n * 2; // keep the space for neuron 

        static const int input_size = 2, reward_size = 2, output_size = 1; // reward means "reward and punishment"

        double input[input_size], reward[reward_size];

        std::list<gene> gen;
        std::list<neuron> nrn;
        std::unordered_map<int, neuron*> itnrn; // id to neuron
        std::unordered_map<mtd::point3<int>, neuron*> ptnrn; // pos to neuron

        bool is_exist_neuron(point3<int> pos);

        neuron *create_neuron_phenotype(point3<int> pos, int id, macro_type type, int atype);
        void build();

        bool create_neuron_normal();
        bool create_edge_normal();
        bool delete_neuron_normal();
        bool delete_edge_normal();
        bool move_neuron_normal();

        network mutate();

        int _time = 0;
        int &time() { return _time; }
        void next_time() { ++time(); }
        void run();

        void network::set_special_input(int id, double w);
        void network::set_special_reward(int id, double w);
        double network::get_special_output(int id);

    };

    bool network::is_exist_neuron(point3<int> pos) {
        return (ptnrn.find(pos) != ptnrn.end());
    }

    neuron *network::create_neuron_phenotype(point3<int> pos, int id, macro_type type, int atype) {
        nrn.push_back(neuron(this, pos, id, type, atype));
        itnrn[id] = &nrn.back();
        ptnrn[pos] = &nrn.back();
        return &nrn.back();
    }

    void network::build() { // you can only use this network after you call this function.
        for (const gene &_gen : gen) {
            if (_gen.type == 0) {
                create_neuron_phenotype(_gen.neuron.pos, _gen.neuron.id, _gen.neuron.macro_t, _gen.neuron.atype);
            } else if (_gen.type == 1) {
                itnrn[_gen.edge.edge.x]->link(itnrn[_gen.edge.edge.y], _gen.edge.w);
            }
        }

        for (neuron &_nrn : nrn) if (_nrn.macro_t == macro_type::positive_da || _nrn.macro_t == macro_type::negative_da) {
            double da = (_nrn.macro_t == macro_type::positive_da ? 1.0 : -1.0);
            for (int dx = -2; dx <= 2; ++dx) {
                for (int dy = -2; dy <= 2; ++dy) {
                    for (int dz = -2; dz <= 2; ++dz) {
                        point3<int> pos = _nrn.pos + (point3<int>){dx, dy, dz};
                        if (is_exist_neuron(pos)) {
                            double _da = da;
                            if (dx == 0 && dy == 0 && dz == 0) { _da *= 0.8; }
                            else if (abs(dx) <= 1 && abs(dy) <= 1 && abs(dz) <= 1) { _da *= 0.6; }
                            else if (abs(dx) <= 2 && abs(dy) <= 2 && abs(dz) <= 2) { _da *= 0.4; }
                            _nrn.ax.da_target.push_back({ptnrn[pos], _da});
                        }
                    }
                }
            }
        }
    }

    bool network::create_neuron_normal() { // more function will coming soon
        point3<int> pos = rand_int_point3(0, n);
        if (is_exist_neuron(pos)) return false;
        gene ngen;
        ngen.type = 0;
        ngen.neuron = {pos, int(nrn.size()), macro_type(rand_int(0, 4)), 0};
        gen.push_back(ngen);

        return true;
    }

    bool network::create_edge_normal() {
        std::unordered_set<point2<int>> mp;
        for (const gene &_gen : gen) {
            if (_gen.type == 1) mp.insert({_gen.edge.edge.x, _gen.edge.edge.y});
        }

        point2<int> edge = rand_int_point2(0, nrn.size());
        if (mp.find(edge) != mp.end()) return false;
        if (itnrn[edge.x]->ax.syn.size() >= max_edge) return false;
        if (itnrn[edge.x]->is_link(itnrn[edge.y])) return false;

        gene ngen; 
        ngen.type = 1, ngen.edge = {edge, rand_int(0, 1), 0.0};

        if (itnrn[edge.x]->macro_t == macro_type::positive) {
            ngen.edge.w = rand_double(0.2, 0.8);
        } else if (itnrn[edge.x]->macro_t == macro_type::negative) {
            ngen.edge.w = rand_double(-0.8, 0.2);
        }

        gen.push_back(ngen);

        return true;
    }

    bool network::delete_neuron_normal() {
        int id = rand_int(0, nrn.size());
        if (itnrn[id]->atype < 0) return false;
        for (auto it = gen.begin(); it != gen.end(); ) {
            auto nx = std::next(it);
            if (it->type == 0) {
                if (it->neuron.id == id) gen.erase(it);
                else it->neuron.id -= (it->neuron.id > id);
            } else if (it->type == 1) {
                if (it->edge.edge.x == id || it->edge.edge.y == id) gen.erase(it);
                else it->edge.edge.x -= (it->edge.edge.x > id), it->edge.edge.y -= (it->edge.edge.y > id);
            }
            it = nx;
        }

        return true;
    }

    bool network::delete_edge_normal() {
        int cnt = 0;
        for (const gene &_gen : gen) cnt += (_gen.type == 1);
        if (cnt == 0) return false;
        cnt = rand_int(0, cnt);
        for (auto it = gen.begin(); it != gen.end(); ) {
            auto nx = std::next(it);
            cnt -= (it->type == 1);
            if (cnt == 0) gen.erase(it);
            it = nx;
        }    

        return true;
    }

    bool network::move_neuron_normal() {
        int id = rand_int(0, nrn.size());
        point3<int> npos = itnrn[id]->pos + rand_int_point3(-1, 2);
        if (is_exist_neuron(npos)) return false;
        if (npos.x < 0 || npos.y < 0 || npos.z < 0) return false;
        if (npos.x >= n || npos.y >= n || npos.z >= n) return false;

        for (gene &_gen : gen) if (_gen.type == 0 && _gen.neuron.id == id) {
            _gen.neuron.pos = npos; break;
        }

        return true;
    }

    network network::mutate() {
        network new_network;
        new_network.gen = this->gen;

        for (int flag = 0, change_t = rand_int(0, 5); !flag; change_t = rand_int(0, 5)) {
            if (change_t == 0) {
                flag = create_neuron_normal();
            } else if (change_t == 1) {
                flag = create_edge_normal() ;
            } else if (change_t == 2) {
                flag = delete_neuron_normal();
            } else if (change_t == 3) {
                flag = delete_edge_normal();
            } else if (change_t == 4) {
                flag = move_neuron_normal();
            }
        }

        for (gene &_gen : gen) if (_gen.type == 1 && rand_bool(0.1)) {
            _gen.edge.w *= rand_double(0.95, 1.05);
        }

        std::swap(new_network.gen, this->gen);

        return new_network;
    }

    /*
    special section id order
    input
    reward/punishment
    output
    */

    void network::set_special_input(int id, double w) {
        input[id] = w;
    }

    void network::set_special_reward(int id, double w) {
        reward[id] = w;
    }

    double network::get_special_output(int id) {
        return itnrn[input_size + reward_size + id]->get_val();
    }


    void network::run() {
        for (int i = 0; i < input_size; ++i) {
            itnrn[i]->v.v() += (input[i] * 0.05 + 0.09);
        }
        for (int i = 0; i < reward_size; ++i) {
            itnrn[i + input_size]->v.v() += (reward[i] * 0.05 + 0.09);
        }

        for (neuron &_nrn : nrn) _nrn.bp();
        for (neuron &_nrn : nrn) _nrn.run();
        
        ++time();
    }



}