#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353;
const int N=200010;
int r[N],tinv[N];
int omg[N],iomg[N],inv[N];
int strl[20][20],fac[N],ifac[N];
int f[20][N],g[20][N],h[20][N],ig0[N],sum[N];
int n,k;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int dev(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,LL b)
{
    int ans=1;
    if(b<0) b+=ha-1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void math_init(int n=200000)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
    strl[0][0]=1;
    for(int i=1;i<=15;i++)
        for(int j=1;j<=i;j++)
            strl[i][j]=(strl[i-1][j-1]+1ll*j*strl[i-1][j])%ha;
}

void NTT_init()
{
    for(int i=1;i<N;i<<=1)
    {
        int p=i<<1;
        omg[i]=Pow(3,(ha-1)/p);
        iomg[i]=Pow(omg[i],ha-2);
        inv[i]=Pow(i,ha-2);
    }
}

void NTT(int *A,int n,int d)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int wn=(d>0)?omg[i]:iomg[i];
        for(int j=0;j<n;j+=i<<1)
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=add(x,y);
                A[i+j+k]=dev(x,y);
                w=1ll*w*wn%ha;
            }
    }
    if(d>0) return;
    for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv[n]%ha;
}

void get_inv(int *a,int *b,int n)
{
    if(n==1){b[0]=Pow(a[0],ha-2);return;}
    get_inv(a,b,(n+1)>>1);
    int l=0,len=1;while(len<(n<<1)) len<<=1,l++;
    for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
    for(int i=0;i<len;i++) tinv[i]=(i<n)?a[i]:0;
    NTT(tinv,len,1);NTT(b,len,1);
    for(int i=0;i<len;i++)
        b[i]=1ll*(2ll-1ll*tinv[i]*b[i]%ha+ha)*b[i]%ha;
    NTT(b,len,-1);
    for(int i=n;i<len;i++) b[i]=0;
}

int C(LL n,int m)
{
    int res=1;
    for(LL i=n;i>n-m;i--) res=i*res%ha;
    res=1ll*res*ifac[m]%ha;
    return res;
}

void falun_dafa_is_good()
{
    int len=1;while(len<=n) len<<=1;
    for(int i=0;i<=k;i++)
    {
        for(int j=0;j<len;j++)
        {
            LL e=1ll*j*(j-1)/2;
            int s=1ll*C(e,i)*Pow(2,e-i)%ha;
            g[i][j]=1ll*s*ifac[j]%ha;
            if(j) h[i][j]=1ll*s*ifac[j-1]%ha;
        }
        if(!i) get_inv(g[i],ig0,len);
        NTT(g[i],len<<1,1);
    }
    NTT(ig0,len<<1,1);
    int ans=0;
    for(int i=0;i<=k;i++)
    {
        memset(sum,0,sizeof(sum));
        for(int l=0;l<(len<<1);l++)
            for(int j=0;j<i;j++)
                sum[l]=(sum[l]+1ll*f[j][l]*g[i-j][l])%ha;
        NTT(sum,len<<1,-1);
        for(int j=0;j<len;j++) f[i][j]=(h[i][j]-sum[j]+ha)%ha;
        NTT(f[i],len<<1,1);
        for(int j=0;j<(len<<1);j++) f[i][j]=1ll*f[i][j]*ig0[j]%ha;
        NTT(f[i],len<<1,-1);
        for(int j=len;j<(len<<1);j++) f[i][j]=0;
        ans=(ans+1ll*fac[n-1]*f[i][n]%ha*strl[k][i]%ha*fac[i])%ha;
        NTT(f[i],len<<1,1);
    }
    printf("%d\n",ans);
}

int main()
{
    NTT_init();math_init();
    scanf("%d%d",&n,&k);
    falun_dafa_is_good();
    return 0;
}