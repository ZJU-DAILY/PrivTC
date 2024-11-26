#include <vector>
#include <set>
#include <algorithm>
#include "utils.h"
#include "naive_counting_with_projection.h"
#include "../stats/include/stats.hpp"
#include <iostream>


std::pair<double, double> centralized_DP_Naive(std::vector<std::set<int>>& neighbors, int d_max, double epsilon)
{
    //Graph Projection
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
    
    
    //divide privacy budget
    //ratio = 0.5

    double ratio = 0.5;
    
    double epsilon_cycle = epsilon * ratio;
    double epsilon_flow = epsilon - epsilon_cycle;
    
    //compute true answer
    std::pair<double, double> true_answer;
    true_answer = compute_true_answer(neighbors, del);

    //Cycle Triangle
    double sen_cycle_tri = d_max;
    true_answer.first += stats::rlaplace(0.0, sen_cycle_tri/epsilon_cycle, engine);

    //Flow Triangle
    double sen_flow_tri = node_num + 2 * d_max - 4;
    true_answer.second += stats::rlaplace(0.0, sen_flow_tri/epsilon_flow, engine);

    return true_answer;
}

