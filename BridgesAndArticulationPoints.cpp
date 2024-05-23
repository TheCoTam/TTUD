#include <bits/stdc++.h>

using namespace std;

#define MAX 100001

vector<int> Adj[MAX];
int N, M, current = 0, Num[MAX], Low[MAX], khop = 0, cau = 0;

void Analyze(int v, int pv) {
    Num[v] = ++current;
    Low[v] = Num[v];

    for (int u: Adj[v]) {
        if (u == pv) continue;
        if (Num[u] == -1) {
            // Xét cạnh xuôi
            Analyze(u, v);
            Low[v] = min(Low[u], Low[v]);
        } else {
            // Xét cạnh ngược
            Low[v] = min(Low[v], Num[u]);
        }
    }

    if (v == 1) {
        if (Adj[v].size() >= 2) khop++;
    } else {
        for (int u: Adj[v]) {
            if (Num[v] <= Low[u]) {
                khop++;
                break;
            }
        }
    }

    for (int u: Adj[v]) {
        if (Num[v] < Low[u]) {
            cau++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }
    for (int i = 1; i <= N; ++i)Num[i] = -1;
    Analyze(1, 0);

    cout << khop << " " << cau;

    return 0;
}

//10 12
//1 10
//10 2
//10 3
//2 4
//4 5
//5 2
//3 6
//6 7
//7 3
//7 8
//8 9
//9 7