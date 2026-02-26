#include <stdio.h>
#include <vector> 
#include <math.h>

#include "neuron/brain.hpp"
#include "my_algorithm.hpp"

Brain brain;

int main() {
    brain.build();

    for (int i = 0; i < 2000; ++i) {
        int x = rand_bool(), y = rand_bool();
        int z = x ^ y;
        for ( ; ; next_time()) {
            brain.get_input(std::vector<double>{double(x), double(y)});
            
            brain.t_run();
        }

    }

    
    return 0;
}

/*


*/