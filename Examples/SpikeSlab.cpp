#include "SpikeSlab.h"
#include "../Tools/Misc.hpp"

namespace SimpleNS
{

SpikeSlab::SpikeSlab(Tools::RNG& rng)
:params(20)
{
    for(double& param: params)
        param = rng.rand();
}

double SpikeSlab::perturb(Tools::RNG& rng)
{
    int k = rng.rand_int(params.size());
    params[k] += rng.randh();
    Tools::wrap(params[k], 0.0, 1.0);
    return 0.0;
}

} // namespace
