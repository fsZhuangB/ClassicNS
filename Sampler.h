#ifndef ClassicNS_Sampler_h
#define ClassicNS_Sampler_h

#include "Tools/RNG.hpp"

namespace ClassicNS
{

template<typename T>
class Sampler
{
    private:

        // RNG to use (local to this sampler)
        Tools::RNG rng;

        // The particles and their log-likelihoods
        std::vector<T> particles;
        std::vector<double> log_likelihoods;

    public:
        Sampler() = delete;
        Sampler(int rng_seed);

};

} // namespace

#endif

#include "SamplerImpl.h"
