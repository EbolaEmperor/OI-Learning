#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

class SegmentTree{
private:
    // val[o] 是区间里最大的 a[k]
    // mx[o] 是区间里 B[k]+a[k] 的最大值，这里 B[k] = max [2j-i<=k] (a[i] + a[j])
    // tag[o] 是对区间里的 B 做 upmax 时用到的 lazy 标记
    int tag[N << 2], mx[N << 2], val[N << 2];

    void down(int o, int v){
        tag[o] = max(tag[o], v);
        mx[o] = max(mx[o], val[o] + tag[o]);
    }

    void pushdown(int o){
        if(!tag[o]) return;
        down(o << 1, tag[o]);
        down(o << 1 | 1, tag[o]);
        tag[o] = 0;
    }

public:
    SegmentTree(){
        memset(tag, 0, sizeof(tag));
        memset(val, 0, sizeof(val));
        memset(mx, -0x3f, sizeof(mx));
    }

    void build(int o, int l, int r, int *a){
        if(l == r){
            val[o] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(o << 1, l, mid, a);
        build(o << 1 | 1, mid + 1, r, a);
        val[o] = max(val[o << 1], val[o << 1 | 1]);
    }

    void upmaxB(int o, int l, int r, int nl, int nr, int x){
        if(l >= nl && r <= nr) return down(o, x);
        int mid = (l + r) / 2;
        pushdown(o);
        if(nl <= mid) upmaxB(o << 1, l, mid, nl, nr, x);
        if(nr > mid) upmaxB(o << 1 | 1, mid + 1, r, nl, nr, x);
        mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
    }

    int qmax(int o, int l, int r, int nl, int nr){
        if(l >= nl && r <= nr) return mx[o];
        int mid = (l + r) / 2, ans = 0;
        pushdown(o);
        if(nl <= mid) ans = max(ans, qmax(o << 1, l, mid, nl, nr));
        if(nr > mid) ans = max(ans, qmax(o << 1 | 1, mid + 1, r, nl, nr));
        return ans;
    }
} sgt;

int n, q, a[N], ans[N], qr[N];
vector<pair<int,int>> hangij[N];
vector<int> hangq[N];

// 用单调栈找到所有可能成为最优的 (i,j) 对
// 也就是：j 是 i 后面第一个 >= a[i] 的
//    或：i 是 j 前面最后一个 > a[j] 的
void findij(){
    stack<int> stk;
    for(int i = n; i >= 1; i--){
        while(!stk.empty() && a[stk.top()] < a[i]) stk.pop();
        int j = stk.empty() ? 0 : stk.top();
        if(j) hangij[i].emplace_back(2 * j - i, a[i] + a[j]);
        stk.push(i);
    }
    while(!stk.empty()) stk.pop();
    for(int j = 1; j <= n; j++){
        while(!stk.empty() && a[stk.top()] <= a[j]) stk.pop();
        int i = stk.empty() ? 0 : stk.top();
        if(i) hangij[i].emplace_back(2 * j - i, a[i] + a[j]);
        stk.push(j);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    findij();

    scanf("%d", &q);
    for(int i = 1; i <= q; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        hangq[l].push_back(i);
        qr[i] = r;
    }

    sgt.build(1, 1, n, a);
    for(int l = n; l >= 1; l--){
        for(auto [k, v] : hangij[l])
            if(k <= n) sgt.upmaxB(1, 1, n, k, n, v);
        for(int j : hangq[l])
            ans[j] = sgt.qmax(1, 1, n, l, qr[j]);
    }

    for(int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}