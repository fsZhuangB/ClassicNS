#ifndef ClassicNS_SamplerImpl_h
#define ClassicNS_SamplerImpl_h

#include <iostream>
#include "Constants.h"
#include "Tools/Misc.hpp"
#include <curl/curl.h>

namespace ClassicNS
{

    static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

    template <typename T>
    Sampler<T>::Sampler(int rng_seed)
        : iteration(0), rng(rng_seed), threshold_logl(-1E300), threshold_tiebreaker(0.0)
    {
        std::cout << "Initialising sampler." << std::endl;

        auto &db = database.get_db();
        db << "INSERT INTO sampler_info VALUES (?);" << rng_seed;

        std::cout << "Generating " << num_particles;
        std::cout << " particles from the prior..." << std::flush;

        // TODO: Implement this
        for (int i = 0; i < num_particles; ++i)
        {
            T t(rng);
            double logl = t.log_likelihood();
            particles.emplace_back(std::move(t));
            log_likelihoods.push_back(logl);
            tiebreakers.emplace_back(rng.rand());
        }

        std::cout << "done.\n"
                  << std::endl;
    }

    template <typename T>
    int Sampler<T>::find_worst() const
    {
        // Use a simple scan.
        int worst = 0;

        for (int i = 1; i < num_particles; ++i)
            if (log_likelihoods[i] < log_likelihoods[worst] ||
                (log_likelihoods[i] == log_likelihoods[worst] &&
                 tiebreakers[i] < tiebreakers[worst]))
                worst = i;

        return worst;
    }

    template <typename T>
    std::string Sampler<T>::get_val(double query)
    {
        CURL *curl;
        CURLcode res;
        std::string params;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &params);
            std::string q = std::to_string(query);
            // std::cout << q << std::endl;
            std::string all_query = "query=" + q + "&submit=Submit";
            // std::cout << all_query << std::endl;
            
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, all_query.c_str());
            //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "query=-93.88701485340454&submit=Submit");
            res = curl_easy_perform(curl);

            /* Check for errors */
            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return params;
    }
    
    template <typename T>
    void Sampler<T>::do_iteration()
    {
        ++iteration;

        std::cout << "Iteration " << iteration << ".\n";

        // Save the worst particle
        int worst = find_worst();
        auto &db = database.get_db();
        db << "INSERT INTO particles VALUES (?, ?, ?, ?);"
           << iteration << particles[worst].to_string()
           << log_likelihoods[worst] << tiebreakers[worst];

        // Update the threshold
        threshold_logl = log_likelihoods[worst];
        threshold_tiebreaker = tiebreakers[worst];

        std::cout << "(log_likelihood, tiebreaker) = (";
        std::cout << log_likelihoods[worst] << ", " << tiebreakers[worst] << ").";
        std::cout << std::endl;

        // Generate a new particle above the threshold
        // Later this will be done peer to peer
        std::cout << "Generating new particle..." << std::endl;
        if (num_particles > 1)
        {
            int clone;
            while (true)
            {
                clone = rng.rand_int(num_particles);
                if (clone != worst)
                    break;
            }
            particles[worst] = particles[clone];
            log_likelihoods[worst] = log_likelihoods[clone];
            tiebreakers[worst] = tiebreakers[clone];
        }

        // Do MCMC to refresh the particle
        int accepted = refresh_particle(worst);
        std::cout << "done. Acceptance rate = ";
        std::cout << accepted << '/' << mcmc_steps << ".\n"
                  << std::endl;
    }

    template <typename T>
    int Sampler<T>::refresh_particle(int k)
    {
        int accepted = 0;

        // This is the Metropolis algorithm to sample the prior above the threshold.
        for (int i = 0; i < num_particles; ++i)
        {
            T proposal = particles[k];
            double logh = proposal.perturb(rng);
            if (rng.rand() <= exp(logh))
            {
                double proposal_logl = proposal.log_likelihood();
                double proposal_tb = tiebreakers[k];
                proposal_tb += rng.randh();
                Tools::wrap(proposal_tb);
                if (proposal_logl > threshold_logl ||
                    (proposal_logl == threshold_logl &&
                     proposal_tb > threshold_tiebreaker))
                {
                    particles[k] = proposal;
                    log_likelihoods[k] = proposal_logl;
                    tiebreakers[k] = proposal_tb;
                    ++accepted;
                }
            }
        }

        return accepted;
    }

    template <typename T>
    void Sampler<T>::run_to_depth(double nats)
    {
        int iterations = nats * num_particles;
        for (int i = 0; i < iterations; ++i)
            do_iteration();
    }

} // namespace

#endif
