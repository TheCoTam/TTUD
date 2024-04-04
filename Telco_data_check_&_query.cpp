#include <bits/stdc++.h>

using namespace std;


int countTime(string start, string end) {
    int res=0;
    res += (int)(end[0]-start[0]) * 36000;
    res += (int)(end[1]-start[1]) * 3600;
    res += (int)(end[3]-start[3]) * 600;
    res += (int)(end[4]-start[4]) * 60;
    res += (int)(end[6]-start[6]) * 10;
    res += (int)(end[7]-start[7]);

    return res;
}

bool checkNumber(string phoneNumber) {
    if (phoneNumber.length() != 10) return false;
    for(auto &c : phoneNumber) {
        if (c > '9' || c < '0') {
            return false;
        }
    }
    return true;
}

int main() {
    string log, fromNumber, toNumber, date, fromTime, toTime;
    unordered_map<string, pair<int, int>> dataset;
    int totalCall = 0, callTime, incorrectNumber=0;

    while (true) {
        cin >> log;
        if (log == "#") {
            break;
        }
        totalCall += 1;
        cin >> fromNumber >> toNumber >> date >> fromTime >> toTime;

        if (!checkNumber(fromNumber)) incorrectNumber +=1;
        callTime = countTime(fromTime, toTime);

        if (dataset.count(fromNumber) > 0) {
            dataset[fromNumber].first += 1;
            dataset[fromNumber].second += callTime;
        } else {
            dataset[fromNumber] = make_pair(1, callTime);
        }
    }

    while (true) {
        cin >> log;
        if (log == "#") {
            break;
        }
        if (log == "?number_total_calls") {
            cout << totalCall << endl;
        } else if (log == "?number_calls_from") {
            cin >> fromNumber;
            cout << dataset[fromNumber].first << endl;
        } else if (log == "?count_time_calls_from") {
            cin >> fromNumber;
            cout << dataset[fromNumber].second << endl;
        } else {
            if(incorrectNumber != 0) {
                cout << 0 << endl;
            } else {
                cout << 1 << endl;
            }
        }
    }
    return 0;
}
