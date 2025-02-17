#include <bits/stdc++.h>
#define ls (o << 1)
#define rs (o << 1 | 1)
#define ll long long
using namespace std;

const ll inf = 1e18;
struct Matrix{
    long long a[2][2];
    void clear(){
        a[0][0] = a[1][1] = 0;
        a[0][1] = a[1][0] = -inf;
    }
    Matrix operator * (const Matrix &rhs) const{
        Matrix c;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++){
                c.a[i][j] = -inf;
                for(int k = 0; k < 2; k++)
                    c.a[i][j] = max(c.a[i][j], a[i][k] + rhs.a[k][j]);
            }
        return c;
    }
    pair<ll, ll> operator * (const pair<ll, ll> &rhs) const{
        pair<ll, ll> res;
        res.first = max(a[0][0] + rhs.first, a[0][1] + rhs.second);
        res.second = max(a[1][0] + rhs.first, a[1][1] + rhs.second);
        return res;
    }
};

const int N = 100010;
int a[N], ql[N], pre[N], last[N << 1], n, q;
Matrix tag[N << 2];
pair<ll, ll> f[N << 2];
vector<int> qry[N];
long long ans[N];

Matrix maketag(int v){
    Matrix t;
    t.a[0][0] = t.a[1][0] = v;
    t.a[0][1] = -inf;
    t.a[1][1] = 0;
    return t;
}

void pushdown(int o){
    f[o << 1] = tag[o] * f[o << 1];
    tag[o << 1] = tag[o] * tag[o << 1];
    f[o << 1 | 1] = tag[o] * f[o << 1 | 1];
    tag[o << 1 | 1] = tag[o] * tag[o << 1 | 1];
    tag[o].clear();
}

void pushup(int o){
    f[o].first = max(f[o << 1].first, f[o << 1 | 1].first);
    f[o].second = max(f[o << 1].second, f[o << 1 | 1].second);
}

void add(int o, int l, int r, int nl, int nr, int x){
    if(l >= nl && r <= nr){
        auto t = maketag(x);
        f[o] = t * f[o];
        tag[o] = t * tag[o];
        return;
    }
    int mid = (l + r) / 2;
    pushdown(o);
    if(nl <= mid) add(ls, l, mid, nl, nr, x);
    if(nr > mid) add(rs, mid + 1, r, nl, nr ,x);
    pushup(o);
}

long long fmax(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return f[o].second;
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