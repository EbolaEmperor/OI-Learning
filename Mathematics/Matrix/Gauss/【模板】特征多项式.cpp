// O(n^3) 算法
// 上 Hessenberg 化 + O(n^2) 求行列式 + Lagrange 插值
#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

const int N = 505;

int Pow(int a,int b)
{
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

struct Matrix
{
    int n, a[N][N];
    Matrix(){memset(a, 0, sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator = (const Matrix &B)
    {
        n = B.n;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                a[i][j] = B.a[i][j];
        return *this;
    }
    
    friend Matrix operator * (Matrix &A,Matrix &B)
    {
        Matrix C; C.n = A.n;
        for(int i = 1; i <= A.n; i++)
            for(int j = 1; j <= A.n; j++)
                for(int k = 1; k <= A.n; k++)
                    C[i][j] = (C[i][j] + 1ll * A[i][k] * B[k][j]) % ha;
        return C;
    }
};

struct Poly
{
    int n, a[N*2];
    Poly(){memset(a, 0, sizeof(a)); n = 0;}
    int& operator [] (const int &x){return a[x];}
    
    friend Poly operator * (Poly A,Poly B)
    {
        Poly C; C.n = A.n + B.n;
        for(int i = 0; i <= A.n; i++)
            for(int j = 0; j <= B.n; j++)
                C[i + j] = (C[i + j] + 1ll * A[i] * B[j]) % ha;
        return C;
    }

    friend Poly operator * (Poly A, int x)
    {
        Poly C = A;
        for(int i = 0; i <= C.n; i++)
            C[i] = 1ll * C[i] * x % ha;
        return C;
    }

    // 求 A / (x-v)
    friend Poly operator / (Poly A, int v)
    {
        Poly C; C.n = A.n - 1;
        for(int i = C.n; i >= 0; i--)
            C[i] = (A[i + 1] + 1ll * v * C[i + 1]) % ha;
        return C;
    }

    friend Poly operator + (Poly A, Poly B)
    {
        Poly C; C.n = max(A.n, B.n);
        for(int i = 0; i <= C.n; i++)
            C[i] = (A[i] + B[i]) % ha;
        return C;
    }
};

void Hessenberg(Matrix &A)
{
    int n = A.n;
    for (int j = 1; j <= n-2; j++) {
        for (int i = j+2; i <= n; i++) {
            if (A[i][j] == 0) continue;
            if (A[j+1][j] == 0) {
                int k = j+2;
                while (k <= n && A[k][j] == 0) k++;
                if (k <= n) {
                    for (int l = 1; l <= n; l++) swap(A[j+1][l], A[k][l]);
                    for (int l = 1; l <= n; l++) swap(A[l][j+1], A[l][k]);
                }
            }
            if (A[j+1][j] == 0) continue;
            int factor = 1LL * A[i][j] * Pow(A[j+1][j], ha-2) % ha;
            // 行操作：第i行减去第j+1行乘以factor
            for (int k = 1; k <= n; k++) {
                A[i][k] = (A[i][k] - 1LL * factor * A[j+1][k] % ha + ha) % ha;
            }
            // 添加一个对称的列操作来保证相似性质
            for (int k = 1; k <= n; k++) {
                A[k][j+1] = (A[k][j+1] + 1LL * factor * A[k][i] % ha) % ha;
            }
        }
    }
}

int DetHessenberg(const Matrix &A)
{
    int n = A.n;
    Matrix B = A;
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (B[i][i] == 0) {
            if (i+1 <= n && B[i+1][i] != 0) {
                for (int j = i; j <= n; j++)
                    swap(B[i][j], B[i+1][j]);
                ans = 1LL * ans * (ha - 1) % ha;
            } else return 0;
        }
        ans = 1LL * ans * B[i][i] % ha;
        if (i+1 <= n && B[i+1][i] != 0) {
            int inv = Pow(B[i][i], ha - 2);
            int t = 1LL * B[i+1][i] * inv % ha;
            for (int j = i; j <= n; j++) {
                B[i+1][j] = (B[i+1][j] - 1LL * B[i][j] * t % ha + ha) % ha;
            }
        }
    }
    ans = 1LL * ans * B[n][n] % ha;
    return ans;
}

int n,k;
Matrix A,B;
int ay[N];

Poly Lagrange(int n)
{
    Poly A;
    A.n = 0; A[0] = 1;
    for(int i = 0; i <= n; i++){
        Poly tmp;
        tmp.n = 1;
        tmp[0] = (ha - i) % ha; tmp[1] = 1;
        A = A * tmp;
    }
    Poly res;
    for(int i = 0; i <= n; i++)
    {
        Poly s1 = A / i;
        int val = ay[i];
        for(int j = 0; j <= n; j++)
            if(i != j) val = 1ll * val * Pow((i - j + ha) % ha, ha - 2) % ha;
        res = res + s1 * val;
    }
    return res;
}

int main()
{
    scanf("%d",&k);A.n=k;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=k;j++)
            scanf("%d",&A[i][j]);
    Hessenberg(A);
    B.n = A.n;
    for(int x = 0; x <= k; x++)
    {
        for(int i = 1; i <= k; i++){
            B[i][i] = (x - A[i][i] + ha) % ha;
            for(int j = 1; j <= k; j++)
                if(i != j) B[i][j] = (ha - A[i][j]) % ha;
        }
        ay[x] = DetHessenberg(B);
    }
    Poly cp = Lagrange(k);
    for(int i=0;i<=cp.n;i++) printf("%d ",cp[i]);
    return 0;
}