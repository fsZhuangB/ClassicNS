#ifndef ClassicNS_Sampler_h
#define ClassicNS_Sampler_h

#include "SqliteDB.h"
#include "Tools/RNG.hpp"

namespace ClassicNS
{

template<typename T>
class Sampler
{
    private:

        // Output database connection
        SqliteDB database;

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

        // Find and return the index of the worst particle
        int find_worst() const;

        // Do one iteration
        void do_iteration();

        // Refresh a particle with MCMC
        int refresh_particle(int k);
        double send_requests(double query);

    public:
        Sampler() = delete;
        Sampler(int rng_seed);
        double run_to_depth(double nats);
        // calculate mse
        double cal_mse(std::vector<double>& all_lnZ);
        void run_to_depth(double nats);
        std::string get_val(double query);

};

} // namespace

#endif

#include "SamplerImpl.h"
