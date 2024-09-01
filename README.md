# Privacy-preserving Triangle Counting in Directed Graphs
## Introduction
This repository contains the source code for **Privacy-preserving Triangle Counting in Directed Graphs**. 
We study two scenarios for triangle counting in directed graphs under edge differential privacy (edge-DP). One for trusted central servers under edge centralized differential privacy (edge-CDP), the other for untrusted central server under edge local differential privacy (edge-LDP).
## Datasets
We use 6 real-world directed graphs to evaluate our proposed algorithms. All datasets can be downloaded from [SNAP](https://snap.stanford.edu/data/). We preprocess each dataset to an uniform format. The uniform format of the dataset contains n vertices is
```
lambda_{1,1} lambda_{1,2} ... lambda_{1,n}
lambda_{2,1} lambda_{2,2} ... lambda_{2,n}
...
lambda_{n,1} lambda_{n,2} ... lambda_{n,n}
```
where `lambda_{i,j} = 1` if there exits an edge from vertex `v_{i}` to `v_{j}`, and otherwise, `lambda_{i,j} = 0`.
Notice that we delete all self-loops and treat multi-edges as simple edges. The `datasets/toy_graph.txt` is an example format of the input data.
## Algorithms
We implement algorithms in our paper in C++. The following files contain the source code of these algorithms:   
1.`/code/PrivTC/CDPCounting.cpp`: The proposed centralized algorithm for triangle counting with edge-CDP in directed graphs (CDP).   
2.`/code/PrivTC/LDPCounting.cpp`: The proposed local algorithm for triangle counting with edge-LDP in directed graphs (LDP).   
3.`/code/PrivTC_Naive/CDPNaive.cpp`: The strawman solution of triangle counting with edge-CDP in directed graphs (CDP Naive).   
4.`/code/PrivTC_Naive/LDPNaive.cpp`: The strawman solution of triangle counting with edge-LDP in directed graphs (LDP Naive).
## Usage
1.**CDP** and **LDP** (Test the **impact of privacy budget**): Compile all the files in `/code/PrivTC/` by using:
```
g++ -o main main.cpp
```
Then run `main`.   
2.**CDP Naive** and **LDP Naive** (Test the **impact of privacy budget**): Complie all the files in `/code/PrivTC_Naive/` by using:
```
g++ -o main main.cpp
```
Then run `main`.   
3.Test the **impact of graph size** on **CDP** and **LDP**: To generate subgraphs of the input-directed graph, complie all the files in `/code/PriTC_test_graph_size/sampling/` by using:
```
g++ -o sampling sampling.cpp
```
The run `sampling` to generate subgraphs.      
Then compile all the files in `/code/PrivTC_test_graph_size/` except the folder `sampling` by using:
```
g++ -o main_V main_V.cpp
```
Then run `main_V`.   
4.Test the **impact of privacy budget allocation** on **CDP** and **LDP**: Complie all the files in `/code/PrivTC_test_privacy_budget_allocation` by using:
```
g++ -o main_epsratio main_espratio.cpp
```
Then run `main_epsratio`.   
5.Test the **impact of projection degree** on **CDP** and **LDP**: Complie all the files in `/code/PrivTC_test_projection_degree` by using:
```
g++ -o main_dmax main_dmax.cpp
```
Then run `main_dmax`.   
## Requirements
- GCC 11.2.1
- [StatsLib](https://www.kthohr.com/statslib.html)
- [gcem](https://www.kthohr.com/gcem.html)
