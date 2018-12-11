//
//  mini_optimum_solver.cpp
//  practice
//
//  Created by Mahmud on 12/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

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

typedef vector<vector<int>> graph;

int N, M;
graph G;

int main() {
    string filename = "./data/gc_4_1";
    freopen(filename, "r", stdin);
    
    cin >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i ++) {
        int u, v;
        cin >> u >> v;
        
    }
    
}

