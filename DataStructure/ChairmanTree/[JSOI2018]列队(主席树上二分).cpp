#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6;
const int N = MX + 10;
const int M = N * 20;
int rt[N], ls[M], rs[M], sz[M], tot = 0;
long long sum[M];

int newnode(int p, int x){
    ++tot;
    ls[tot] = ls[p];
    rs[tot] = rs[p];
    sum[tot] = sum[p] + x;
    sz[tot] = sz[p] + 1;
    return tot;
}

void insert(int &o, int p, int l, int r, int x){
    o = newnode(p, x);
    if(l == r) return;
    int mid = (l + r) / 2;
    if(x <= mid) insert(ls[o], ls[p], l, mid, x);
    else insert(rs[o], rs[p], mid+1, r, x);
}

inline long long qsum(int a, int b){
    return (long long) (a + b) * (b - a + 1) / 2;
}

// 编号在给定区间、位置在 [l,r] 的学生都按顺序跑到 [a,b] 去
long long run(int lrt, int rrt, int l, int r, int a, int b){
    int csz = sz[rrt] - sz[lrt];
    if(csz == 0) return 0;
    long long csum = sum[rrt] - sum[lrt];
    if(l >= a) return csum - qsum(a,b);
    if(r <= b) return qsum(a,b) - csum;
    int mid = (l + r) / 2;
    int lsz = sz[ls[rrt]] - sz[ls[lrt]];
    return run(ls[lrt], ls[rrt], l, mid, a, a + lsz - 1) +
           run(rs[lrt], rs[rrt], mid + 1, r, a + lsz, b);
}

int main(){
    int n, m, x, l, r;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &x);
        insert(rt[i], rt[i-1], 1, MX, x);
    }
    while(m--){
        scanf("%d%d%d", &l, &r, &x);
        printf("%lld\n", run(rt[l-1], rt[r], 1, MX, x, x+r-l));
    }
    return 0;
}