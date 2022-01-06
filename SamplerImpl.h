#ifndef ClassicNS_SamplerImpl_h
#define ClassicNS_SamplerImpl_h

#include <iostream>

namespace ClassicNS
{

template<typename T>
Sampler<T>::Sampler(int rng_seed)
:rng(rng_seed)
{
    std::cout << "Initialising sampler." << std::endl;
    std::cout << "Generating particles from the prior..." << std::flush;

    // TODO: Implement this

    std::cout << "done." << std::endl;
}


} // namespace

#endif
