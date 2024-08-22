#include <vector>
#include <set>
#include "LDPNaive.cpp"
#include "CDPNaive.cpp"
#include "read_graph.cpp"
#include <cmath>
#include <chrono>


using namespace std;


int main()
{
    std::vector<std::set<int>> neighbors;
    read_graph(neighbors);
    //int d_max = -1;
    int node_num = neighbors.size();
    std::cout << "read_end" << std::endl;
    std::cout << node_num << std::endl;
    
    /*
    int i;
    for (i = 0; i < node_num; i++)
    {
        int cnt_deg = neighbors[i].size();
        if(cnt_deg > d_max)
        {
            d_max = cnt_deg;
        }
    }
    */

    long long true_cycle_answer = compute_cycle_true_answer(neighbors);
    long long true_flow_answer = compute_flow_true_answer(neighbors);
    std::cout << "true_answer:" << std::endl;
    std::cout << true_cycle_answer << " " << true_flow_answer << std::endl;

    
    for (double epsilon = 2.0; epsilon >= 1.99; epsilon -= 1.0)
    {
        double CDP_avg_time = 0.0;
        double c_var = 0.0, f_var = 0.0;
        double c_relative_error = 0.0, f_relative_error = 0.0;
        for (int j = 0; j < 10; j++)
        {
            auto start = std::chrono::steady_clock::now();
            std::pair<double, double> CDP_answer = centralized_DP_Naive(neighbors, epsilon);
            auto end = std::chrono::steady_clock::now();
            CDP_avg_time += (std::chrono::duration<double>(end - start)).count();
            c_var += pow((CDP_answer.first - true_cycle_answer), 2);
            f_var += pow((CDP_answer.second - true_flow_answer), 2);
            c_relative_error += abs(CDP_answer.first - true_cycle_answer) / (double)true_cycle_answer;
            f_relative_error += abs(CDP_answer.second - true_flow_answer) / (double)true_flow_answer;
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
    
    
    
    for (double epsilon = 2.0; epsilon >= 1.99; epsilon -= 1.0)
    {
        double LDP_avg_time = 0.0;
        double c_var = 0.0, f_var = 0.0;
        double c_relative_error = 0.0, f_relative_error = 0.0;
        for (int j = 0; j < 10; j++)
        {
            auto start = std::chrono::steady_clock::now();
            std::pair<double, double> LDP_answer = localized_DP_Naive(neighbors, epsilon);
            auto end = std::chrono::steady_clock::now();
            LDP_avg_time += (std::chrono::duration<double>(end - start)).count();
            c_var += pow((LDP_answer.first - true_cycle_answer), 2);
            f_var += pow((LDP_answer.second - true_flow_answer), 2);
            c_relative_error += abs(LDP_answer.first - true_cycle_answer) / (double)true_cycle_answer;
            f_relative_error += abs(LDP_answer.second - true_flow_answer) / (double)true_flow_answer;
        }
        LDP_avg_time /= 10;
        c_var /= 10;
        f_var /= 10;
        c_relative_error /= 10;
        f_relative_error /= 10;
        
        std::cout << "time:" << "epsilon:" << epsilon << "LDP_avg_time:" << LDP_avg_time << std::endl;
        std::cout << "var:" << c_var << " " << f_var << std::endl;
        std::cout << "relateive error:" << c_relative_error << " " << f_relative_error << std::endl;
    }
    

    return 0;
}
