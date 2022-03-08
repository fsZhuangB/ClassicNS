#include <iostream>
#include "Examples/SpikeSlab.h"
#include "Sampler.h"

using namespace ClassicNS;
using Model = SpikeSlab;

int main()
{
    double query = -93.88701485340454;
    // initial the sampler
    // model is from the spike and slab
    Sampler<Model> sampler(123);
    // sampler.run_to_depth(100.0);
    std::cout << sampler.get_val(query) << std::endl;
    return 0;
}
