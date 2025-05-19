#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = unsigned long long;

template <typename T>
struct MatrixOrAnd {
    vector<vector<T>> a;

    MatrixOrAnd() {}

    MatrixOrAnd(int n) {
        a.resize(n, vector<T>(n, 0));
    }

    static MatrixOrAnd identity(int n) {
        MatrixOrAnd c(n);
        for (int i = 0; i < n; i++)
            c.a[i][i] = numeric_limits<T>::max();
        return c;
    }

    MatrixOrAnd operator * (const MatrixOrAnd &b) const {
        const int N = a.size();
        assert(N == b.a.size());
        MatrixOrAnd c(N);
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++)
                    c.a[i][j] |= a[i][k] & b.a[k][j];
        return c;
    }

    MatrixOrAnd operator ^ (int b) const {
        const int N = a.size();
        MatrixOrAnd c = identity(N);
        MatrixOrAnd aa = *this;
        for(; b; b >>= 1, aa = aa * aa)
            if (b & 1) c = c * aa;
        return c;
    }
};

// 以 [GZOI2017] 河神 为例
int main(){
    int n, k;
    cin >> n >> k;

    vector<ll> a(k), b(k);
    for (int i = 0; i < k; i++) cin >> a[i];
    for (int i = 0; i < k; i++) cin >> b[i];

    MatrixOrAnd<ll> mat(k);
    for(int i = 0; i < k; i++) mat.a[0][i] = b[k - i - 1];
    for(int i = 1; i < k; i++) mat.a[i][i-1] = numeric_limits<ll>::max();

    if (n < k) {
        cout << a[n] << endl;
        return 0;
    }
    mat = mat ^ (n - k + 1);
    ll ans = 0;
    for (int i = 0; i < k; i++)
        ans |= mat.a[0][i] & a[k - i - 1];
    cout << ans << endl;

    return 0;
}