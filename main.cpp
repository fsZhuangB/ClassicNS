#include <ctime>
#include <iostream>
#include <ctime>
#include <vector>
#include "Examples/SpikeSlab.h"
#include "Sampler.h"

using namespace ClassicNS;
using Model = SpikeSlab;

int main()
{
    const int iter = 10;
    std::vector<double> all_lnZ;

    // run iter times
    for (int i = 0; i < iter; ++i)
    {
        Sampler<Model> sampler(time(0));
        std::cout << "iterations:" << i + 1 << std::endl;
        sleep(2);
        all_lnZ.push_back(sampler.run_to_depth(100.0));
    }
    Sampler<Model> sampler(time(0));
    std::cout << "The mse of this model is:" << sampler.cal_mse(all_lnZ) << std::endl;
    for (auto& z : all_lnZ)
    {
        std::cout << z << std::endl;
    }

    return 0;
}
