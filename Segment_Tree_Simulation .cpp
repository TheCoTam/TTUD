#include <bits/stdc++.h>

using namespace std;

struct Node {
    int id, maxVal, l, r;
    Node *left;
    Node *right;
};

void insertNode(Node *&node, int id, int left, int right) {
    node = new Node;
    node->id = id;
//    node->maxVal = -1;
    node->l = left;
    node->r = right;
    node->left = nullptr;
    node->right = nullptr;
}

inline Node *make_tree(int id, int left, int right, const int *sequence, int *maxVal) {
    Node *Node = nullptr;
    insertNode(Node, id, left, right);
    if (left == right) {
        Node->maxVal = sequence[left - 1];
        maxVal[id - 1] = sequence[left - 1];
//        cout << id << " " << maxVal[id-1] << endl;
        return Node;
    }
    int m = (left + right) / 2;
    Node->left = make_tree(2 * id, left, m, sequence, maxVal);
    Node->right = make_tree(2 * id + 1, m + 1, right, sequence, maxVal);
//    Node->maxVal = max(Node->left->maxVal, Node->right->maxVal);
    maxVal[id - 1] = max(maxVal[Node->left->id - 1], maxVal[Node->right->id - 1]);
//    cout << "left child: " << Node->left->id << " " << maxVal[Node->left->id - 1] << endl;
//    cout << "right child: " << Node->right->id << " " << maxVal[Node->right->id - 1] << endl;
//    cout << id << " " << maxVal[id-1] << endl;
    return Node;
}

void printTree(Node *node) {
    if (node == nullptr) {
        return;
    }

    // In ra thông tin của nút hiện tại
    cout << "[" << node->id << ", " << node->l << ", " << node->r << ", " << node->maxVal << "]" << endl;

    // Gọi đệ quy để in ra thông tin của các nút con
    printTree(node->left);
    printTree(node->right);
}

inline int findMaxVal(int id, Node *node) {
    stack<bool> s;
    if (id == 1) {
        return node->maxVal;
    }
    while (id != 1) {
        if (id % 2 != 0) s.push(true);
        else s.push(false);
        id = id / 2;
    }

    Node *targetNode = node;
    while (!s.empty()) {
        if (s.top()) targetNode = targetNode->right;
        else targetNode = targetNode->left;
        s.pop();
    }
    return targetNode->maxVal;
}

inline int getMaxFromSequence(int id, int left, int right, int i, int j, Node *node, int *maxVal) {
    if (i > right || j < left) return -1;
//    if (i <= left and j >= right) return findMaxVal(id, node);
    if (i <= left and j >= right) return maxVal[id - 1];
    int m = (left + right) / 2;
    int leftId = 2 * id, rightId = 2 * id + 1;
    int maxLeft = getMaxFromSequence(leftId, left, m, i, j, node, maxVal);
//    int maxLeft2 = maxVal[leftId-1];
//    cout << "leftChild: " << maxLeft << " " << maxLeft2 << endl;
    int maxRight = getMaxFromSequence(rightId, m + 1, right, i, j, node, maxVal);
//    int maxRight2 = maxVal[rightId-1];
//    cout << "right child: " << maxRight << " " << maxRight2 << endl;
    return max(maxLeft, maxRight);
}

inline void update(int id, int left, int right, int index, int value, int *maxVal) {
    if (left > right) return;
    if (index < left || index > right) return;
    if (left == right) {
        maxVal[id - 1] = value;
        return;
    }
    int leftChild = 2 * id, rightChild = 2 * id + 1;
    int m = (left + right) / 2;
    update(leftChild, left, m, index, value, maxVal);
    update(rightChild, m+1, right, index, value, maxVal);
    maxVal[id-1] = max(maxVal[leftChild-1], maxVal[rightChild-1]);
//    cout << "update done!!!" << endl;
}

int main() {
    int N, m;
    cin >> N;
    int sequence[N];
    for (int i = 0; i < N; i++) {
        int in;
        cin >> in;
        sequence[i] = in;
    }

    int maxVal[4 * N];
    fill(maxVal, maxVal + 4 * N, -1);
    Node *Node = make_tree(1, 1, N, sequence, maxVal);

//    cout << "Done initial tree!!!" << endl;
//    printTree(Node);
//    for (int i = 0; i < 4*N; i++) {
//        std::cout << maxVal[i] << " ";
//    }
//    cout << findMaxVal(11, Node) <<endl;
    cin >> m;
    for (int a = 0; a < m; a++) {
        string cmd;
        cin >> cmd;
        int i, j;
        cin >> i >> j;
        if (cmd == "get-max") {
            cout << getMaxFromSequence(1, 1, N, i, j, Node, maxVal) << endl;
        } else {
            update(1, 1, N, i, j, maxVal);
        }
    }
    return 0;
}