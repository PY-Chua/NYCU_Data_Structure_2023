#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>

using namespace std;

// Define maze constants
const char ROAD = '.';
const char OBSTACLE = '#';
const char START = 'S';
const char END = 'E';

// Define directions for traversal
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Point {
    int x, y, dist;

    // Default constructor
    Point() : x(0), y(0), dist(0) {}

    // Parameterized constructor
    Point(int x, int y, int dist) : x(x), y(y), dist(dist) {}

    // Custom equality operator for Point struct
    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y && dist == other.dist;
    }
};

// Global variables
int n;
Point start(0, 0, 0);
pair<int, int> target;
vector<vector<char>> maze;
vector<vector<bool>> visited;
multimap<int, Point> path;

// Function to check if a point is within the maze
inline bool isValid(int x, int y, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n);
};

inline bool checkEND(Point current){
    vector<Point> result;
    result.push_back(current);

    if(current == start) {
        std::cout << "Shortest Path: Start";
        std::cout << " -> (" << current.x << ", " << current.y << ")";
        std::cout << " -> End" << std::endl;
        return true;
    }

    else {
        while (!path.empty()) {
            int nextDist = current.dist - 1;                   
            auto itr1 = path.lower_bound(nextDist);
            auto itr2 = path.upper_bound(nextDist);
            while (itr1 != itr2) {
                bool found = false;
                for (int i = 0; i < 4; i++) {
                    int newX = current.x + dx[i];
                    int newY = current.y + dy[i];

                    if (itr1 -> second.x == newX && itr1 -> second.y == newY) {
                        current = Point(newX, newY, nextDist);
                        result.push_back(current);
                        path.erase(path.find(nextDist));
                        found = true;
                    }
                    if (found) break;
                }
                if (found) break;
                else itr1++;
            }
            if (current.x == start.x && current.y == start.y){
                path.clear();
                break;
            } 
        }
    }
    std::reverse(result.begin(), result.end());               
    std::cout << "Shortest Path: Start";
    for (const Point& cell : result) {
        std::cout << " -> (" << cell.x << ", " << cell.y << ")";
    }
    std::cout << " -> End" << std::endl;
    return true;
};

// Function to perform IDDFS and find the shortest path
inline bool iddfs() {
    int maxDepth = n * n;
    stack<Point> s;
    stack<Point> previous_element;
    visited.assign(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = (maze[i][j] == OBSTACLE);
        }
    }

    s.push(start);
    path.insert(make_pair(start.dist, start));
    visited[start.x][start.y] = true;

    for (int depth = 0; depth <= maxDepth; depth++) {
        
        while (!previous_element.empty()) {
            s.push(previous_element.top());
            path.insert(make_pair(s.top().dist, s.top()));
            previous_element.pop();
        }

        while (!s.empty()) {                
            Point current = s.top();
            s.pop();
        
            if (current.x == target.first && current.y == target.second) return checkEND(current);
            
            if (current.dist <= depth) {
                for (int i = 0; i < 4; i++) {
                    int newX = current.x + dx[i];
                    int newY = current.y + dy[i];

                    if (isValid(newX, newY, n) && !visited[newX][newY]) {
                        s.push(Point(newX, newY, current.dist + 1));
                        visited[newX][newY] = true;
                        previous_element.push(s.top());
                    }
                }
            }
            else {
                continue;
            }
        }
    }
    return false;
};

int main() {
    int startRow, startCol;
    std::cin >> startRow >> startCol;
    std::cin >> target.first >> target.second;
    std::cin >> n;

    maze.assign(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> maze[i][j];
        }
    }

    start = Point(startRow, startCol, 0);

    if (!iddfs()) {
        std::cout << "No path found!" << std::endl;
    }

    return 0;
}