#include<bits/stdc++.h>

using namespace std;

string P, T;
map<char, int> last;

int main() {
    getline(cin, P);
    getline(cin, T);
    int count = 0;
    int n = T.length();
    int m = P.length();
    for (char i: T) {
        last[i] = -1;
    }
    for (int i = 0; i < P.length(); ++i) {
        last[P[i]] = i;
    }
    int s = 0;
    while (s <= n - m) {
        int i = m - 1;
        while (i >= 0 && T[i + s] == P[i])i--;
        if (i == -1) {
            count++;
            s++;
        } else {
            char curChar = T[s + i];
            int lastOfCurCharInT = last[curChar];
            int k = (i - lastOfCurCharInT > 1) ? i - lastOfCurCharInT : 1;
            s += k;
        }
    }

    cout << count << endl;

    return 0;
}

// computer
// There are so many kinds of computers today including high performance computers, laptop computers. Mobile phones are also computers
