//C++
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int n, k, res = 99999, load = 0, path = 0, Cmin = 9999;
//vector<vector<int>> distanceMatrix;
//vector<bool> visited;
//vector<int> route;
vector<int> routePath;
vector<int> realPath;

//print current path of bus
void printPath() {
    for (int i = 0; i < realPath.size(); i++) {
        cout << realPath[i] << " ";
    }
    cout << endl;
}

bool check(int v, const bool *visited) {
//    not consider point that was visited
    if (visited[v]) return false;
    if (v > n) {
//        not consider drop off point if passenger is not on bus
        if (!visited[v - n]) return false;
    } else {
//        not consider pick-up point if bus is full
        if (load + 1 > k) return false;
    }
    return true;
}

void updateBest(int **distanceMatrix, const int *route) {
//    update optimal value if find more optimal value
    if (path + distanceMatrix[route[2 * n]][0] < res){
        res = path + distanceMatrix[route[2 * n]][0];
        realPath = routePath;
    }
}

void solve(int index, int **distanceMatrix, bool *visited, int *route) {
    for (int v = 1; v <= 2 * n; ++v) {
//        consider next point
        if (check(v, visited)) {
//            print current path
            routePath.push_back(v);

//            update data structure
            route[index] = v;
            path += distanceMatrix[route[index - 1]][route[index]];
            visited[v] = true;

//            change load according to next point
            if (v <= n) {
                load += 1;
            } else {
                load -= 1;
            }

            if (index == 2 * n) {
//                if a solution is found
//                cout << "Update is here " << path + distanceMatrix[2 * n][0] << " " << res << endl;
                updateBest(distanceMatrix, route);
            } else {
                if (path + Cmin * (2 * n - index) < res) {
                    solve(index + 1, distanceMatrix, visited, route);
                }
            }

//            restore data structure
            if (v <= n) load -= 1;
            else load += 1;
            path -= distanceMatrix[route[index - 1]][route[index]];
            visited[v] = false;

            routePath.pop_back();
        }
    }
}

int main() {
//    auto start = high_resolution_clock::now();

    cin >> n >> k;

    int **distanceMatrix = new int *[2 * n + 1];
    bool visited[2 * n + 1];
    memset(visited, false, sizeof(visited));
    int route[2 * n + 1];
    memset(route, 0, sizeof(route));

//    initialize distanceMatrix
    for (int x = 0; x <= 2 * n; ++x) {
        distanceMatrix[x] = new int[2 * n + 1];
        for (int y = 0; y <= 2 * n; ++y) {
            int c;
            cin >> c;
            if (x!=y) Cmin = min(Cmin, c);
            distanceMatrix[x][y] = c;
        }
    }

//    route.resize(2 * n + 1);
//    visited.resize(2 * n + 1);

    solve(1, distanceMatrix, visited, route);
    cout << res << endl;
    printPath();

//    auto stop = high_resolution_clock::now();
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    for (int x = 0; x <= 2 * n; ++x) {
        delete[] distanceMatrix[x];
    }
    delete[] distanceMatrix;
    return 0;
}
