// 思路：最优方案是把点按照权值从大到小排序，依次删除这些点的所有连边
// 做法是反过来模拟边的合并，对于边 (u,v)，它的删除时刻是由 max(val[u],val[v]) 决定的，
// 所以反过来模拟合并的时候，要按 max(val[u],val[v]) 从小到大排序
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, fa[N], mxv[N];
struct Edge {
    int u, v;
    bool operator < (const Edge &rhs) const {
        return max(mxv[u],mxv[v]) < max(mxv[rhs.u],mxv[rhs.v]);
    }
} e[N];
long long ans = 0;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    ans += mxv[x] + mxv[y];
    mxv[x] = max(mxv[x], mxv[y]);
    fa[y] = x;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", mxv + i);
        fa[i] = i;
    }
    for(int i = 1, u, v; i < n; i++)
        scanf("%d%d", &e[i].u, &e[i].v);
    sort(e+1, e+n);
    for(int i = 1; i < n; i++)
        merge(e[i].u, e[i].v);
    cout << ans << endl;
    return 0;
}