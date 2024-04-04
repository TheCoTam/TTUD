#include <bits/stdc++.h>

using namespace std;

void print_queue(queue<pair<int, int>> qe) {
    while (!qe.empty()) {
        pair<int, int> item = qe.front();
        qe.pop();
        cout << "(" << item.first << ", " << item.second << ") ";
    }
    cout << endl;
}

//print algorithm's path graph
void printD(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n, m, r, c, val, row, col;
    cin >> n >> m >> r >> c;
    queue<pair<int, int>> qe;
    vector<vector<int>> maze(n, vector<int>(m)), d(n, vector<int>(m));

//    4 directions in x and y axis
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

//    initialize the maze
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> val;
//            maze[i].push_back(val);
            maze[i][j] = val;
//            cout << maze[i][j];
        }
    cout << "take maze: done!" << endl;

    if (maze[r-1][c-1] == 1) {
        cout << -1 << endl;
        return 0;
    }
    d[r-1][c-1] = 0;
    maze[r-1][c-1] = 1;
    qe.push(make_pair(r-1, c-1));
    while (!qe.empty()) {
        row = qe.front().first;
        col = qe.front().second;
        qe.pop();
//        Check 4 directions of the current position
        for (int i = 0; i < 4; i++) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

//            Only consider next position that is not wall
            if (maze[newRow][newCol] != 1) {
                d[newRow][newCol] = d[row][col] + 1;

//                consider if next position is the escape way
                if (newRow == 0 || newRow == n - 1 || newCol == 0 || newCol == m - 1) {
                    cout << d[newRow][newCol] << endl;
                    printD(d);
                    return 0;
                }
//                when the next position is not the escape way, push it in the queue
                qe.push(make_pair(newRow, newCol));
                maze[newRow][newCol] = 1;
            }
        }
        print_queue(qe);
    }
    return 0;
}
