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
    for(long long gcd = 1; gcd <= r; gcd++){
        // 尝试完 gcd=33，直接尝试 gcd=50
        // r = 100, gcd = 34
        // r / (r / gcd) = r / (2) = 50
        // 在 r/gcd 不变的情况下，gcd 最大能是多少
        gcd = min(r / (r / gcd), r);
        if(r / gcd - (l - 1) / gcd >= k) maxgcd = gcd;
        // 上一步到了这里，gcd = 33
        // 接下来 gcd++ 变成 34，然后进入下一次循环
    }
    return maxgcd;
}

int main(){
    cin >> mod >> l >> r >> k;
    cout << getFib(getID()) << endl;
    return 0;
}