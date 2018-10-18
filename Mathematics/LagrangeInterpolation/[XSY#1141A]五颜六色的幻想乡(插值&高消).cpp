#include<bits/stdc++.h>
#define ha 1000000007
#define X(x) (1000+(x))
using namespace std;

const int N=55,M=N*N*2;
int G[N][N],n,m;
int fr[M],tt[M],col[M];
int arry[M],a[M];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int Det()
{
    int ans=1;
    for(int i=1;i<n;i++)
    {
        int p=i;
        while(p<n&&!G[p][i]) p++;
        if(p>=n) return -1;
        if(p!=i)
        {
            ans=-ans;
            for(int j=1;j<n;j++) swap(G[i][j],G[p][j]);
        }
        ans=1ll*ans*G[i][i]%ha;
        int inv=Pow(G[i][i],ha-2);
        for(int j=i+1;j<n;j++)
        {
            int t=1ll*inv*G[j][i]%ha;
            for(int k=1;k<n;k++)
                G[j][k]=(G[j][k]-1ll*G[i][k]*t%ha+ha)%ha;
        }
    }
    return (ans+ha)%ha;
}

void prework()
{
    for(int i=1;i<=n*n;i++)
    {
        memset(G,0,sizeof(G));
        int x=X(i),px=Pow(x,n);
        for(int j=1;j<=m;j++)
        {
            int u=fr[j],v=tt[j],w=col[j];
            if(w==1) w=x;
            if(w==2) w=px;
            if(w==3) w=1;
            (G[u][u]+=w)%=ha;
            (G[v][v]+=w)%=ha;
            (G[u][v]-=w-ha)%=ha;
            (G[v][u]-=w-ha)%=ha;
        }
        arry[i]=Det();
    }
}

struct Poly
{
    vector<int> a;
    Poly(int x=0){a.resize(x);}
    int size(){return a.size();}
    int& operator [] (const int &x){return a[x];}

    Poly operator * (Poly &B)
    {
        Poly C(size()+B.size()-1);
        if(!size()) return B;
        for(int i=0;i<size();i++)
            for(int j=0;j<B.size();j++)
                C[i+j]=(C[i+j]+1ll*a[i]*B[j])%ha;
        return C;
    }

    Poly operator / (Poly &B)
    {
        Poly C=*this;
        int x=0,y=Pow(B[0],ha-2);
        for(int i=0;i<size();i++)
        {
            int z=(C[i]-x+ha)%ha;
            C[i]=x;x=1ll*z*y%ha;
        }
        for(int i=0;i<size()-1;i++)
            C[i]=C[i+1];
        C.a.pop_back();
        return C;
    }
};

void Lagrange()
{
    static int fac[M];
    Poly S;int t=n*n;fac[0]=1;
    for(int i=1;i<=t;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    for(int i=1;i<=t;i++)
    {
        Poly tmp(2);
        tmp[0]=ha-X(i);tmp[1]=1;
        S=S*tmp;
    }
    for(int i=1;i<=t;i++)
    {
        Poly tmp(2);
        tmp[0]=ha-X(i);tmp[1]=1;
        Poly erator=S/tmp;
        int minator=1ll*fac[i-1]*fac[t-i]%ha;
        if((t-i)&1) minator=ha-minator;
        minator=Pow(minator,ha-2);
        int k=1ll*minator*arry[i]%ha;
        for(int j=0;j<erator.size();j++)
            a[j]=(a[j]+1ll*erator[j]*k)%ha;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",fr+i,tt+i,col+i);
    prework();Lagrange();
    for(int r=0;r<n;r++)
        for(int b=0;b<n-r;b++)
            printf("%d\n",(a[r+n*b]+ha)%ha);
    return 0;
}