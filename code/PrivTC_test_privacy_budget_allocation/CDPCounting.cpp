#include <vector>
#include <set>
#include <algorithm>
#include "utils.h"
#include "../stats/include/stats.hpp"
#include <iostream>

std::pair<long long, long long> compute_true_answer(std::vector<std::set<int>>& neighbors, std::vector<std::set<int>>& del)
{
    long long cycle_tri_num = 0;
    long long flow_tri_num = 0;

    int node_num = neighbors.size();
    int i, j, k;
    std::set<int>::iterator itera1;
    std::set<int>::iterator itera2;
    for (i = 0; i < node_num; i++)
    {
        for (itera1 = neighbors[i].begin(); itera1 != neighbors[i].end(); itera1++)
        {
            j = *itera1;
            if (del[i].count(j) || j <= i)
            {
                continue;
            }
            for (itera2 = neighbors[j].begin(); itera2 != neighbors[j].end(); itera2++)
            {
                k = *itera2;
                if (del[j].count(k) || k <= i)
                {
                    continue;
                }
                if (neighbors[k].count(i) && (!del[k].count(i)))
                {
                    cycle_tri_num++;
                }
            }
        }
    }

    for (i = 0; i < node_num; i++)
    {
        for (itera1 = neighbors[i].begin(); itera1 != neighbors[i].end(); itera1++)
        {
            j = *itera1;
            if (del[i].count(j))
            {
                continue;
            }
            for (itera2 = neighbors[i].begin(); itera2 != neighbors[i].end(); itera2++)
            {
                k = *itera2;
                if (del[i].count(k))
                {
                    continue;
                }
                if (neighbors[j].count(k) && (!del[j].count(k)))
                {
                    flow_tri_num++;
                }
            }
        }
    }
    return std::make_pair(cycle_tri_num, flow_tri_num);
}


std::pair<double, double> centralized_DP(std::vector<std::set<int>>& neighbors, int d_max, double epsilon)
{
    //graph projection
    int node_num = neighbors.size();
    int i, j;
    std::vector<std::set<int>> del(node_num, std::set<int>());
    for (i = 0; i < node_num; i++)
    {
        std::vector<int> rndperm;
        int deg_vi = neighbors[i].size();
        make_rnd_perm(rndperm, deg_vi, deg_vi);

        std::set<int>::iterator itera;
        int x = 0;
        for (itera = neighbors[i].begin(); itera != neighbors[i].end(); itera++)
        {
            if (rndperm[x] >= d_max)
            {
                del[i].insert(*itera);
            }
            x++;
        }

        //int x = 0;

        //for (j = 0; j < node_num; j++)
        //{
        //    if (!neighbors[i].count(j))
        //    {
        //        continue;
        //    }
        //    if(rndperm[x] >= d_max)
        //    {
        //        del[i].insert(j);
        //    }
        //    x++;
        //}
    }

    std::pair<double, double> true_answer;
    true_answer = compute_true_answer(neighbors, del);

    //add Laplace Noise
    double sen_tri = node_num + 3 * d_max - 4;
    true_answer.first += stats::rlaplace(0.0, sen_tri/epsilon, engine);
    true_answer.second += stats::rlaplace(0.0, sen_tri/epsilon, engine);

    return true_answer;
}

