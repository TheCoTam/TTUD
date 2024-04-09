//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace chrono;

struct Road {
    int load = 0;
    vector<bool> visited;
    vector<int> road;

    void init(int start, int size) {
        road.push_back(start);
        visited.resize(2*size+1);
        visited.assign(2*size+1, false);
        visited[start] = true;
        load = 1;
    }

    Road addPoint(int newPoint) {
        Road newRoad = *this;

        newRoad.road.push_back(newPoint);
        newRoad.load += 1;
        newRoad.visited[newPoint] = true;

        return newRoad;
    }

    Road removePoint(int newPoint) {
        Road newRoad = *this;

        newRoad.road.push_back(newPoint);
        newRoad.load -= 1;
        newRoad.visited[newPoint] = true;

        return newRoad;
    }

    int getLastPoint() {
        return road[road.size()-1];
    }

    void printRoad() {
        for (auto point: road){
            cout << point << " ";
        }
        cout << endl;
    }
};

struct Compare {
    bool operator()(const pair<int, Road>& a, const pair<int, Road>& b) const {
        return a.first > b.first;
    }
};

int main() {
//    auto start = high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    priority_queue<pair<int, Road>, vector<pair<int, Road>>, Compare> pq;

    cin >> n >> k;

    int distanceMatrix[2 * n + 1][2 * n + 1];

//    initialize distanceMatrix
    for (int x = 0; x <= 2 * n; ++x) {
        for (int y = 0; y <= 2 * n; ++y) {
            int c;
            cin >> c;
            distanceMatrix[x][y] = c;
        }
    }

    for (int i = 1; i <= n; ++i) {
        Road newRoad;
        newRoad.init(i, n+1);
        pq.push(make_pair(distanceMatrix[0][i], newRoad));
    }
//
    cout << n << endl;

    while (!pq.empty()) {
        Road curRoad;
        curRoad = pq.top().second;
        int load = curRoad.load;
        int index = curRoad.getLastPoint();
        int prio = pq.top().first;

        pq.pop();

        if (curRoad.road.size() == 2 * n) {
            curRoad.printRoad();
            break;
        }

        for (int i = 1; i <= 2 * n; ++i) {
            if (curRoad.visited[i]) continue;
            if (i <= n && load < k) {
                if (curRoad.road.size() == 2*n-1) {
                    continue;
                } else {
                    pq.push(make_pair(prio + distanceMatrix[index][i], curRoad.addPoint(i)));
                }
            } else if (i > n && load > 0) {
                if (curRoad.visited[i-n]) {
                    if (curRoad.road.size() == 2*n-1) {
                        pq.push(make_pair(prio + distanceMatrix[index][i]+distanceMatrix[i][0], curRoad.removePoint(i)));
                    } else {
                        pq.push(make_pair(prio + distanceMatrix[index][i], curRoad.removePoint(i)));
                    }
                }
            }
        }
    }

//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
