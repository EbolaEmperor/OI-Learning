#include <iostream>
using namespace std;

typedef long long LL;
const LL inf = 1e16;
const int N = 2e5 + 5;

struct Matrix{
    LL a[2][2];
    LL* operator [] (int i){return a[i];}
    const LL* operator [] (int i) const{return a[i];}
    Matrix operator * (const Matrix &rhs) const{
        Matrix ans;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++){
                ans[i][j] = -inf;
                for(int k = 0; k < 2; k++)
                    ans[i][j] = max(ans[i][j], a[i][k] + rhs[k][j]);
            }
        return ans;
    }
    LL getmax() const{
        LL ans = -inf;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                ans = max(ans, a[i][j]);
        return ans;
    }
};

Matrix tr[N << 2];
int a[N], d[N], n, q;

Matrix getmat(int i){
    Matrix mat;
    mat[0][0] = (d[i] >= 0) ? d[i] : 0;
    mat[1][1] = (d[i] <= 0) ? -d[i] : 0;
    mat[0][1] = mat[1][0] = 0;
    return mat;
}

void update(int o, int l, int r, int k){
    if(l == r){
        tr[o] = getmat(l);
        return;
    }
    int mid = (l + r) / 2;
    if(k <= mid) update(o << 1, l, mid, k);
    else update(o << 1 | 1, mid + 1, r, k);
    tr[o] = tr[o << 1] * tr[o << 1 | 1];
}

void build(int o, int l, int r){
    if(l == r){
        tr[o] = getmat(l);
        return;
    }
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    tr[o] = tr[o << 1] * tr[o << 1 | 1];
}

int main(){
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(i > 1) d[i] = a[i] - a[i - 1];
    }
    if(n > 1) build(1, 2, n);
    while(q--){
        if(n == 1){
            cout << 0 << endl;
            continue;
        }
        int l, r, x;
        cin >> l >> r >> x;
        d[l] += x;
        d[r + 1] -= x;
        if(l >= 2) update(1, 2, n, l);
        if(r + 1 <= n) update(1, 2, n, r + 1);
        cout << tr[1].getmax() << endl;
    }
    return 0;
}