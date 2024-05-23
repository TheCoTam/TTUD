#include <bits/stdc++.h>

using namespace std;

#define MAX 100001

vector<int> Adj[MAX], start(MAX, 0);
int N, M, duration[MAX], c[MAX], res = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    memset(c, 0, N + 1);
    for (int i = 1; i <= N; ++i) cin >> duration[i];
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        c[v]++;
        Adj[u].push_back(v);
    }

    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (c[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        res = max(res, start[u] + duration[u]);
        for (int v: Adj[u]) {
            start[v] = max(start[v], start[u] + duration[u]);
            res = max(res, start[u] + duration[u]);
            c[v]--;
            if (c[v] == 0)q.push(v);
        }
    }

    cout << res;

    return 0;
}

//9 13
//5 3 1 2 6 4 3 1 4
//1 3
//1 5
//1 6
//2 1
//2 3
//3 5
//4 1
//4 2
//4 6
//5 8
//7 9
//9 5
//9 8