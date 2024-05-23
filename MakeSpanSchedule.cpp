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
