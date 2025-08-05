#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> xpool;
struct Line {
    int xl, xr, y, v;
    // v=1 表示下边界，-1 表示上边界
} lne[N*2];

bool cmp(const Line &a, const Line &b) {
    return a.y < b.y;
}

// cnt 表示的是区间整个被覆盖的次数
int cnt[N<<2], coverd[N<<2], len[N<<2];

void pushup(int o, int l, int r) {
    if(l == r) {
        coverd[o] = (cnt[o] != 0) * len[o];
    } else {
        coverd[o] = cnt[o] ? len[o] : (coverd[o<<1] + coverd[o<<1|1]);
    }
}

void build(int o, int l, int r) {
    if(l == r) {
        len[o] = xpool[l] - xpool[l-1];
        return;
    }
    int mid = (l + r) / 2;
    build(o<<1, l, mid);
    build(o<<1|1, mid+1, r);
    len[o] = len[o<<1] + len[o<<1|1];
}

void modify(int o, int l, int r, int nl, int nr, int v) {
    if (l >= nl && r <= nr) {
        cnt[o] += v;
        pushup(o, l, r);
        return;
    }
    int mid = (l + r) / 2;
    if(nl <= mid) modify(o<<1, l, mid, nl, nr, v);
    if(nr > mid) modify(o<<1|1, mid+1, r, nl, nr, v);
    pushup(o, l, r);
}

int main() {
    int n, xl, xr, yl, yr;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
        lne[2*i-1] = {xl, xr, yl, 1};
        lne[2*i] = {xl, xr, yr, -1};
        xpool.push_back(xl);
        xpool.push_back(xr);
    }
    sort(xpool.begin(), xpool.end());
    xpool.erase(unique(xpool.begin(), xpool.end()), xpool.end());

    sort(lne+1, lne+1+2*n, cmp);
    build(1, 1, xpool.size()-1);
    int cur = -1;
    long long ans = 0;
    for(int i = 1; i <= 2*n; i++) {
        if(i > 1) {
            ans += 1ll * coverd[1] * (lne[i].y - cur);
        }
        xl = lower_bound(xpool.begin(), xpool.end(), lne[i].xl) - xpool.begin();
        xr = lower_bound(xpool.begin(), xpool.end(), lne[i].xr) - xpool.begin();
        modify(1, 1, xpool.size()-1, xl+1, xr, lne[i].v);
        cur = lne[i].y;
    }
    cout << ans << endl;
    return 0;
}