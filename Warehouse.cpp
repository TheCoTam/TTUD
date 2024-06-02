#include <bits/stdc++.h>

#define MAXN 1001
#define MAXT 101
using namespace std;

int N, T, D, a[MAXN], t[MAXN], table[MAXT][MAXN];

inline int findMaxGoods(int prevT, int curTruckIndex) {
    int res = 0;
    int start = max(curTruckIndex - D, 1);
    for (int i = start; i < curTruckIndex; ++i) {
        res = max(table[prevT][i], res);
    }
    return res;
}

int main() {
    cin >> N >> T >> D;
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 1; i <= N; ++i) cin >> t[i];

    for (int currentT = 1; currentT <= T; ++currentT) {
        for (int currentTruck = 1; currentTruck <= N; ++currentTruck) {
            if (currentT == t[currentTruck]) {
                table[currentT][currentTruck] = a[currentTruck];
            } else if (currentT < t[currentTruck]) {
                table[currentT][currentTruck] = 0;
            } else {
                int newT = currentT - t[currentTruck];
                int otherTruckGoods = findMaxGoods(newT, currentTruck);
                int currentTruckGoods = a[currentTruck] + otherTruckGoods;
                table[currentT][currentTruck] = currentTruckGoods;
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= N; ++i) {
        int item = table[T][i];
        res = max(res, item);
    }
    cout << res << endl;

    return 0;
}

//6 6 2
//6 8 5 10 11 6
//1 2 2 3 3 2
