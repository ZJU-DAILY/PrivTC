#include <vector>
#include <set>
#include <algorithm>
#include "utils.h"
#include "naive_counting.h"
#include "../stats/include/stats.hpp"
#include <iostream>


std::pair<double, double> centralized_DP_Naive(std::vector<std::set<int>>& neighbors, double epsilon)
{
    int node_num = neighbors.size();

    //divide privacy budget
    //ratio = 0.5
    
    double epsilon_cycle = epsilon * 0.5;
    double epsilon_flow = epsilon - epsilon_cycle;

    //Cycle Triangle
    double cycle_true_answer = compute_cycle_true_answer(neighbors);
    double sen_cycle_tri = node_num - 2;
    cycle_true_answer += stats::rlaplace(0.0, sen_cycle_tri/epsilon_cycle, engine);

    //Flow Triangle
    double flow_true_answer = compute_flow_true_answer(neighbors);
    double sen_flow_tri = 3 * (node_num - 2);
    flow_true_answer += stats::rlaplace(0.0, sen_flow_tri/epsilon_flow, engine);

    
    return std::make_pair(cycle_true_answer, flow_true_answer);
}

