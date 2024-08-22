#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include "utils.h"
#include "../stats/include/stats.hpp"

#include <iostream>

std::pair<double, double> localized_DP(std::vector<std::set<int>>& neighbors, int d_max, double epsilon1, double epsilon2)
{
    double p, q;
    q = 1.0 / (exp(epsilon1) + 1.0);
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

    //两个三角形的个数估值
    double wc = 0;
    double wf = 0;
    //每个client对4 + 2个集合的观测值
    for (i = 0; i < node_num; i++)
    {
        //先进行投影
        std::vector<int> rndperm;
        std::set<int> del_i;
        int deg_vi = neighbors[i].size();
        make_rnd_perm(rndperm, deg_vi, deg_vi);

        std::set<int>::iterator itera;
        int x = 0;
        for (itera = neighbors[i].begin(); itera != neighbors[i].end(); itera++)
        {
            if (rndperm[x] >= d_max)
            {
                del_i.insert(*itera);
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
        //        del_i.insert(j);
        //    }
        //    x++;
        //}

        //对六个集合进行计算

        double t_i = 0;
        double t_1_i = 0;
        double t_2_i = 0;
        double l_i = 0;
        double r_i = 0;
        double s_i = 0;

        std::set<int>::iterator itera1;
        std::set<int>::iterator itera2;


        std::set<int> reverse_noisy_neighbors;

        for (k = 0; k < node_num; k++)
        {
            if (noisy_neighbors[k].count(i))
            {
                reverse_noisy_neighbors.insert(i);
            }
        }

        for (itera1 = neighbors[i].begin(); itera1 != neighbors[i].end(); itera1++)
        {
            j = *itera1;
            if (del_i.count(j))
            {
                continue;
            }

            std::set<int> t_i_set;
            std::set_intersection(noisy_neighbors[j].begin(), noisy_neighbors[j].end(), reverse_noisy_neighbors.begin(), reverse_noisy_neighbors.end(), std::inserter(t_i_set, t_i_set.begin()));
            t_i += t_i_set.size();

            if (noisy_neighbors[j].count(i))
            {
                t_1_i += (noisy_neighbors[j].size() - 1);
            }
            else
            {
                t_1_i += noisy_neighbors[j].size();
            }


            if (reverse_noisy_neighbors.count(j))
            {
                t_2_i += (reverse_noisy_neighbors.size() - 1);
            }
            else
            {
                t_2_i += (reverse_noisy_neighbors.size());
            }

            l_i += (node_num - 2);

            std::set<int> r_i_set_tmp;
            std::set<int> r_i_set;
            std::set_difference(neighbors[i].begin(), neighbors[i].end(), del_i.begin(), del_i.end(), std::inserter(r_i_set_tmp, r_i_set_tmp.begin()));
            std::set_intersection(r_i_set_tmp.begin(), r_i_set_tmp.end(), noisy_neighbors[j].begin(), noisy_neighbors[j].end(), std::inserter(r_i_set, r_i_set.begin()));
            //if (r_i_set.count(j))
            //{
            //    r_i += (r_i_set.size() - 1);
            //}
            //else
            //{
            r_i += r_i_set.size();
            //}

            std::set<int> s_i_set;
            std::set_difference(neighbors[i].begin(), neighbors[i].end(), del_i.begin(), del_i.end(), std::inserter(s_i_set, s_i_set.begin()));
            
            //if (s_i_set.count(j))
            //{
            s_i += (s_i_set.size() - 1);
            //}
            //else
            //{
            //    s_i += (s_i_set.size());
            //}
        }
        double wc_i = t_i - q * t_1_i - q * t_2_i + q * q * l_i;
        double wf_i = r_i - q * s_i;
        //add Laplace noise
        wc_i += stats::rlaplace(0.0, ((2 * (node_num - 2)) + (2 * d_max)) / epsilon2, engine);
        wf_i += stats::rlaplace(0.0, ((2 * (node_num - 2)) + (2 * d_max)) / epsilon2, engine);
        wc += wc_i;
        wf += wf_i;
    }
    return std::make_pair(wc / (3 * pow(2 * q - 1, 2)), wf / (1 - 2 * q));
}