//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace chrono;

int main() {
//    auto start = high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int data[n], memo[n];
    bool calculated[n];
    memset(calculated, false, sizeof(calculated));

    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        data[i] = input;
    }

    int max_sum = data[0];
    int res = max_sum;
    for (int i = 1; i < n; ++i) {
        max_sum = max(data[i], data[i] + max_sum);
        res = max(res, max_sum);
    }

    cout << res << endl;

//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
