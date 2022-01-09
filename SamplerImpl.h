#ifndef ClassicNS_SamplerImpl_h
#define ClassicNS_SamplerImpl_h

#include <iostream>
#include "Constants.h"

namespace ClassicNS
{

template<typename T>
Sampler<T>::Sampler(int rng_seed)
:iteration(0)
,rng(rng_seed)
,threshold_logl(-1E300)
,threshold_tiebreaker(0.0)
{
    std::cout << "Initialising sampler." << std::endl;
    std::cout << "Generating particles from the prior..." << std::flush;

    // TODO: Implement this
    for(int i=0; i<num_particles; ++i)
    {
        T t(rng);
        double logl = t.log_likelihood();
        particles.emplace_back(std::move(t));
        log_likelihoods.push_back(logl);
        tiebreakers.emplace_back(rng.rand());
    }

    std::cout << "done." << std::endl;
}


template<typename T>
int Sampler<T>::find_worst() const
{
    // Use a simple scan.
    int worst = 0;

    for(int i=1; i<num_particles; ++i)
        if(log_likelihoods[i] < log_likelihoods[worst] ||
            (log_likelihoods[i] == log_likelihoods[worst] &&
             tiebreakers[i] < tiebreakers[worst]))
            worst = i;

    return worst;
}

} // namespace

#endif
