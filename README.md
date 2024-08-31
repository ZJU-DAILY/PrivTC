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
Notice that we delete all self-loops and treat multi-edges as simple edges. The datasets/toy_graph.txt is an example format of the input data.
## Algorithms
We implement algorithms in our paper in C++. The following files contain the source code of these algorithms:   
1.`/code/PrivTC/CDPCounting.cpp`: The proposed centralized algorithm for triangle counting with edge-CDP in directed graphs.   
2.`/code/PrivTC/LDPCounting.cpp`: The proposed local algorithm for triangle counting with edge-LDP in directed graphs.   
3.`/code/PrivTC_Naive/CDPNaive.cpp`: The strawman solution of triangle counting with edge-CDP in directed graphs.   
4.`/code/PrivTC_Naive/LDPNaive.cpp`: The strawman solution of triangle counting with edge-LDP in directed graphs.
## Usage
