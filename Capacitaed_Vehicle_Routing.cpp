//C++
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

int n, K, Q, segments = 0, allPath = 0, nbR = 0, Cmin = 99999, res = 99999;

bool checkY(int startingPoint, int truckIndex, const int* load, const bool* visited, const int* d) {
//    skip this truck
    if (startingPoint == 0) return true;
//    do not consider if current capacity + requested packages > max capacity
    if (load[truckIndex] + d[startingPoint] > Q) return false;
//    already delivery to this client
    if (visited[startingPoint]) return false;
    return true;
}

bool checkX(int nextPoint, int truckIndex, const int* load, const bool* visited, const int* d) {
//    if next delivery point already visited
    if (nextPoint > 0 && visited[nextPoint]) return false;
//    do not consider if current capacity + requested packages > max capacity
    if (load[truckIndex] + d[nextPoint] > Q) return false;
    return true;
}

void updateBest() {
    if (allPath < res) res = allPath;
}

void tryX(int &curPoint, int truckIndex, int* startingPointOfTruck, int* load, bool* visited, const int* d, int** c, int* afterStartingPointOfTruck) {
    if (curPoint == 0) {
//        current truck does not delivery packages -> consider next truck (if have)
        if (truckIndex < K) tryX(startingPointOfTruck[truckIndex + 1], truckIndex + 1, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
        return;
    }
    for (int i = 0; i <= n; ++i) {
        if (checkX(i, truckIndex, load, visited, d)) {
//            update data structure
            afterStartingPointOfTruck[truckIndex] = i;
            visited[i] = true;
            allPath += c[curPoint][i];
            load[truckIndex] += d[i];
            segments += 1;
            if (i > 0) {
                if (allPath + Cmin * (n + nbR - segments) < res) tryX(i, truckIndex, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
            } else {
                if (truckIndex == K) {
                    if (segments == n + nbR) updateBest();
                } else {
                    if (allPath + Cmin * (n + nbR - segments) < res)
                        tryX(startingPointOfTruck[truckIndex + 1], truckIndex + 1, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
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

void tryY(int truckIndex, int* startingPointOfTruck, int* load, bool* visited, const int* d, int** c, int* afterStartingPointOfTruck) {
    int s = 0;
    if (startingPointOfTruck[truckIndex - 1] > 0) {
        s = startingPointOfTruck[truckIndex - 1] + 1;
    }
    for (int i = s; i <= n; ++i) {
        if (checkY(i, truckIndex, load, visited, d)) {
//            update data structure
            startingPointOfTruck[truckIndex] = i;
            if (i > 0) segments += 1;
            visited[i] = true;
            allPath += c[0][i];
            load[truckIndex] += d[i];
            if (truckIndex < K) tryY(truckIndex + 1, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
            else {
                nbR = segments;
                tryX(startingPointOfTruck[1], 1, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> K >> Q;

    int d[n+1], startingPointOfTruck[K+1], afterStartingPointOfTruck[K+1], load[n+1];
    int** c = new int *[n+1];
    bool visited[n+1];

    // init default value of arrays
    memset(d, 0, sizeof(d));
    memset(startingPointOfTruck, 0, sizeof(startingPointOfTruck));
    memset(afterStartingPointOfTruck, 0, sizeof(afterStartingPointOfTruck));
    memset(load, 0, sizeof(load));
    memset(visited, false, sizeof(visited));

//    initialize requested packages of clients
    for (int i = 0; i <= n; ++i) {
        if (i == 0) {
            d[i] = 0;
        } else {
            int val;
            cin >> val;
            d[i] = val;
        }
    }

//    initialize distance matrix
    for (int i = 0; i <= n; ++i) {
        c[i] = new int [n+1];
        for (int j = 0; j <= n; ++j) {
            int val;
            cin >> val;
            if (i != j) Cmin = min(Cmin, val);
            c[i][j] = val;
        }
    }

    tryY(1, startingPointOfTruck, load, visited, d, c, afterStartingPointOfTruck);
    cout << res << endl;
//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    for (int x = 0; x <= n; ++x) {
        delete[] c[x];
    }
    delete[] c;
    return 0;
}
