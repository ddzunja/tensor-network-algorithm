//
//  mini_optimum_solver.c
//  practice
//
//  Created by Mahmud on 12/15/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 O(3^N) deterministic algorithm to find
    optimal graph coloring.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma GCC optimize("-0g")

const int MAX_VERTICES = 20;

int N, M;
int adjacency[MAX_VERTICES][MAX_VERTICES];
int dp[1 << MAX_VERTICES];

int independent[1 << MAX_VERTICES];
int maskBitCount[1 << MAX_VERTICES];
int maxIndependentSubsets[1 << MAX_VERTICES];
int parent[1 << MAX_VERTICES];

int main(int argv, char** argc) {
    char* filename = argc[1];
    //filename = "./data/gc_4_1";
    //freopen(filename.c_str(), "r", stdin);
    freopen(filename, "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adjacency[u][v] = 1;
        adjacency[v][u] = 1;
    }
    if (N > 20) {
        printf("Exponential solution will not work\n");
        printf("Of course, you can keep it running until your resources or patience run out\n");
        return 0;
    }
    for (int i = 0; i < (1 << N); i ++) {
        independent[i] = 1;
        for (int j = 0; j < N && independent[i]; j ++) {
            if (i & (1 << j)) {
                for (int k = j + 1; k < N; k ++) {
                    if (i & (1 << k)) {
                        if (adjacency[j][k]) {
                            independent[i] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    maskBitCount[0] = 0;
    for (int mask = 1; mask < (1 << N); mask ++) {
        for (int bit = 0; bit < N; bit ++) {
            if (mask & (1 << bit)) {
                maskBitCount[mask] = maskBitCount[mask ^ (1 << bit)] + 1;
                break;
            }
        }
    }
    for (int i = 0; i < (1 << N); i ++) {
        for (int j = i; j > 0; j = (j - 1) & i) {
            if (independent[j]) {
                //maximize(maxIndependentSubsets[i], maskBitCount[j]);
                if (maskBitCount[j] > maxIndependentSubsets[i]) {
                    maxIndependentSubsets[i] = maskBitCount[j];
                    //parent[i] = j;
                }
            }
        }
    }
    dp[0] = -1;
    for (int mask = 1; mask < (1 << N); mask ++) { // submask enumeration
        dp[mask] = N + 1;
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (maxIndependentSubsets[mask] == maxIndependentSubsets[sub]
                && maxIndependentSubsets[sub] == maskBitCount[sub]) {
                if (1 + dp[mask ^ sub] < dp[mask]) {
                    dp[mask] = 1 + dp[mask ^ sub];
                    parent[mask] = sub;
                }
            }
            
        }
    }
    printf("chromatic number is equal to %d\n", dp[(1 << N) - 1] + 1);
    
    // recovering the optimal setting of colors
    
    int path[MAX_VERTICES];
    int colors[MAX_VERTICES];
    int current = (1 << N) - 1;
    int activeColor = 0;
    while (current > 0) {
        int activeSet = parent[current];
        for (int i = 0; i < N; i ++) {
            if (activeSet & (1 << i)) {
                colors[i] = activeColor;
            }
        }
        current = current ^ parent[current];
        activeColor ++;
    }
    printf("Assigned colors in optimal coloring is:\n");
    for (int i = 0; i < N; i ++) {
        printf("color of node %d is %d\n", i, colors[i]);
    }
    
    return 0;
}
