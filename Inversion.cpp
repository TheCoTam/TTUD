//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

const long AAA = 1000000007;

int n;
vector<int> sequence;
long res = 0;

void merge_sort(vector<int> &sequence, int left, int right) {

    if (left >= right) return;

    int mid = (left + right) / 2;

    merge_sort(sequence, left, mid);
    merge_sort(sequence, mid + 1, right);

    vector<int> A(sequence.begin() + left, sequence.begin() + mid + 1);
    vector<int> B(sequence.begin() + mid + 1, sequence.begin() + right + 1);

    int i = 0, j = 0;

    while (true) {
        if (i == A.size() && j == B.size()) break;
        if (i == A.size()) {
            for (; j < B.size(); ++j) {
                sequence[left] = B[j];
                left++;
            }
            break;
        }
        if (j == B.size()) {
            for (; i < A.size(); ++i) {
                sequence[left] = A[i];
                left++;
            }
            break;
        }

        if (A[i] > B[j]) {
//            cout << B[j]<<  " " << A[i] << endl;
            sequence[left] = B[j];
            j++;
            res += A.size() - i;
            res = res % AAA;
        } else {
            sequence[left] = A[i];
            i++;
        }
        left++;
    }
}

int main() {
//    auto start = high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        sequence.push_back(input);
    }

    merge_sort(sequence, 0, n - 1);

    cout << res << endl;

//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}
