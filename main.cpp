#include <ctime>
#include <iostream>
#include <ctime>
#include "Examples/SpikeSlab.h"
#include "Sampler.h"

using namespace ClassicNS;
using Model = SpikeSlab;

int main()
{
    Sampler<Model> sampler(time(0));
    sampler.run_to_depth(100.0);
    return 0;
}
