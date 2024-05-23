#include <bits/stdc++.h>

using namespace std;

inline int rmq(int i, int j, vector<vector<int>> sparseTable, vector<int> sequence) {
    int k = floor(log2(j - i + 1));
    int l = sparseTable[k][i];
    int r = sparseTable[k][j - int(pow(2, k)) + 1];
    if (sequence[l] < sequence[r]) {
        return sequence[l];
    } else {
        return sequence[r];
    }
}

int rmq(int i, int j) {

    return 0;
}

int main() {
    int n, a, m, res = 0;
    cin >> n;
    int s = floor(log2(n + 1));
    vector<int> sequence;
    vector<vector<int>> sparseTable(s + 1);
    for (int x = 0; x < n; x++) {
        cin >> a;
        sequence.push_back(a);
        sparseTable[0].push_back(x);
    }
    for (int x = 1; x <= s; x++) {
        int end = n + 1 - int(pow(2, x));
        for (int y = 0; y < end; y++) {
            int left = sparseTable[x - 1][y];
            int right = sparseTable[x - 1][y + int(pow(2, x - 1))];
            if (sequence[left] < sequence[right]) {
                sparseTable[x].push_back(left);
            } else {
                sparseTable[x].push_back(right);
            }
        }
    }

    cin >> m;

    for (int y = 0; y < m; y++) {
        int i, j;
        cin >> i >> j;
        cout << rmq(i, j, sparseTable, sequence) << endl;
        res += rmq(i, j, sparseTable, sequence);
    }

    cout << res << endl;
    return 0;
}
