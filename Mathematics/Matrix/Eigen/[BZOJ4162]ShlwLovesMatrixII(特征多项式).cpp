#include<iostream>
#include<cstdio>
#include<cstring>
#define ha 1000000007
using namespace std;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

struct Matrix
{
    int n,a[55][55];
    Matrix(){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix& operator = (const Matrix &B)
    {
        n=B.n;
        memcpy(a,B.a,sizeof(a));
        return *this;
    }
    
    friend Matrix operator * (Matrix &A,Matrix &B)
    {
        Matrix C;C.n=A.n;
        for(int i=1;i<=A.n;i++)
            for(int j=1;j<=A.n;j++)
                for(int k=1;k<=A.n;k++)
                    C[i][j]=(C[i][j]+1ll*A[i][k]*B[k][j])%ha;
        return C;
    }
};

struct Poly
{
    int n,a[155];
    Poly(){memset(a,0,sizeof(a));n=0;}
    int& operator [] (const int &x){return a[x];}
    
    friend Poly operator * (Poly A,Poly B)
    {
        Poly C;C.n=A.n+B.n;
        for(int i=0;i<=A.n;i++)
            for(int j=0;j<=B.n;j++)
                C[i+j]=(C[i+j]+1ll*A[i]*B[j])%ha;
        return C;
    }
    
    friend Poly operator * (Poly A,int x)
    {
        Poly C=A;
        for(int i=0;i<=C.n;i++)
            C[i]=1ll*C[i]*x%ha;
        return C;
    }
    
    friend Poly operator + (Poly A,Poly B)
    {
        Poly C;C.n=max(A.n,B.n);
        for(int i=0;i<=C.n;i++)
            C[i]=(A[i]+B[i])%ha;
        return C;
    }
    
    friend Poly operator % (Poly A,Poly B)
    {
        for(int i=A.n-B.n;i>=0;i--)
        {
            int k=1ll*A[i+B.n]*Pow(B[B.n],ha-2)%ha;
            for(int j=0;j<=B.n;j++)
                A[i+j]=(A[i+j]-1ll*B[j]*k%ha+ha)%ha;
        }
        A.n=B.n-1;
        return A;
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

char s[10010];
int n,k;
Matrix A,A0,B,ans;
int ay[55];

Poly Lagrange(int n)
{
    Poly res;
    for(int i=0;i<=n;i++)
    {
        Poly s1;
        s1[0]=1;
        for(int j=0;j<=n;j++)
        {
            if(i==j) continue;
            Poly tmp;tmp.n=1;
            tmp[0]=(ha-j)%ha;tmp[1]=1;
            s1=s1*tmp*Pow((i-j+ha)%ha,ha-2);
        }
        res=res+s1*ay[i];
    }
    return res;
}

int main()
{
    scanf("%s%d",s,&k);A.n=k;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=k;j++)
            scanf("%d",&A[i][j]);
    A0 = A;
    Hessenberg(A0);
    B.n = A0.n;
    for(int x = 0; x <= k; x++)
    {
        for(int i = 1; i <= k; i++){
            B[i][i] = (x - A0[i][i] + ha) % ha;
            for(int j = 1; j <= k; j++)
                if(i != j) B[i][j] = (ha - A0[i][j]) % ha;
        }
        ay[x] = DetHessenberg(B);
    }
    Poly cp=Lagrange(k),falun,dafa;
    falun.n=1;falun[1]=1;dafa[0]=1;
    for(int i=strlen(s)-1;i>=0;i--,falun=falun*falun%cp)
        if(s[i]=='1') dafa=dafa*falun%cp;
    memset(B.a,0,sizeof(B.a));
    for(int i=1;i<=k;i++) B[i][i]=1;
    for(int t=0;t<k;t++,B=A*B)
        for(int i=1;i<=k;i++)
            for(int j=1;j<=k;j++)
                ans[i][j]=(ans[i][j]+1ll*B[i][j]*dafa[t])%ha;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=k;j++)
            printf("%d ",ans[i][j]);
        puts("");
    }
    return 0;
}
