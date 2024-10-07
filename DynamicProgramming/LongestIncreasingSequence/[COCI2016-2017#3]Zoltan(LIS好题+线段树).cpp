#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;

const int ha = 1e9 + 7;
inline void add(int &x, const int &y){
    x = (x + y >= ha) ? (x + y - ha) : x + y;
}

// 用于维护最大 dp 值，以及相应的 cnt 值之和
//    dp : 从某位置开始的 LIS/LDS 长度
//   cnt : 从某位置开始的 LIS/LDS 有几个
struct Node{
    int dp, cnt;
    Node(int dp = 0, int cnt = 0)
        : dp(dp), cnt(cnt) {}
    void upmax(const Node &rhs){
        if(rhs.dp > dp) *this = rhs;
        else if(rhs.dp == dp) add(cnt, rhs.cnt);
    }
    Node operator + (int a) const{
        return Node(dp + a, cnt);
    }
};

const int N = 2e5 + 5;
int n, m, h[N], val[N], pw2[N];
Node dpLIS[N], dpLDS[N];

struct Segment{
    Node tr[N << 2];
    Node query(int o, int l, int r, int nl, int nr){
        if(nl > nr) return Node();
        if(l >= nl && r <= nr) return tr[o];
        int mid = (l + r) / 2; Node ans;
        if(nl <= mid) ans.upmax(query(o << 1, l, mid, nl, nr));
        if(nr > mid) ans.upmax(query(o << 1 | 1, mid + 1, r, nl, nr));
        return ans;
    }
    void update(int o, int l, int r, int v, Node x){
        if(l == r) {tr[o].upmax(x); return;}
        int mid = (l + r) / 2;
        if(v <= mid) update(o << 1, l, mid, v, x);
        else update(o << 1 | 1, mid + 1, r, v, x);
        (tr[o] = tr[o << 1]).upmax(tr[o << 1 | 1]);
    }
} trLIS, trLDS;

void readInit(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", h + i), val[i] = h[i];
    sort(val + 1, val + 1 + n);
    m = unique(val + 1, val + 1 + n) - (val + 1);
    for(int i = 1; i <= n; i++)
        h[i] = lower_bound(val + 1, val + 1 + m, h[i]) - val;
    pw2[0] = 1;
    for(int i = 1; i <= n; i++)
        pw2[i] = (pw2[i - 1] << 1) % ha;
}

int main(){
    readInit();
    int ans1 = 0, ans2 = 0;
    for(int i = n; i >= 1; i--){
        dpLIS[i].dp = dpLIS[i].cnt = 1;
        dpLDS[i].dp = dpLDS[i].cnt = 1;
        dpLIS[i].upmax(trLIS.query(1, 1, m, h[i] + 1, m) + 1);
        dpLDS[i].upmax(trLDS.query(1, 1, m, 1, h[i] - 1) + 1);
        trLIS.update(1, 1, m, h[i], dpLIS[i]);
        trLDS.update(1, 1, m, h[i], dpLDS[i]);
        ans1 = max(ans1, dpLIS[i].dp + dpLDS[i].dp - 1);
    }
    for(int i = 1; i <= n; i++)
        if(dpLIS[i].dp + dpLDS[i].dp - 1 == ans1)
            ans2 = (ans2 + (long long) dpLIS[i].cnt * dpLDS[i].cnt) % ha;
    ans2 = (long long) ans2 * pw2[n - ans1] % ha;
    printf("%d %d\n", ans1, ans2);
    return 0;
}