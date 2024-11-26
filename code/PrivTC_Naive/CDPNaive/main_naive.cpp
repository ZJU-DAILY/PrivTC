#include <vector>
#include <set>
#include "CDPNaive.cpp"
#include "read_graph.cpp"
#include <cmath>
#include <chrono>


using namespace std;


int main()
{
    std::vector<std::set<int>> neighbors;
    read_graph(neighbors);
    int d_max = -1;
    int node_num = neighbors.size();
    std::cout << "read_end" << std::endl;
    std::cout << node_num << std::endl;
    int i;
    for (i = 0; i < node_num; i++)
    {
        int cnt_deg = neighbors[i].size();
        if(cnt_deg > d_max)
        {
            d_max = cnt_deg;
        }
    }

    std::vector<std::set<int>> del(node_num, std::set<int>());
    std::pair<long long, long long> true_answer = compute_true_answer(neighbors, del);

    std::cout << "true_answer:" << std::endl;
    std::cout << true_answer.first << " " << true_answer.second << std::endl;

    
    for (double epsilon = 2.0; epsilon >= 1.99; epsilon -= 1.0)
    {
        double CDP_avg_time = 0.0;
        double c_var = 0.0, f_var = 0.0;
        double c_relative_error = 0.0, f_relative_error = 0.0;
        for (int j = 0; j < 10; j++)
        {
            auto start = std::chrono::steady_clock::now();
            std::pair<double, double> CDP_answer = centralized_DP_Naive(neighbors, d_max, epsilon);
            auto end = std::chrono::steady_clock::now();
            CDP_avg_time += (std::chrono::duration<double>(end - start)).count();
            c_var += pow((CDP_answer.first - true_answer.first), 2);
            f_var += pow((CDP_answer.second - true_answer.second), 2);
            c_relative_error += abs(CDP_answer.first - true_answer.first) / (double)true_answer.first;
            f_relative_error += abs(CDP_answer.second - true_answer.second) / (double)true_answer.second;
        }
        CDP_avg_time /= 10;
        c_var /= 10;
        f_var /= 10;
        c_relative_error /= 10;
        f_relative_error /= 10;

        std::cout << "time:" << "epsilon:" << epsilon << " " << "CDP_avg_time:" << CDP_avg_time << std::endl;
        std::cout << "var:" << c_var << " " << f_var << std::endl;
        std::cout << "relative error:" << c_relative_error << " " << f_relative_error << std::endl;
    }

    return 0;
}
