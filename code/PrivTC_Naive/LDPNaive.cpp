#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include "utils.h"
#include "naive_counting.h"
#include "../stats/include/stats.hpp"

#include <iostream>


std::pair<double, double> localized_DP_Naive(std::vector<std::set<int>>& neighbors, double epsilon)
{
    double p, q;
    q = 1.0 / (exp(epsilon) + 1.0);
    p = 1.0 - q;

    int node_num = neighbors.size();
    //初始化噪声图
    std::vector<std::set<int>> noisy_neighbors(node_num, std::set<int>());
    int i, j, k;

    for (i = 0; i < node_num; i++)
    {
        for (j = 0; j < node_num; j++)
        {
            if (j == i)
            {
                continue;
            }
            if (genrand_real2() < q)
            {
                if (neighbors[i].count(j) ^ 1)
                {
                    noisy_neighbors[i].emplace(j);
                }
            }
            else
            {
                if ((neighbors[i].count(j)))
                {
                    noisy_neighbors[i].emplace(j);
                }
            }
        }
    }

    long long release_cycle_answer = compute_cycle_true_answer(noisy_neighbors);
    long long release_flow_answer = compute_flow_true_answer(noisy_neighbors);

    return std::make_pair(release_cycle_answer, release_flow_answer);

}