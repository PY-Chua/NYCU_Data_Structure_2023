#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> maxAllure(vector<vector<int>>& elements, vector<int>& inquiries) {
    sort(elements.begin(), elements.end());
    int m = elements.size();
    int n = inquiries.size();
    vector<int> result(n, 0);
    
    for (int i = 0; i < n; ++i) {
        int costLimit = inquiries[i];
        int maxAllure = 0, j = 0;
        while (j < m && elements[j][0] <= costLimit) {
            maxAllure = max(maxAllure, elements[j][1]);
            j++;
        }
        result[i] = maxAllure;
    }
    return result;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> elements(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> elements[i][0] >> elements[i][1];
    }

    vector<int> inquiries(n);
    for (int i = 0; i < n; ++i) {
        cin >> inquiries[i];
    }

    vector<int> responses = maxAllure(elements, inquiries);

    for (int i = 0; i < n; ++i) {
        cout << responses[i] << " ";
    }
    cout << endl;

    return 0;
}