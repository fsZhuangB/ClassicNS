#include <iostream>
#include "Examples/SpikeSlab.h"
#include "Sampler.h"

using namespace ClassicNS;
using Model = SpikeSlab;

int main()
{
    // initial the sampler
    // model is from the spike and slab
    Sampler<Model> sampler(123);
    sampler.run_to_depth(100.0);
    return 0;
}
