//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

int n, m, res;
vector<unordered_set<int>> preferenceList;
vector<unordered_set<int>> conflict;
vector<unordered_set<int>> curCourse;
priority_queue<pair<int, int>> pq;
vector<int> finalList;
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
    for (int val: conflict[course]) {
        if (curCourse[teacher].count(val)) {
            return false;
        }
    }
    return true;
}

void solve(int index) {
    int course = finalList[index];

    if (index == n) {
        int maxVal = 0;
        for (const auto &it: curCourse) {
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
                solve(index + 1);
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

    // each element of priority_queue pq  contains number of teachers can take certain course and index of this certain course
    for (int i = 0; i <= n; ++i) {
        if (i == 0) continue;
        int count = 0;
        for (const auto &teacher: preferenceList) {
            if (teacher.count(i)) count++;
        }
        pq.push(make_pair(count, i));
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        conflict[x].emplace(y);
        conflict[y].emplace(x);
    }

    // finalList is a vector of courses that sorted in ascending order of number of teachers can take course
    // for example: the first element of finalList is the course that fewest teachers can take it
    while(!pq.empty()) {
        int index = pq.top().second;
        finalList.insert(finalList.begin(), index);
        pq.pop();
    }

    solve(0);
    if (changed) cout << res << endl;
    else cout << -1 << endl;

//    auto stop = high_resolution_clock::now(); // Kết thúc đo thời gian
//    auto duration = duration_cast<milliseconds>(stop - start); // Tính thời gian thực hiện
//
//    cout << "Thời gian thực hiện: " << duration.count() << " milliseconds" << endl; // In thời gian thực hiện ra màn hình

    return 0;
}
