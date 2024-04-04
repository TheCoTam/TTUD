//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

int N, n, C;

bool check(vector<int> &sequence, int d) {
    int left = sequence[0];

    for (int i = 1; i < C; ++i) {
        int index = upper_bound(sequence.begin(), sequence.end(), left + d - 1) - sequence.begin();
        if (index >= n) {
            return false;
        }

        left = sequence[index];
    }

    return true;
}

int main() {
//    auto start = high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> n >> C;
        vector<int> sequence;
        for (int j = 0; j < n; ++j) {
            int input;
            cin >> input;
            sequence.push_back(input);
        }

        sort(sequence.begin(), sequence.end());

        int d = (sequence[n - 1] - sequence[0]) / (C - 1);

        while (d > 0) {
            if (check(sequence, d)) {
                break;
            }
            d--;
        }

        cout << d << endl;
    }
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}
