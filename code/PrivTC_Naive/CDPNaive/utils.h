
#ifndef CDPTRIANGLECOUNTING_UTILS_H
#define CDPTRIANGLECOUNTING_UTILS_H

#include <vector>
#include "mt19937ar.h"
#include "../stats/include/stats.hpp"

// Initialization of statslib
stats::rand_engine_t engine(1776);

void make_rnd_perm(std::vector<int>& rndperm, int size, int num)
{
    int rnd;
    std::vector<int> ordperm;
    int i, j;

    for (i = 0; i < size; i++)
    {
        ordperm.push_back(i);
    }

    for (i = 0; i < num; i++)
    {
        rnd = genrand_int32() % (size - i);
        rndperm.push_back(ordperm[rnd]);
        for (j = rnd + 1; j < size - i; j++)
        {
            ordperm[j - 1] = ordperm[j];
        }
    }
}


#endif //CDPTRIANGLECOUNTING_UTILS_H
