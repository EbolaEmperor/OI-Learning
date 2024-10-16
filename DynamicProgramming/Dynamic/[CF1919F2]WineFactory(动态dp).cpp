#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Matrix{
    ll a[2][2];
    ll* operator [] (int i){
        return a[i];
    }
    Matrix operator * (Matrix& b){
        Matrix c;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++){
                c[i][j] = 1e18;
                for(int k = 0; k < 2; k++)
                    c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
            }
        return c;
    }
    ll getmin() const{
        ll ans = 1e18;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                ans = min(ans, a[i][j]);
        return ans;
    }
};

const int N = 500010;
Matrix mat[N << 2];
ll a[N], b[N], c[N];

void setmat(Matrix &p, int i){
    p[0][0] = a[i];
    p[0][1] = a[i] + c[i - 1];
    p[1][0] = p[1][1] = b[i];
}

void build(int o, int l, int r){
    if(l == r){
        setmat(mat[o], l);
        return;
    }
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    mat[o] = mat[o << 1 | 1] * mat[o << 1];
}

void update(int o, int l, int r, int x){
    if(l == r){
        setmat(mat[o], l);
        return;
    }
    int mid = (l + r) / 2;
    if(x <= mid) update(o << 1, l, mid, x);
    else update (o << 1 | 1, mid + 1, r, x);
    mat[o] = mat[o << 1 | 1] * mat[o << 1];
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%lld", a + i);
    for(int i = 1; i <= n; i++) scanf("%lld", b + i);
    for(int i = 1; i < n; i++) scanf("%lld", c + i);
    build(1, 1, n);
    while(q--){
        int p;
        scanf("%d", &p);
        scanf("%lld%lld%lld", a + p, b + p, c + p);
        update(1, 1, n, p);
        update(1, 1, n, p + 1);
        printf("%lld\n", mat[1].getmin());
    }
    return 0;
}