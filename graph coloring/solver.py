#!/usr/bin/python
# -*- coding: utf-8 -*-

import random

def node_selector(graph, node_count, colors, available_neighbors):
    best_node = -1
    for i in range(node_count):
        if colors[i] == -1:
            if best_node == -1 or available_neighbors[i] > available_neighbors[best_node]:
                best_node = i
    options = []
    for i in range(node_count):
        if colors[i] == -1 and available_neighbors[i] == available_neighbors[best_node]:
            options.append(i)
    return options[random.randint(0, len(options) - 1)]


def check_optimize(node_count, graph, colors):
    high = max(colors)
    for i in range(node_count):
        if colors[i] >= 0:
            for c in range(colors[i] - 1, -1, -1):
                valid = True
                for j in graph[i]:
                    if colors[j] == c:
                        valid = False
                        break
                if valid == True:
                    return 1000000 * i + c
    return -1
    
    
def find_mincolor(graph, colors, node):
    available = range(0, len(graph[node]) + 2)
    for i in graph[node]:
        if colors[i] != -1 and colors[i] <= len(graph[node]) + 1:
            available[colors[i]] = -1
    for i in available:
        if i != -1:
            return i
    return -1


def greedycoloring(node_count, graph):
    best_coloring = range(0, node_count)
    available_neighbors = [0 for i in range(node_count)]
    
    trials = (10 ** 5) // (node_count * node_count)
    for tr in range(trials):
        colors = [-1 for i in range(node_count)]
        for i in range(node_count):
            available_neighbors[i] = len(graph[i])
        colors[0] = 0
        feasible = 1
        for i in graph[0]:
            available_neighbors[i] -= 1
        for i in range(node_count - 1):
            chosen_node = node_selector(graph, node_count, colors, available_neighbors)
            c = find_mincolor(graph, colors, chosen_node)
            colors[chosen_node] = c
            if c > max(best_coloring):
                feasible = 0
                break
            for i in graph[chosen_node]:
                available_neighbors[i] -= 1
            while True:
                v = check_optimize(node_count, graph, colors)
                if v == -1:
                    break
                node, color = v // 1000000, v % 1000000
                colors[node] = color    
            used_colors = max(colors) + 1
            
        if feasible == 0:
            continue
        while True:
            v = check_optimize(node_count, graph, colors)
            if v == -1:
                break
            node, color = v // 1000000, v % 1000000
            colors[node] = color    
        used_colors = max(colors) + 1
        for i in range(1000):
            chosen_node = random.randint(0, node_count - 1)
            c = find_mincolor(graph, colors, chosen_node)
            if c < colors[c]:
                colors[chosen_node] = c
        
        #print(chosen_node, c)
        if max(colors) < max(best_coloring):
            best_coloring = colors
    
    return best_coloring



def max_violator(node_count, graph, colors):
    best, edges = -1, node_count + 1
    for i in range(node_count):
        bad_edges = 0
        for j in graph[i]:
            if colors[i] == colors[j]:
                bad_edges += 1
        if bad_edges < edges:
            best, edges = i, bad_edges
    if edges == 0:
        return -1
    else:
        return best
    

def local_search(node_count, graph):
    trials = 50
    for tr in range(trials):
        colors = range(0, node_count)
        for i in range(node_count):
            colors[i] = random.randint(0, 6)
        for i in range(12345):
            node = max_violator(node_count, graph, colors)
            if node == -1:
                return colors
            c = find_mincolor(graph, colors, node)
            colors[node] = c
    return -1      
            

adj_matrix = [[]]

def find_setcover(node_count, graph, used_nodes):
    global adj_matrix
    
    trials = 20
    best_set = []
    ids = range(0, node_count)
    for tr in range(trials):
        current_set = []
        random.shuffle(ids)
        for i in ids:
            if used_nodes[i] == 1:
                continue
            available = 1
            for j in current_set:
                if adj_matrix[i][j] == 1:
                    available = 0
                    break
            if available == 1:
                current_set.append(i)
        if len(current_set) > len(best_set):
            best_set = current_set
    return best_set
    

def heuristic_on_colors(node_count, graph):
    best_coloring = range(0, node_count)
    trials = 10
    for tr in range(trials):
        taken = [0 for i in range(node_count)]
        colors = [0 for i in range(node_count)]
        used_colors, used_nodes = 0, 0
        while used_nodes < node_count:
            s = find_setcover(node_count, graph, taken)
            for i in s:
                colors[i] = used_colors
                taken[i] = 1
                used_nodes += 1
            used_colors += 1
        if used_colors < max(best_coloring):
            best_coloring = colors
    return best_coloring
    

def get_colorable_node(node_count, color, colors, graph):
    trials = 50
    for tr in range(trials):
        node = random.randint(0, node_count - 1)
        if colors[node] != -1:
            continue
        valid = True
        for j in graph[node]:
            if colors[j] == color:
                valid = False
                break
        if valid == True:
            return node
    return -1
    


def bipartite_coloring(node_count, graph):
    best_coloring = range(0, node_count)
    trials = 5000 / node_count + 10
    if trials > 500:
        trials = 500
    for tr in range(trials):
        colors = [-1 for i in range(node_count)]
        available_neighbors = [0 for i in range(node_count)]
        for i in range(node_count):
            available_neighbors[i] = len(graph[i])
        used_colors, used_nodes = 0, 0
        while used_nodes < node_count:
            node = node_selector(graph, node_count, colors, available_neighbors)
            #for i in graph[node]:
            #    available_neighbors[i] -= 1
            used_nodes += 1
            colors[node] = used_colors
            while True:
                node = get_colorable_node(node_count, used_colors, colors, graph)
                if node == -1:
                    break
                colors[node] = used_colors
                used_nodes += 1
                #for i in graph[node]:
                #    available_neighbors[i] -= 1
            while True:
                v = check_optimize(node_count, graph, colors)
                if v == -1:
                    break
                node, color = v // 1000000, v % 1000000
                colors[node] = color    
            used_colors = max(colors) + 1
        
        while True:
            v = check_optimize(node_count, graph, colors)
            if v == -1:
                break
            node, color = v // 1000000, v % 1000000
            colors[node] = color    
        used_colors = max(colors) + 1
        
        if max(colors) < max(best_coloring):
            best_coloring = colors
    return best_coloring
        
    

def solve_it(input_data):
    # Modify this code to run your optimization algorithm
    
    # parse the input
    lines = input_data.split('\n')
    
    first_line = lines[0].split()
    node_count = int(first_line[0])
    edge_count = int(first_line[1])
    graph = [[] for i in range(node_count)]
    edges = []
    for i in range(1, edge_count + 1):
        line = lines[i]
        parts = line.split()
        graph[int(parts[0])].append(int(parts[1]))
        graph[int(parts[1])].append(int(parts[0]))
        #edges.append((int(parts[0]), int(parts[1])))
    
    # build a trivial solution
    # every node has its own color
    #solution = range(0, node_count)
    
    global adj_matrix
    adj_matrix = [[0 for i in range(node_count)] for j in range(node_count)]
    for i in range(node_count):
        for j in graph[i]:
            adj_matrix[i][j] = 1
    
    print(local_search(node_count, graph))
    exit(0)
    
    solution = greedycoloring(node_count, graph)
    hs_colors = heuristic_on_colors(node_count, graph)
    if max(hs_colors) < max(solution):
        solution = hs_colors
    
    bs_colors = bipartite_coloring(node_count, graph)
    if max(bs_colors) < max(solution):
        solution = bs_colors  
    # prepare the solution in the specified output format
    output_data = str(max(solution) + 1) + ' ' + str(0) + '\n'
    output_data += ' '.join(map(str, solution))
    
    return output_data


import sys

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/gc_4_1)')

