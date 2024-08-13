#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxPoints(vector<int>& benefit1, vector<int>& benefit2, int m) {
    int n = benefit1.size();
    int totalPoints = 0;

    vector<pair<int, int>> diff(n);
    for (int i = 0; i < n; ++i) {
        diff[i] = {benefit1[i] - benefit2[i], i};
    }
    sort(diff.rbegin(), diff.rend());

    for (int i = 0; i < m; ++i) {
        totalPoints += benefit1[diff[i].second];
    }

    for (int i = m; i < n; ++i) {
        totalPoints += benefit2[diff[i].second];
    }
    return totalPoints;
}

int main() {
    int n, m;
    cin >> n;

    vector<int> benefit1(n);
    vector<int> benefit2(n);

    for (int i = 0; i < n; ++i) {
        cin >> benefit1[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> benefit2[i];
    }

    cin >> m;

    int maxPointsRabbits = maxPoints(benefit1, benefit2, m);
    cout << maxPointsRabbits << endl;

    return 0;
}