#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
set<pair<int, int>> edges;
int n, m, fa[N], deg[N], endID[N], aa[N], bb[N];
// endID[x]: 运动员 x 当前所在位置在【比赛结束的时候】站的是哪个运动员
vector<int> groups[N], ans[N];
vector<int> g[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void dfs(int u, int ffa, int iid) {
    ans[iid].push_back(u);
    for (int v : g[u]) {
        if (v == ffa) continue;
        dfs(v, u, iid);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    iota(fa + 1, fa + n + 1, 1);
    iota(endID + 1, endID + n + 1, 1);
    for (int i = 1; i <= m; i++) {
        cin >> aa[i] >> bb[i];
    }
    for (int i = m; i >= 1; i--) {
        int a = aa[i], b = bb[i];
        int endA = endID[a], endB = endID[b];
        if (edges.find({endA, endB}) == edges.end()) {
            int faA = find(endA), faB = find(endB);
            if (faA == faB) {
                cout << "No" << endl;
                return 0;
            }
            fa[faA] = faB;
            deg[endA]++, deg[endB]++;
            g[endA].push_back(endB);
            g[endB].push_back(endA);
            if (deg[endA] > 2 || deg[endB] > 2) {
                cout << "No" << endl;
                return 0;
            }
            edges.insert({endA, endB});
            edges.insert({endB, endA});
        }
        swap(endID[a], endID[b]);
    }

    cout << "Yes" << "\n";
    vector<int> pids;
    for (int i = 1; i <= n; i++) {
        groups[find(i)].push_back(i);
        if (find(i) == i) pids.push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (groups[i].empty()) continue;
        if (groups[i].size() == 1) {
            ans[i].push_back(groups[i][0]);
            continue;
        }
        vector<int> endPoints;
        for (int x : groups[i])
            if (deg[x] == 1) endPoints.push_back(x);
        assert(endPoints.size() == 2);
        dfs(min(endPoints[0], endPoints[1]), 0, i);
    }

    sort(pids.begin(), pids.end(), [](int x, int y) {
        return ans[x][0] < ans[y][0];
    });
    for (int pid : pids)
        for (int x : ans[pid])
            cout << x << "\n";

    return 0;
}