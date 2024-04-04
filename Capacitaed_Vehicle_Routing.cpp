//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

int n, K, Q, segments = 0, allPath = 0, nbR = 0, Cmin = 99999, res = 99999;
vector<int> d, startingPointOfTruck, load, afterStartingPointOftruck;
vector<bool> visited;
vector<vector<int>> c;

bool checkY(int startingPoint, int truckIndex) {
//    skip this truck
    if (startingPoint == 0) return true;
//    do not consider if current capacity + requested packages > max capacity
    if (load[truckIndex] + d[startingPoint] > Q) return false;
//    already delivery to this client
    if (visited[startingPoint]) return false;
    return true;
}

bool checkX(int nextPoint, int truckIndex) {
//    if next delivery point already visited
    if (nextPoint > 0 && visited[nextPoint]) return false;
//    do not consider if current capacity + requested packages > max capacity
    if (load[truckIndex] + d[nextPoint] > Q) return false;
    return true;
}

void updateBest() {
    if (allPath < res) res = allPath;
}

void tryX(int &curPoint, int truckIndex) {
    if (curPoint == 0) {
//        current truck does not delivery packages -> consider next truck (if have)
        if (truckIndex < K) tryX(startingPointOfTruck[truckIndex + 1], truckIndex + 1);
        return;
    }
    for (int i = 0; i <= n; ++i) {
        if (checkX(i, truckIndex)) {
//            update data structure
            afterStartingPointOftruck[truckIndex] = i;
            visited[i] = true;
            allPath += c[curPoint][i];
            load[truckIndex] += d[i];
            segments += 1;
            if (i > 0) {
                if (allPath + Cmin * (n + nbR - segments) < res) tryX(i, truckIndex);
            } else {
                if (truckIndex == K) {
                    if (segments == n + nbR) updateBest();
                } else {
                    if (allPath + Cmin * (n + nbR - segments) < res)
                        tryX(startingPointOfTruck[truckIndex + 1], truckIndex + 1);
                }
            }
//             restore data structure
            segments -= 1;
            visited[i] = false;
            allPath -= c[curPoint][i];
            load[truckIndex] -= d[i];
        }
    }
}

void tryY(int truckIndex) {
    int s = 0;
    if (startingPointOfTruck[truckIndex - 1] > 0) {
        s = startingPointOfTruck[truckIndex - 1] + 1;
    }
    for (int i = s; i <= n; ++i) {
        if (checkY(i, truckIndex)) {
//            update data structure
            startingPointOfTruck[truckIndex] = i;
            if (i > 0) segments += 1;
            visited[i] = true;
            allPath += c[0][i];
            load[truckIndex] += d[i];
            if (truckIndex < K) tryY(truckIndex + 1);
            else {
                nbR = segments;
                tryX(startingPointOfTruck[1], 1);
            }

//            restore data structure
            if (i > 0) segments -= 1;
            visited[i] = false;
            allPath -= c[0][i];
            load[truckIndex] -= d[i];
        }
    }
}

int main() {
//    auto start = high_resolution_clock::now();
    cin >> n >> K >> Q;

//    initialize requested packages of clients
    for (int i = 0; i <= n; ++i) {
        if (i == 0) {
            d.push_back(0);
        } else {
            int val;
            cin >> val;
            d.push_back(val);
        }
    }

//    initialize distance matrix
    for (int i = 0; i <= n; ++i) {
        vector<int> row;
        for (int j = 0; j <= n; ++j) {
            int val;
            cin >> val;
            if (i != j) Cmin = min(Cmin, val);
            row.push_back(val);
        }
        c.push_back(row);
    }

    startingPointOfTruck.resize(K + 1);
    afterStartingPointOftruck.resize(K + 1);
    visited.resize(n + 1);
    load.resize(n + 1);

    tryY(1);
    cout << res << endl;
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}
