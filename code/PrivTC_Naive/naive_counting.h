#ifndef CDPTRIANGLECOUNTING_NAIVE_COUNTING_H
#define CDPTRIANGLECOUNTING_NAIVE_COUNTING_H

#include <vector>
#include <set>

long long compute_cycle_true_answer(std::vector<std::set<int>>& neighbors)
{
    long long cycle_tri_num = 0;

    int node_num = neighbors.size();
    int i, j, k;
    std::set<int>::iterator itera1;
    std::set<int>::iterator itera2;
    for (i = 0; i < node_num; i++)
    {
        for (itera1 = neighbors[i].begin(); itera1 != neighbors[i].end(); itera1++)
        {
            j = *itera1;
            if (j <= i)
            {
                continue;
            }
            for (itera2 = neighbors[j].begin(); itera2 != neighbors[j].end(); itera2++)
            {
                k = *itera2;
                if (k <= i)
                {
                    continue;
                }
                if (neighbors[k].count(i))
                {
                    cycle_tri_num++;
                }
            }
        }
    }
    return cycle_tri_num;
}

long long compute_flow_true_answer(std::vector<std::set<int>>& neighbors)
{
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
            for (itera2 = neighbors[i].begin(); itera2 != neighbors[i].end(); itera2++)
            {
                k = *itera2;
                if (neighbors[j].count(k))
                {
                    flow_tri_num++;
                }
            }
        }
    }
    return flow_tri_num;
}

#endif //CDPTRIANGLECOUNTING_NAIVE_COUNTING_H
