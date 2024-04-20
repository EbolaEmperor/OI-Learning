#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int ch[N][2], pa[N], tot = 0;
int sz[N];
bool revtag[N];
int a[N], n;

struct Object{
    int val, id;
    bool operator < (const Object &rhs) const{
        return val < rhs.val || val == rhs.val && id < rhs.id;
    }
} b[N];

void pushrev(int u){
    if(!revtag[u]) return;
    swap(ch[u][0], ch[u][1]);
    revtag[ch[u][0]] ^= 1;
    revtag[ch[u][1]] ^= 1;
    revtag[u] = 0;
}

inline void maintain(const int &u){
    sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
}

void build(int &u, int l, int r){
    int mid = (l + r) / 2;
    u = a[mid] + 1;
    if(l < mid) build(ch[u][0], l, mid - 1), pa[ch[u][0]] = u;
    if(mid < r) build(ch[u][1], mid + 1, r), pa[ch[u][1]] = u;
    maintain(u);
}

inline int which(const int &u){
    return ch[pa[u]][1] == u;
}

void rotate(int u){
    int p = pa[u], z = pa[p];
    int d = which(u) ^ 1;
    // d=0: 左旋; d=1: 右旋
    int k = which(p);
    pa[u] = z;
    pa[p] = u;
    pa[ch[u][d]] = p;
    if(z) ch[z][k] = u;
    ch[p][d^1] = ch[u][d];
    ch[u][d] = p; 
    maintain(p);
    maintain(u);
}

void splay(int u, int dstpa){
    stack<int> stk;
    for(int p = u; p; p = pa[p]) stk.push(p);
    while(!stk.empty()) pushrev(stk.top()), stk.pop();

    while(pa[u] != dstpa){
        int p = pa[u];
        if(pa[p] != dstpa) rotate(which(u)==which(p) ? p : u);
        rotate(u);
    }
}

int leftmost(int u){
    pushrev(u);
    if(ch[u][0]) return leftmost(ch[u][0]);
    else return u;
}

int main(){
    scanf("%d", &n);
    a[0] = 0; a[n+1] = n+1;
    for(int i = 1; i <= n; i++)
        scanf("%d", &b[i].val), b[i].id = i;
    sort(b + 1, b + 1 + n);
    for(int i = 1; i <= n; i++)
        a[b[i].id] = i;
    int rt;
    build(rt, 0, n + 1);
    for(int i = 2; i <= n + 1; i++){
        splay(i - 1, 0);
        splay(i, i - 1);
        printf("%d ", sz[ch[i][0]] + i - 1);
        int nxt = leftmost(ch[i][1]);
        splay(nxt, i - 1);
        revtag[ch[nxt][0]] ^= 1;
    }
    return 0;
}