//C++
#include <bits/stdc++.h>

using namespace std;

void solve(int k, int f, int n, int M, int a[], int preS[], int &res) {
    int max = (M - f - (preS[n - 1] - preS[k])) / a[k];
    for (int i = 1; i <= max; ++i) {
        int newF = f + a[k] * i;
        if (k < n - 1) solve(k + 1, newF, n, M, a, preS, res);
        else {
            if (newF == M) {
                res += 1;
            }
        }
    }
}

int main() {
    int n, M, res = 0;
    cin >> n >> M;
    int a[n], preS[n];
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        a[i] = val;
        if (i == 0) {
            preS[i] = val;
        } else {
            preS[i] = preS[i - 1] + val;
        }
    }

    solve(0, 0, n, M, a, preS, res);
    cout << res << endl;
}
