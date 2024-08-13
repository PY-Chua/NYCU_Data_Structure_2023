#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void dfs(int node, const unordered_map<int, vector<int>>& graph, vector<int>& path, vector<vector<int>>& paths) {
    path.emplace_back(node);
    if (graph.find(node) == graph.end()) { // Reached target node
        paths.emplace_back(path);
    } else {
        for (int next : graph.at(node)) {
            dfs(next, graph, path, paths);
        }
    }
    path.pop_back();
}

vector<vector<int>> allPaths(int numNodes, const vector<pair<int, int>>& edges) {
    unordered_map<int, vector<int>> adjacencyList;

    for (const auto& edge : edges) {
        if (edge.second != -1) {
            adjacencyList[edge.first].emplace_back(edge.second);
        }
    }

    vector<vector<int>> paths;
    vector<int> path;

    // Find the source node(s)
    vector<bool> isSource(numNodes, true);
    for (const auto& edge : edges) {
        if (edge.second != -1) {
            isSource[edge.second] = false;
        }
    }

    // Perform DFS from source node(s)
    for (int i = 0; i < numNodes; ++i) {
        if (isSource[i]) {
            dfs(i, adjacencyList, path, paths);
        }
    }

    // Sort paths based on length and lexicographical order
    sort(paths.begin(), paths.end(), [](const vector<int>& a, const vector<int>& b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    });

    return paths;
}

int main() {
    int numNodes;
    cin >> numNodes;

    vector<pair<int, int>> edges;
    int from, to;
    while (cin >> from >> to) {
        edges.emplace_back(from, to);
    }

    vector<vector<int>> result = allPaths(numNodes, edges);

    // Output paths
    for (const auto& path : result) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}