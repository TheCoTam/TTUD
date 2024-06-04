#include <bits/stdc++.h>

#define dayOff 0
#define lastDayWorking 1
#define MAX 1001
using namespace std;

int N, K1, K2;
int table[2][MAX];

inline int findAllCase(int index) {
    int res = 0;
    if (index - K1 < 1) return 0;
    int start = max(index - K2, 1);
    int end = max(index - K1, 1);
    for (int i = start; i <= end; ++i) {
        res += table[dayOff][i];
    }
    return res;
}

int main() {
    cin >> N >> K1 >> K2;
    table[dayOff][1] = 1;
    table[lastDayWorking][1] = 0;
    for (int i = 2; i <= N; ++i) {
        table[dayOff][i] = table[lastDayWorking][i - 1];
        if (i < K1) {
            table[lastDayWorking][i] = 0;
        } else if (i <= K2) {
            table[lastDayWorking][i] = findAllCase(i) + 1;
        } else {
            table[lastDayWorking][i] = findAllCase(i);
        }
    }
    cout << table[dayOff][N] + table[lastDayWorking][N] << endl;

    return 0;
}

// Input
// 6 2 3
// Output
// 4
