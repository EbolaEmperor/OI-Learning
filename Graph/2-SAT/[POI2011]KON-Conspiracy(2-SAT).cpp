#include <bits/stdc++.h>
using namespace std;

// 用 Tarjan 算法求解 2-SAT 问题
class TwoSAT {
private:
    int n; // 变量数量
    vector<vector<int>> graph; // 隐含图
    int index; // 当前索引
    int sccCount; // 强连通分量计数
    vector<int> indices; // 节点索引
    vector<int> lowlink; // 节点低链接值
    vector<bool> onStack; // 节点是否在栈中
    stack<int> S; // 辅助栈
    vector<int> sccId; // 每个节点所属的强连通分量ID
    vector<bool> assignment; // 变量赋值结果

    void strongConnect(int v) {
        indices[v] = lowlink[v] = index++;
        S.push(v);
        onStack[v] = true;

        for (int w : graph[v]) {
            if (indices[w] == -1) {
                strongConnect(w);
                lowlink[v] = min(lowlink[v], lowlink[w]);
            } else if (sccId[w] == -1) {
                lowlink[v] = min(lowlink[v], indices[w]);
            }
        }

        if (lowlink[v] == indices[v]) {
            while (true) {
                int w = S.top();
                S.pop();
                onStack[w] = false;
                sccId[w] = sccCount;
                if (w == v) break;
            }
            sccCount++;
        }
    }

public:
    TwoSAT(int n) : n(n), graph(2 * n), index(0), sccCount(0),
                    indices(2 * n, -1), lowlink(2 * n, -1), onStack(2 * n, false),
                    sccId(2 * n, -1), assignment(n, false) {}

    // 添加子句 (i isTrueI) implies (j isTrueJ)
    void addImplication(int i, bool isTrueI, int j, bool isTrueJ) {
        int a = 2 * i + (isTrueI ? 0 : 1);
        int b = 2 * j + (isTrueJ ? 0 : 1);
        graph[a].push_back(b);
    }

    // 求解 2-SAT
    bool solve() {
        for (int v = 0; v < 2 * n; ++v)
            if (indices[v] == -1) strongConnect(v);
        for (int i = 0; i < n; ++i) {
            if (sccId[2 * i] == sccId[2 * i + 1]) {
                return false; // 不可满足
            }
            assignment[i] = sccId[2 * i] < sccId[2 * i + 1];
        }
        return true; // 可满足
    }

    // 获取变量的赋值结果
    vector<bool> getAssignment() const {
        return assignment;
    }

    pair< vector<int>, vector<int> > getPartition() const {
        vector<int> setTrue, setFalse;
        for (int i = 0; i < n; ++i) {
            if (assignment[i]) setTrue.push_back(i);
            else setFalse.push_back(i);
        }
        return {setTrue, setFalse};
    }

private:
    // 验证一组解是否满足所有子句，从给定的解开始用 dfs 推理，如果推理结果与 sol 矛盾则返回 false
    void _dfscheck(int var, bool value, vector<bool> &visited, const vector<bool> &sol) const {
        int node = 2 * var + (value ? 0 : 1);
        if (visited[node]) return;
        visited[node] = true;
        for (int neighbor : graph[node]) {
            int neighborVar = neighbor / 2;
            bool neighborValue = (neighbor % 2 == 0);
            if (sol[neighborVar] != neighborValue) {
                throw false; // 矛盾
            }
            _dfscheck(neighborVar, neighborValue, visited, sol);
        }
    }

public:
    bool checkSolution(const vector<bool> &sol) const {
        vector<bool> visited(2 * n, false);
        try {
            for (int i = 0; i < n; ++i) {
                _dfscheck(i, sol[i], visited, sol);
            }
        } catch (bool) {
            return false;
        }
        return true;
    }
};

const int N = 5010;
bool a[N][N];
int n;

int main() {
    cin >> n;
    for (int i = 0, m; i < n; ++i) {
        cin >> m;
        for (int j = 0, x; j < m; ++j) {
            cin >> x;
            a[i][x - 1] = true;
        }
    }
    // true: 在独立集里，false: 在团里
    TwoSAT solver(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (a[i][j]) solver.addImplication(i, true, j, false);
            else solver.addImplication(i, false, j, true);
        }
    }
    if (solver.solve()) {
        auto [independ, clique] = solver.getPartition();
        vector<int> cnt(n);
        for (int u : independ)
            for (int v : clique)
                if (a[u][v]) cnt[u]++, cnt[v]++;
        int ans = (independ.size() >= 1) && (clique.size() >= 1);
        if (independ.size() > 1) {
            for (int u : independ)
                ans += (cnt[u] == clique.size());
        }
        if (clique.size() > 1) {
            for (int v : clique)
                ans += (cnt[v] == 0);
        }
        if (!independ.empty() && !clique.empty()) {
            for (int u : independ)
                for (int v : clique) {
                    if (a[u][v] && cnt[u] == clique.size() && cnt[v] == 1) ans++;
                    if (!a[u][v] && cnt[u] == clique.size() - 1 && cnt[v] == 0) ans++;
                }
        }
        cout << ans << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}