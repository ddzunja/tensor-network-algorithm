//
//  mini_optimum_solver.cpp
//  practice
//
//  Created by Mahmud on 12/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 O(3^N) deterministic algorithm to find
    optimal graph coloring.
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#pragma GCC optimize("-0g")

template <class T>
void fastInput(T &N) {
    char ch;
    int sign = 1;
    N = 0;
    while ((ch = getchar_unlocked()) && ch == ' ') {};
    if (ch == '-') sign = -1;
    else if (isdigit(ch)) N = ch - '0';
    while ((ch = getchar_unlocked()) && isdigit(ch)) {
        N = (N << 1) + (N << 3) + ch - '0';
    }
    if (sign == -1) N = ~N + 1;
}
template<class T> void fastPrint(T n){
    if(n == 0){
        puts("0");
        return;
    }
    char buffer[256];
    int ptr = 0, sign = 1;
    
    if(n < 0){
        sign = -1;
        n *= -1;
    }
    while(n > 0){
        buffer[ptr ++] = (char)(n % 10 + '0');
        n /= 10;
    }
    if(sign == -1)
    putchar_unlocked('-');
    for(int i = ptr - 1; i >= 0; i --)
    putchar_unlocked(buffer[i]);
    putchar_unlocked('\n');
}

typedef vector<vector<int> > graph;

const int MAX_VERTICES = 20;

int N, M;
graph G;
int adjacency[MAX_VERTICES][MAX_VERTICES];
int dp[1 << MAX_VERTICES];

bool independent[1 << MAX_VERTICES];
int maskBitCount[1 << MAX_VERTICES];
int maxIndependentSubsets[1 << MAX_VERTICES];
int parent[1 << MAX_VERTICES];

void maximize(int &a, int b) {
    if (a < b) {
        a = b;
    }
}
void minimize(int &a, int b) {
    if (a > b) {
        a = b;
    }
}


int main(int argv, char** argc) {
    char* filename = argc[1];
    //filename = "./data/gc_4_1";
    //freopen(filename.c_str(), "r", stdin);
    freopen(filename, "r", stdin);
    
    cin >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i ++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        adjacency[u][v] = 1;
        adjacency[v][u] = 1;
    }
    if (N > 20) {
        cout << "Exponential solution will not work" << endl;
        cout << "Of course, you can keep it running until your resources or patience run out" << endl;
        return 0;
    }
    for (int i = 0; i < (1 << N); i ++) {
        independent[i] = true;
        for (int j = 0; j < N && independent[i]; j ++) {
            if (i & (1 << j)) {
                for (int k = j + 1; k < N; k ++) {
                    if (i & (1 << k)) {
                        if (adjacency[j][k]) {
                            independent[i] = false;
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
                    parent[i] = j;
                }
            }
        }
    }
    dp[0] = 0;
    for (int mask = 1; mask < (1 << N); mask ++) { // submask enumeration
        dp[mask] = N + 1;
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (maxIndependentSubsets[mask] == maxIndependentSubsets[sub]
                && maxIndependentSubsets[sub] == maskBitCount[sub])
            dp[mask] = min(dp[mask], 1 + dp[mask ^ sub]);
        }
    }
    cout << "chromatic number is equal to " << dp[(1 << N) - 1] << endl;
    
    
    // recovering the optimal setting of colors
    
    vector<int> path;
    vector<int> colors(N);
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
    cout << "Assigned colors in optimal coloring is:" << endl;
    for (int i = 0; i < N; i ++) {
        cout << "color of node " << i << " is " << colors[i] << endl;
    }
    
    return 0;
}
