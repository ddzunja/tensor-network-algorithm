# Tensor Network Algorithms
As we can see from the partial success of Ising model describing phase transition, chains which composed of combinatorial objects and sites are important. In this project, we implement basic tensor network algorithms.The graph coloring visualizations and calculations over Hoffman bounding is done in the file named "Graph visualization.ipynb".

## Implementation of graph coloring based on heuristic methods in Python
    The following methods have been used:
    - Local search (tabu will be added)
    - greedy heuristic (logarithmic upper bound)
    - set cover based approach
    - bipartite coloring based optimization

## C++ optimum chromatic number solver for mini graphs
    - Assuming the number of vertices < 20
    - Complexity of calculating chromatic number is O(3^N)
    - Memory complexity of calculating the coloring itself is O(2^N)
    - To compile the solver in C++11 use command: make mini_optimum_solver
    - To run the specified data file use command: ./mini_optimum_solver graph_file
    - To compile the solver in C++11 use command: make mini_optimum_solver
    - To run the specified data file use command: ./mini_optimum_solver graph_file

## C++ optimum maximum clique solver for mini graphs
    - Assuming the number of vertices < 25
    - Complexity of calculating chromatic number is O(2^N * N^2)
    - Memory complexity of calculating the coloring itself is O(N^2) (storing the adjacency matrix of the graph)
    - To compile the solver in C++11 use command: make mini_optimum_solver
    - To run the specified data file use command: ./max_clique graph_file
    - To compile the solver in C++11 use command: make max_clique
    - To run the specified data file use command: ./max_clique graph_file

## C++ bipartite graph checker
    - Linear time algorithm to check if chromatic number is 2
    - Depth search routines are used to verify bipartiteness of the graph
    - The outlining method can be replaced by BFS alsgorithm as well.

## Tensor Renormalization Group algorithm

    - Choose Honeycomb lattice network
    - Calculate Hamiltonian
    - Geometrical replacement of tensors
    - Using SVD decomposition
    - Reducing rank
    - Merging
    - Calculating energy


## Participitants(Skoltech 2018-NLA-14)
- Mahmud Allahverdiyev - Data Science Msc. 1st year student
- Dejan Dzunja - Data Science Msc. 1st year student
- Mohammad Ali Sadri - Data Science Msc. 1st year student
- Woongseon Yoo - Data Science Msc. 1st year student



