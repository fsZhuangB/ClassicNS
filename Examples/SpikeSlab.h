#ifndef ClassicNS_Examples_SpikeSlab_h
#define ClassicNS_Examples_SpikeSlab_h

#include "../Tools/RNG.hpp"
#include <string>
#include <sstream>
#include <iostream>

namespace ClassicNS
{

class SpikeSlab
{
    private:

        // The 20 parameters
        std::vector<double> params;

    public:

        // Construct by generating from the prior.
        SpikeSlab(Tools::RNG& rng);
        SpikeSlab(const std::string& s);

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
