#ifndef Examples_SpikeSlab_h
#define Examples_SpikeSlab_h

#include "../Tools/RNG.hpp"

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
        double perturb(Tools::RNG& rng);

};

} // namespace

#endif
