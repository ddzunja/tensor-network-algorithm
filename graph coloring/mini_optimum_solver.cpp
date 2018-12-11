//
//  mini_optimum_solver.cpp
//  practice
//
//  Created by Mahmud on 12/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

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

typedef vector<vector<int> > graph;

const int MAX_VERTICES = 20;

int N, M;
graph G;
int adjacency[MAX_VERTICES][MAX_VERTICES];
int dp[1 << MAX_VERTICES];

bool independent[1 << MAX_VERTICES];
int maskBitCount[1 << MAX_VERTICES];
int maxIndependentSubsets[1 << MAX_VERTICES];

int main() {
    string filename = "./data/gc_4_1";
    freopen(filename.c_str(), "r", stdin);
    
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
        cout << "Exponential solution does not work" << endl;
        return 0;
    }
    for (int i = 0; i < (1 << N); i ++) {
        bool independent[i] = true;
        for (int j = 0; j < N && independent[i]; j ++) {
            if (i & (1 << j)) {
                for (int k = j + 1; k < N; k ++) {
                    if (i & (1 << k)) {
                        if (adjacency[i][j]) {
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
                maximize(maxIndependentSubsets[i], maxIndependentSubsets[j]);
            }
        }
    }
    dp[0] = 0;
    for (int mask = 1; mask < (1 << N); mask ++) { // iterating over all submasks
        dp[i] = N + 1;
        for (int sub = i; sub > 0; su = (mask - 1) & i) {
            if (maxIndependentSubsets[mask] == maxIndependentSubsets[sub])
            dp[mask] = min(dp[mask], 1 + dp[mask ^ sub]);
        }
    }
    cout << dp[(1 << N) - 1] << endl;
    
    return 0;
}

