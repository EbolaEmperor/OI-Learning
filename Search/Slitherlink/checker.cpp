#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

// 检查是否是单连通区域（所有 * 连成一块）
bool isConnected(const vector<string>& grid, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int, int>> q;

    // 查找第一个 "*" 并进行 BFS
    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                q.push({i, j});
                visited[i][j] = true;
                found = true;
                break;
            }
        }
    }
    if (!found) return false; // 没有任何 *

    // BFS 搜索四联通
    const int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto &dir : directions) {
            int nx = x + dir[0], ny = y + dir[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                !visited[nx][ny] && grid[nx][ny] == '*') {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    // 检查是否所有 "*" 都被访问到
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == '*' && !visited[i][j]) return false;

    return true;
}

// 检查 * 内部是否存在洞（即存在与边界不连通的 # 块）
bool hasNoHoles(const vector<string>& grid, int n, int m) {
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<pair<int,int>> q;
    const int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    int totalSharp = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == '.') ++totalSharp;

    if (totalSharp == 0) return true; // 全是 *，必然无洞

    // 从所有边界上的 # 出发做 BFS
    for (int j = 0; j < m; ++j) {
        if (grid[0][j] == '.' && !vis[0][j]) { vis[0][j] = true; q.push({0,j}); }
        if (grid[n-1][j] == '.' && !vis[n-1][j]) { vis[n-1][j] = true; q.push({n-1,j}); }
    }
    for (int i = 0; i < n; ++i) {
        if (grid[i][0] == '.' && !vis[i][0]) { vis[i][0] = true; q.push({i,0}); }
        if (grid[i][m-1] == '.' && !vis[i][m-1]) { vis[i][m-1] = true; q.push({i,m-1}); }
    }

    int reach = 0;
    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        ++reach;
        for (auto &d : directions) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] == '.' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({nx,ny});
            }
        }
    }

    // 若存在未被边界可达的 #，则存在内洞
    return reach == totalSharp;
}

// 检查每个数字的四个方向上的线段数
bool checkLines(const vector<string>& grid, const vector<string>& result, int n, int m) {
    const int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') continue; // 跳过非数字格
            int expected = grid[i][j] - '0';
            int count = 0;
            for (auto &dir : directions) {
                int nx = i + dir[0], ny = j + dir[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    count += (result[nx][ny] != result[i][j]);
                } else {
                    count += (result[i][j] == '*');
                }
            }
            if (count != expected) {
                cout << "Error at (" << i << ", " << j << "): Expected "
                     << expected << " but got " << count << " lines." << endl;
                return false;
            }
        }
    }
    return true;
}

vector<string> Slitherlink(vector<string> slitherMap);

int main() {
    vector<string> grid;
    string line;
    while (cin >> line) {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();

    // 读取用户提交的答案（由你的求解函数返回）
    auto result = Slitherlink(grid);

    // 0) 检查输出是否合法
    if (result.size() != n) {
        cout << "Error: Wrong size!" << endl;
        return 0;
    }
    for (auto s : result) {
        if (s.size() != m) {
            cout << "Error: Wrong size!" << endl;
            return 0;
        }
        for (auto c : s)
            if (c != '*' && c != '.') {
                cout << "Error: Invalid character in output!" << endl;
                return 0;
            }
        // cerr << s << endl;
    }

    // 1) 检查区域是否单连通
    if (!isConnected(result, n, m)) {
        cout << "Error: Region is not single-connected!" << endl;
        return 0;
    }

    // 2) 检查是否存在内洞
    if (!hasNoHoles(result, n, m)) {
        cout << "Error: Region has holes inside!" << endl;
        return 0;
    }

    // 3) 检查每个数字周围的线段数
    if (!checkLines(grid, result, n, m)) {
        return 0;
    }

    cout << "Correct." << endl;
    return 0;
}
