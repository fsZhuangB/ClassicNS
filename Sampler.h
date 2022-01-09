#ifndef ClassicNS_Sampler_h
#define ClassicNS_Sampler_h

#include "Tools/RNG.hpp"

namespace ClassicNS
{

template<typename T>
class Sampler
{
    private:

        // Iteration counter
        int iteration;

        // RNG to use (local to this sampler)
        Tools::RNG rng;

        // The particles and their log-likelihoods
        std::vector<T> particles;
        std::vector<double> log_likelihoods;
        std::vector<double> tiebreakers;

        // The likelihood threshold
        double threshold_logl;
        double threshold_tiebreaker;

    public:
        Sampler() = delete;
        Sampler(int rng_seed);

};

} // namespace

#endif

#include "SamplerImpl.h"
