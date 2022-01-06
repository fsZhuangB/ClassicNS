#ifndef Examples_SpikeSlab_h
#define Examples_SpikeSlab_h

#include "../Tools/RNG.hpp"
#include <string>

namespace SimpleNS
{

class SpikeSlab
{
    private:

        // The 20 parameters
        std::vector<double> params;

    public:

        // Construct by generating from the prior.
        SpikeSlab(Tools::RNG& rng);

        // Perturb a parameter, so as to explore the prior.
        // The returned value is a log-hastings factor for non-uniform priors.
        double perturb(Tools::RNG& rng);

        // Log likelihood
        double log_likelihood() const;

        // Print to string for output
        std::string to_string() const;
};

} // namespace

#endif
