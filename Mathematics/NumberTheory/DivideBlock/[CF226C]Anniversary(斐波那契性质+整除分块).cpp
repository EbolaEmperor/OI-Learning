#include <iostream>
#include <cstring>
using namespace std;

int mod, l, r, k;

struct Matrix{
    int a[2][2];
    Matrix(){
        memset(a, 0, sizeof(a));
    }
    int* operator [] (int i){return a[i];}
    const int* operator [] (int i) const{return a[i];}
    Matrix operator * (const Matrix &rhs) const{
        Matrix c;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                for(int k = 0; k < 2; k++)
                    c[i][j] = (c[i][j] + (long long)a[i][k] * rhs[j][k]) % mod;
        return c;
    }
    friend Matrix matpow(Matrix a, int n){
        Matrix ans;
        ans[0][0] = ans[1][1] = 1;
        for(; n; n >>= 1, a = a * a)
            if(n & 1) ans = ans * a;
        return ans;
    }
};

int getFib(int n){
    Matrix a;
    a[0][0] = a[0][1] = a[1][0] = 1;
    a = matpow(a, n - 1);
    return a[0][0];
}

int getID(){
    int maxgcd = 1;
    for(int d = 1; d <= r; d++){
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