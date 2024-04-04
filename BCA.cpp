//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

int n, m, res;
vector<unordered_set<int>> preferenceList;
vector<unordered_set<int>> conflict;
vector<unordered_set<int>> curCourse;
bool changed = false;

//bool check(int teacher, int course) {
//    for (int val: conflict[course]) {
//        auto it = curCourse[teacher].find(val);
//        if (it != curCourse[teacher].end()) return false;
//    }
//    return true;
//}

bool check(int teacher, int course) {
//    const auto& teacherCourses = curCourse[teacher];
    for (int val : conflict[course]) {
        if (curCourse[teacher].count(val)) {
            return false;
        }
    }
    return true;
}

void solve(int course) {

    if (course > n) {
        int maxVal = 0;
        for (auto it: curCourse) {
            maxVal = max(maxVal, int(it.size()));
        }
        res = maxVal;
        changed = true;
        return;
    }
    for (int i = 0; i < m; ++i) {
        auto it = preferenceList[i].find(course);
        if (it != preferenceList[i].end() && check(i, course)) {
//            course exists in this teacher's preferenceList and that course is valid
            curCourse[i].insert(course);
            if (curCourse[i].size() < res) {
                solve(course + 1);
            }
            curCourse[i].erase(course);
        }
    }
}

int main() {
//    auto start = high_resolution_clock::now();
    cin >> m >> n;
//    res = m/2+1;
    res = 6;
    conflict.resize(n + 1);
    curCourse.resize(m);
    preferenceList.resize(m);
    for (int i = 0; i < m; ++i) {
        int length;
        cin >> length;
        for (int j = 0; j < length; ++j) {
            int input;
            cin >> input;
            preferenceList[i].insert(input);
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        conflict[x].emplace(y);
        conflict[y].emplace(x);
    }

    solve(1);
    if (changed) cout << res << endl;
    else cout << -1 << endl;

//    auto stop = high_resolution_clock::now(); // Kết thúc đo thời gian
//    auto duration = duration_cast<milliseconds>(stop - start); // Tính thời gian thực hiện
//
//    cout << "Thời gian thực hiện: " << duration.count() << " milliseconds" << endl; // In thời gian thực hiện ra màn hình

    return 0;
}
