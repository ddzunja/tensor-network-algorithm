# Tensor-network-algorithms
As we can see from the partial success of Ising model describing phase transition, chains which composed of combinatorial objects and sites are important. In this project, we implement basic tensor network algorithms.

## Graph algorithm

## Renormalization Group algorithm

## Participitants(Skoltech 2018-NLA-14)
Mahmud Allahverdiyev - Data Science Msc. 1st year student
Dejan Dzunja - Data Science Msc. 1st year student
Mohammad Ali Sadri - Data Science Msc. 1st year student
Woong-seon - Data Science Msc. 1st year student



## Implementation of graph coloring based on heuristic methods in Python
    The following methods have been used:
    - Local search
    - greedy heuristic (logarithmic upper bound)
    - set cover based approach
    - bipartite coloring

## C++ optimum solver for mini graphs
    - Assuming the number of vertices < 20
    - Complexity of calculating chromatic number is O(3^N)
    - Memory complexity of calculating the coloring itself is O(2^N)
    - To compile the solver in C++11 use command: make mini_optimum_solver
    - To run the specified data file use command: ./mini_optimum_solver graph_file
    - To compile the solver in C++11 use command: make mini_optimum_solver
    - To run the specified data file use command: ./mini_optimum_solver graph_file

## C++ bipartite graph checker
    - Linear time algorithm to check if chromatic number is 2
    - Depth search routines are used to verify bipartiteness of the graph
    - The outlining method can be replaced by BFS alsgorithm as well.
