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

    auto& db = database.get_db();
    db << "BEGIN;";
    db << "INSERT INTO sampler_info VALUES (?);" << rng_seed;
    db << "COMMIT;";

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


template<typename T>
void Sampler<T>::do_iteration()
{
    ++iteration;

    // Save the worst particle
    int worst = find_worst();
    auto& db = database.get_db();
    db << "BEGIN;";
    db << "INSERT INTO particles VALUES (?, ?, ?, ?);"
       << iteration << particles[worst].to_string()
       << log_likelihoods[worst] << tiebreakers[worst];
    db << "COMMIT;";

    // Update the threshold
    threshold_logl = log_likelihoods[worst];
    threshold_tiebreaker = tiebreakers[worst];

    // Generate a new particle above the threshold
    // Later this will be done peer to peer
    if(num_particles > 1)
    {
        int clone;
        while(true)
        {
            clone = rng.rand_int(num_particles);
            if(clone != worst)
                break;
        }
        particles[worst]   = particles[clone];
        log_likelihoods[worst] = log_likelihoods[clone];
        tiebreakers[worst] = tiebreakers[clone];
    }

    // Do MCMC to refresh the particle
    refresh_particle(worst);
}


template<typename T>
void Sampler<T>::refresh_particle(int k)
{
}

} // namespace

#endif
