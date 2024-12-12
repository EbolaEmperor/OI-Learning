#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int inf = 0x3f3f3f3f;
int a[N], b[N], h[N], ql[N], qr[N], ans[N], n, q;
int maxf[N << 2], maxg[N << 2], lazy[N << 2];
enum Type{UpF, unUpF, UpG, Query};
struct Node{int type, id;};
vector<Node> hang[N];

void down(int o, int val){
  lazy[o] = max(lazy[o], val);
  maxg[o] = max(maxg[o], maxf[o] + lazy[o]);
}

void pushdown(int o){
  if(lazy[o] == -inf) return;
  down(o << 1, lazy[o]);
  down(o << 1 | 1, lazy[o]);
  lazy[o] = -inf;
}

void update_f(int o, int l, int r, int i, int val){
  if(l == r){
    lazy[o] = -inf;
    maxf[o] = val;
    return;
  }
  int mid = (l + r) / 2;
  pushdown(o);
  if(i <= mid) update_f(o << 1, l, mid, i, val);
  else update_f(o << 1 | 1, mid + 1, r, i, val);
  maxf[o] = max(maxf[o << 1], maxf[o << 1 | 1]);
  maxg[o] = max(maxg[o << 1], maxg[o << 1 | 1]);
}

void update_g(int o, int l, int r, int nl, int nr, int val){
  if(l >= nl && r <= nr){
    down(o, val);
    return;
  }
  int mid = (l + r) / 2;
  pushdown(o);
  if(nl <= mid) update_g(o << 1, l, mid, nl, nr, val);
  if(nr > mid) update_g(o << 1 | 1, mid + 1, r, nl, nr, val);
  maxg[o] = max(maxg[o << 1], maxg[o << 1 | 1]);
}

int qmax_g(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return maxg[o];
    int mid = (l + r) / 2, ans = -inf;
    pushdown(o);
    if(nl <= mid) ans = max(ans, qmax_g(o << 1, l, mid, nl, nr));
    if(nr > mid) ans = max(ans, qmax_g(o << 1 | 1, mid + 1, r, nl, nr));
    return ans;
}

void scan(){
    memset(maxf, -0x3f, sizeof(maxf));
    memset(maxg, -0x3f, sizeof(maxg));
    memset(lazy, -0x3f, sizeof(lazy));
    for(int j = 1; j <= n; j++){
        for(auto e : hang[j]){
            if(e.type == UpF)
                update_f(1, 1, n, e.id, -h[e.id]);
            else if(e.type == unUpF)
                update_f(1, 1, n, e.id, -inf);
            else if(e.type == UpG && j - a[j] >= 1)
                update_g(1, 1, n, max(j - b[j], 1), j - a[j], h[j]);
            else if(e.type == Query)
                ans[e.id] = max(ans[e.id], qmax_g(1, 1, n, ql[e.id], qr[e.id]));
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d%d%d", h + i, a + i, b + i);
        if(i + a[i] <= n)
            hang[i + a[i]].push_back((Node){UpF, i});
        if(i + b[i] < n)
            hang[i + b[i] + 1].push_back((Node){unUpF, i});
    }
    for(int i = 1; i <= n; i++)
        hang[i].push_back((Node){UpG, i});
    scanf("%d", &q);
    for(int i = 1; i <= q; i++){
        scanf("%d%d", ql + i, qr + i);
        hang[qr[i]].push_back((Node){Query, i});
    }
    memset(ans, -0x3f, sizeof(ans));
    scan();
    for(int i = 1; i <= n; i++) h[i] = -h[i];
    scan();
    for(int i = 1; i <= q; i++)
        printf("%d\n", ans[i] >= 0 ? ans[i] : -1);
    return 0;
}