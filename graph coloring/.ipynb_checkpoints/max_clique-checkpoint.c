//
//  mini_optimum_solver.c
//  practice
//
//  Created by Mahmud on 12/16/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 O(N^2 * 2^N) algorithm to find maximum clique in the graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma GCC optimize("-0g")

const int MAX_VERTICES = 20;

int N, M;
int adjacency[MAX_VERTICES][MAX_VERTICES];
int maskBitCount[1 << MAX_VERTICES];

int main(int argv, char** argc) {
    char* filename = argc[1];
    //filename = "./data/gc_4_1";
    //freopen(filename.c_str(), "r", stdin);
    freopen(filename, "r", stdin);
    freopen("clique_output.txt", "w", stdout);
    
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adjacency[u][v] = 1;
        adjacency[v][u] = 1;
    }
    if (N > 26) {
        printf("Exponential solution will not work\n");
        printf("Of course, you can keep it running until your resources or patience run out\n");
        return 0;
    }
    for (int i = 0; i < (1 << N); i ++) {
        for (int j = 0; j < N; j ++) {
            if (i & (1 << j)) {
                maskBitCount[i] = maskBitCount[i ^ (1 << j)] + 1;
                break;
            }
        }
    }
    int maxClique = 0;
    for (int i = 0; i < (1 << N); i ++) {
        int good = 1;
        for (int j = 0; j < N && good; j ++) {
            if (i & (1 << j)) {
                for (int k = j + 1; k < N; k ++) {
                    if (i & (1 << k)) {
                        if (!adjacency[j][k]) {
                            good = 0;
                            break;
                        }
                    }
                }
            }
        }
        if (good && maskBitCount[i] > maxClique) {
            maxClique = maskBitCount[i];
        }
    }
    printf("Size of the maximum clique of the graph is: %d\n", maxClique);
    
    return 0;
}
