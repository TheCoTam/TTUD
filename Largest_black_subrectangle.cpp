#include <bits/stdc++.h>

using namespace std;

inline int largestRectangleInHistogram(vector<int> histogram) {
    stack<int> s;
    int maxArea = 0;
    int area = 0;
    int i = 0;
    int size = histogram.size();

    while (i < size) {
        if (s.empty() || histogram[s.top()] <= histogram[i]) {
            s.push(i);
            i++;
        } else {
            int top = s.top();
            s.pop();
            area = histogram[top] * (s.empty() ? i : (i - s.top() - 1));
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    while (!s.empty()) {
        int top = s.top();
        s.pop();
        area = histogram[top] * (s.empty() ? i : (i - s.top() - 1));
        if (area > maxArea) {
            maxArea = area;
        }
    }

    return maxArea;
}


int main() {
//    int n, m, maxArea = 0;
//    cin >> n >> m;
//    vector<vector<int>> row(n);
//    for (int i = 0; i < m; i++) {
//        int val;
//        cin >> val;
//        row[0].push_back(val);
//    }
//    for (int i = 1; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            int val;
//            cin >> val;
//            if (val != 0) {
//                row[i].push_back(val + row[i - 1][j]);
//            } else {
//                row[i].push_back(0);
//            }
//        }
//        int area = largestRectangleInHistogram(row[i]);
//        maxArea = max(maxArea, area);
//    }
//    cout << maxArea << endl;
    vector<int> test = {3,2,1,2};
    cout << largestRectangleInHistogram(test) << endl;
    return 0;
}
