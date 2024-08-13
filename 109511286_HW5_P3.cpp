#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxConsecutiveGardens(int initial, int final, vector<int>& reserved) {
    sort(reserved.begin(), reserved.end());
    int maxCount = 0;
    int prev = initial - 1; 
    for (int i = 0; i < reserved.size(); ++i) {
        int gap = reserved[i] - prev - 1;
        maxCount = max(maxCount, gap);
        prev = reserved[i];
    }

    int lastGap = final - prev;
    maxCount = max(maxCount, lastGap);

    return maxCount;
}

int main() {
    int initial, final, n;
    cin >> initial >> final >> n;

    vector<int> reserved(n);
    for (int i = 0; i < n; ++i) {
        cin >> reserved[i];
    }

    int maxCount = maxConsecutiveGardens(initial, final, reserved);
    cout << maxCount << endl;

    return 0;
}