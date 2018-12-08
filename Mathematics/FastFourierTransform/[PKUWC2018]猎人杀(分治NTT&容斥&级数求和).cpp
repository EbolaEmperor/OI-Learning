#include<bits/stdc++.h>
using namespace std;

const int N=400010;
const int ha=998244353;
int r[N],a[N],b[N],w[N],n;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void NTT(int *A,int n,int d)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int p=i<<1,wn=Pow(3,(ha-1)/p);
        if(d==-1) wn=Pow(wn,ha-2);
        for(int j=0;j<n;j+=p)
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=(x+y)%ha;
                A[i+j+k]=(x-y+ha)%ha;
                w=1ll*w*wn%ha;
            }
    }
    int inv=Pow(n,ha-2);
    if(d==-1) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv%ha;
}

struct Poly
{
    int n,*p;
    Poly(int _n=-1){n=_n;p=new int[n+1];memset(p,0,sizeof(int)*(n+1));}
    int& operator [] (const int &x){return p[x];}
    void clear(){delete p;}
    friend Poly operator * (Poly &A,Poly &B)
    {
        int len=1,l=0;for(;len<=A.n+B.n;len<<=1,l++);
        for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
        for(int i=0;i<=A.n;i++) a[i]=A[i];
        for(int i=0;i<=B.n;i++) b[i]=B[i];
        for(int i=A.n+1;i<len;i++) a[i]=0;
        for(int i=B.n+1;i<len;i++) b[i]=0;
        NTT(a,len,1);NTT(b,len,1);
        for(int i=0;i<len;i++)
            a[i]=1ll*a[i]*b[i]%ha;
        NTT(a,len,-1);Poly res(A.n+B.n);
        memcpy(res.p,a,sizeof(int)*(res.n+1));
        return res;
    }
} poly[N];

void divide(int o,int l,int r)
{
    if(l==r)
    {
        poly[o]=Poly(w[l]);
        poly[o][w[l]]=-1;
        poly[o][0]=1;
        return;
    }
    int mid=(l+r)/2;
    divide(o<<1,l,mid);
    divide(o<<1|1,mid+1,r);
    poly[o]=poly[o<<1]*poly[o<<1|1];
    poly[o<<1].clear();
    poly[o<<1|1].clear();
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    divide(1,2,n);
    int res=0;
    for(int i=0;i<=poly[1].n;i++)
        res=(res+1ll*poly[1][i]*Pow(w[1]+i,ha-2))%ha;
    res=1ll*w[1]*res%ha;
    printf("%d\n",res);
    return 0;
}