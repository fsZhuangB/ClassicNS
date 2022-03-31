#include "SpikeSlab.h"
#include "../Tools/Misc.hpp"
#include <iomanip>

namespace ClassicNS
{

SpikeSlab::SpikeSlab(Tools::RNG& rng)
:params(20)
{
    for(double& param: params)
        param = rng.rand();
}

SpikeSlab::SpikeSlab(const std::string& s)
{
    std::stringstream ss(s);
    std::string temp;
    while (ss >> temp)
    {
        params.emplace_back(std::stod(temp));
    }
    // for test
    for (double& param:params)
    {
        std::cout << param << " ";
    }
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
    static constexpr double log_100 = log(100.0);

    double slab  = 0.0;
    double spike = 0.0;
    for(double x: params)
    {
        slab  += c_u - 0.5*tau_u*pow(x - 0.5, 2);
        spike += c_v - 0.5*tau_v*pow(x - 0.5 - shift, 2);
    }

    return Tools::logsumexp({slab, log_100 + spike});
}

std::string SpikeSlab::to_string() const
{
    std::stringstream ss;
    ss << std::setprecision(16);
    for(size_t i=0; i<params.size(); ++i)
    {
        ss << params[i];
        if(i != params.size() - 1)
            ss << ',';
    }
    return ss.str();
}

} // namespace
