#include <iostream>
#include <cstring>
using namespace std;

long long mod, l, r, k;

struct Matrix{
    long long a[2][2];
    Matrix(){
        memset(a, 0, sizeof(a));
    }
    long long* operator [] (int i){return a[i];}
    const long long* operator [] (int i) const{return a[i];}
    Matrix operator * (const Matrix &rhs) const{
        Matrix c;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                for(int k = 0; k < 2; k++)
                    c[i][j] = (c[i][j] + a[i][k] * rhs[j][k]) % mod;
        return c;
    }
    friend Matrix matpow(Matrix a, long long n){
        Matrix ans;
        ans[0][0] = ans[1][1] = 1;
        for(; n; n >>= 1, a = a * a)
            if(n & 1) ans = ans * a;
        return ans;
    }
};

long long getFib(long long n){
    Matrix a;
    a[0][0] = a[0][1] = a[1][0] = 1;
    a = matpow(a, n - 1);
    return a[0][0] % mod;
}

long long getID(){
    long long maxgcd = 1;
    for(long long d = 1; d <= r; d++){
        d = min(r / (r / d), r);
        if(r / d - (l - 1) / d >= k) maxgcd = d;
    }
    return maxgcd;
}

int main(){
    cin >> mod >> l >> r >> k;
    cout << getFib(getID()) << endl;
    return 0;
}