#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct Juice{
    int yummy, price;
    long long volume;
    bool operator < (const Juice &rhs) const{
        return yummy < rhs.yummy;
    }
} juice[N];
struct Query{
    long long money, volume;
    int id;
} q[N], q1[N], q2[N];
int ans[N];
int n, m;
long long vsum[N << 2], psum[N << 2];
int curpos;

void insert(int o, int l, int r, int price, long long vol){
    vsum[o] += vol;
    psum[o] += vol * price;
    if(l == r) return;
    int mid = (l + r) / 2;
    if(price <= mid) insert(o << 1, l, mid, price, vol);
    else insert(o << 1 | 1, mid + 1, r, price, vol);
}

long long query(int o, int l, int r, long long vol){
    int mid = (l + r) / 2;
    if(l == r) return vol * l;
    if(vsum[o << 1] >= vol) return query(o << 1, l, mid, vol);
    else return psum[o << 1] + query(o << 1 | 1, mid + 1, r, vol - vsum[o << 1]);
}

void solve(int l, int r, int ql, int qr){
    if(l == r){
        for(int i = ql; i <= qr; ++i)
            ans[q[i].id] = juice[l].yummy;
        return;
    }
    int mid = (l + r + 1) / 2;
    while(curpos > mid) --curpos, insert(1, 0, 1e5, juice[curpos].price, juice[curpos].volume);
    while(curpos < mid) insert(1, 0, 1e5, juice[curpos].price, -juice[curpos].volume), ++curpos;
    int cnt1 = 0, cnt2 = 0;
    for(int i = ql; i <= qr; ++i){
        long long minpr = vsum[1] >= q[i].volume ? query(1, 0, 1e5, q[i].volume) : 2e18;
        if(minpr > q[i].money) q1[++cnt1] = q[i];
        else q2[++cnt2] = q[i];
    }
    for(int i = 1; i <= cnt1; ++i) q[ql + i - 1] = q1[i];
    for(int i = 1; i <= cnt2; ++i) q[ql + cnt1 + i - 1] = q2[i];
    if(cnt1) solve(l, mid - 1, ql, ql + cnt1 - 1);
    if(cnt2) solve(mid, r, ql + cnt1, qr);
}

int main(){
    scanf("%d%d", &n, &m);
    juice[0] = (Juice){-1, 0, (long long)1e18};
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%lld", &juice[i].yummy, &juice[i].price, &juice[i].volume);
    sort(juice, juice + 1 + n);
    for(int i = 1; i <= m; ++i){
        scanf("%lld%lld", &q[i].money, &q[i].volume);
        q[i].id = i;
    }
    curpos = n + 1;
    solve(0, n, 1, m);
    for(int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}