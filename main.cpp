#include <iostream>
#include "Examples/SpikeSlab.h"
#include "Sampler.h"

using namespace ClassicNS;
using Model = SpikeSlab;

int main()
{
    Sampler<Model> sampler(123);
    return 0;
}
