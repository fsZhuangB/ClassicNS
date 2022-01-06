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

double SpikeSlab::log_likelihood() const
{
    static constexpr double u = 0.1;
    static constexpr double v = 0.01;
    static constexpr double tau_u = 1.0/(u*u);
    static constexpr double tau_v = 1.0/(v*v);
    static constexpr double c_u = -0.5*log(2*M_PI*u*u);
    static constexpr double c_v = -0.5*log(2*M_PI*v*v);
    static constexpr double shift = 0.031;

    double slab  = 0.0;
    double spike = 0.0;
    for(double x: params)
    {
        slab  += c_u - 0.5*tau_u*pow(x - 0.5, 2);
        spike += c_v - 0.5*tau_v*pow(x - 0.5 - shift, 2);
    }

    return Tools::logsumexp({slab, 100.0*spike});
}

} // namespace
