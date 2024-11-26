#ifndef CDPTRIANGLECOUNTING_NAIVE_COUNTING_H
#define CDPTRIANGLECOUNTING_NAIVE_COUNTING_H

#include <vector>
#include <set>

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

#endif //CDPTRIANGLECOUNTING_NAIVE_COUNTING_H
