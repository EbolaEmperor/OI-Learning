#include <bits/stdc++.h>
#define ls (o << 1)
#define rs (o << 1 | 1)
using namespace std;

const int N = 100010;
// pre[i]: i 的前一个 =a[i] 的位置
int a[N], ql[N], pre[N], last[N << 1], n, q;
// 对 r 扫描线
// sum[o] (o=[l,l]) : 区间 [l,r] 去重后的子段和
// f[o]   (o=[l,l]) : sum[l] 在扫描过程中对历史最大值
// tag[o]           : 加法标记
// maxtag[o]        : 加法标记的历史最大值
long long sum[N << 2], f[N << 2], tag[N << 2], maxtag[N << 2];
vector<int> qry[N];
long long ans[N];

void doAdd(int o, long long otag, long long omaxtag = 0){
    // sum[o] 是之前某时刻 t 的历史值，omaxtag 是该历史值到现在时刻新增的 tag 最大值
    // 用 sum[o]+omaxtag 可以获取 t 时刻到当前时刻的最大 f 值
    f[o] = max(f[o], sum[o] + omaxtag);
    // tag[o] 是之前某时刻 t 的历史 tag，omaxtag 是该历史值到现在时刻新增的 tag 最大值
    // 用 tag[o]+omaxtag 可以获取 t 时刻到当前时刻的最大 tag 值
    maxtag[o] = max(maxtag[o], tag[o] + omaxtag);
    sum[o] += otag;
    tag[o] += otag;
}

void pushdown(int o){
    doAdd(ls, tag[o], maxtag[o]);
    doAdd(rs, tag[o], maxtag[o]);
    tag[o] = 0;
    maxtag[o] = 0;
}

void pushup(int o){
    sum[o] = max(sum[ls], sum[rs]);
    f[o] = max(f[ls], f[rs]);
}

void add(int o, int l, int r, int nl, int nr, int x){
    if(l >= nl && r <= nr){
        doAdd(o, x, x);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(o);
    if(nl <= mid) add(ls, l, mid, nl, nr, x);
    if(nr > mid) add(rs, mid + 1, r, nl, nr ,x);
    pushup(o);
}

long long fmax(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return f[o];
    int mid = (l + r) / 2;
    long long ans = 0;
    pushdown(o);
    if(nl <= mid) ans = max(ans, fmax(ls, l, mid, nl, nr));
    if(nr > mid) ans = max(ans, fmax(rs, mid + 1, r, nl, nr));
    return ans;
}

void scan(){
    for(int r = 1; r <= n; r++){
        add(1, 1, n, pre[r] + 1, r, a[r]);
        for(int id : qry[r])
            ans[id] = fmax(1, 1, n, ql[id], r);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
        pre[i] = last[a[i] + N];
        last[a[i] + N] = i;
    }
    scanf("%d", &q);
    for(int i = 1; i <= q; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        qry[r].push_back(i);
        ql[i] = l;
    }
    scan();
    for(int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}