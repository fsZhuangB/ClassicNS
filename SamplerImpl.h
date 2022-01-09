#ifndef ClassicNS_SamplerImpl_h
#define ClassicNS_SamplerImpl_h

#include <iostream>
#include "Constants.h"

namespace ClassicNS
{

template<typename T>
Sampler<T>::Sampler(int rng_seed)
:rng(rng_seed)
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


} // namespace

#endif
