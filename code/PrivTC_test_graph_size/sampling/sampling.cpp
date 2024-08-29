#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include "utils.h"


//注意是邻接向量, 有0 也有1
void read_graph(std::vector<std::set<int>>& neighbors)
{
    std::ifstream f;
    std::string line;
    f.open("./Bitcoinotc_.txt", std::ios::in);
    int count = 0;
    while (std::getline(f, line))
    {
        if (count % 10 == 0)
        {
            std::cout << count << std::endl;
        }
        std::set<int> neighbor;
        std::stringstream ss(line);
        int t;
        int i = 0;
        while (ss >> t)
        {
            if (t == 1)
            {
                neighbor.emplace(i);
            }
            i++;
        }
        neighbors.emplace_back(neighbor);
        count += 1;
    }
    int node_num = neighbors.size();
    std::cout << "node_num:" << node_num << std::endl;
    int edge_num = 0;
    for (int i = 0; i < node_num; i++)
    {
        edge_num += (neighbors[i].size());
    }
    std::cout << "edge_num:" << edge_num << std::endl;
}


void sample(std::vector<std::set<int>>& neighbors, std::vector<std::set<int>>& sample_neighbors, double sample_rate)
{
    int node_num = neighbors.size();
    int sample_num = (int)(node_num * sample_rate);
    std::vector<int> vertex_map;
    std::map<int, int> reverse_vertex_map;
    std::vector<int> rndperm;
    make_rnd_perm(rndperm, node_num, node_num);
    int i;
    int j = 0;
    for (i = 0; i < node_num; i++)
    {
        if (rndperm[i] < sample_num)
        {
            vertex_map.emplace_back(i);
            reverse_vertex_map[i] = vertex_map.size() - 1;
            sample_neighbors.emplace_back();
        }
    }
    std::cout << vertex_map.size() << std::endl;
    std::cout << sample_neighbors.size() << std::endl;
    for (i = 0; i < sample_num; i++)
    {
        int raw_ver_num = vertex_map[i];
        
        std::set<int>::iterator itera;

        for (itera = neighbors[raw_ver_num].begin(); itera != neighbors[raw_ver_num].end(); itera++)
        {
            sample_neighbors[i].insert(reverse_vertex_map[*itera]);
        }
    }
}


void output_graph(std::vector<std::set<int>>& sample_neighbors, double sample_rate)
{
    std::vector<std::vector<int>> out_neighbors;
    int sample_node_num = sample_neighbors.size();
    int i;
    std::set<int>::iterator iter;
    for (i = 0; i < sample_node_num; i++)
    {
        std::vector<int> cnt_neighbor(sample_node_num, 0);
        for (iter = sample_neighbors[i].begin(); iter != sample_neighbors[i].end(); iter++)
        {
            cnt_neighbor[*iter] = 1;
        }
        out_neighbors.emplace_back(cnt_neighbor);
    }
    std::cout << sample_node_num << std::endl;
    std::ofstream d_f;
    d_f.open("./Bitcoinotc_" + std::to_string((int)(sample_rate * 100)) + ".txt");
    int j;
    for (i = 0; i < sample_node_num; i++)
    {
        for (j = 0; j < sample_node_num; j++)
        {
            d_f << out_neighbors[i][j] << " ";
        }
        d_f << std::endl;
    }

    d_f.close();
}


int main()
{
    std::vector<std::set<int>> neighbors;
    read_graph(neighbors);
    for (double sample_rate = 0.2; sample_rate < 1.0; sample_rate += 0.2)
    {
        std::vector<std::set<int>> sample_neighbors;
        sample(neighbors, sample_neighbors, sample_rate);
        output_graph(sample_neighbors, sample_rate);
    }
    
    return 0;
}