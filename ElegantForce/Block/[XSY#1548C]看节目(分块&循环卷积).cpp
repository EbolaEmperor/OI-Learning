#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=300010,M=100;
int omg[N],iomg[N],inv[N];
int A[N],B[N],rev[N];
int dv[N],st[M],ed[M],tot=0;
int n,m,seed,y,bsz,a[N],p[N];
int lpn=0,lpid[N],idx[N];
vector<int> loop[M],sum[M][M];
long long falun=0;
bool vis[N];

int random(int l,int r)
{
    seed=1ll*seed*y%ha;
    return seed%(r-l+1)+l;
}
void make_permutation()
{
    for(int i=1;i<=n;i++)
        p[i]=i,swap(p[random(1,i)],p[i]);
}

void divide()
{
    for(int i=1,cnt=0;i<=n;i++)
    {
        if(!cnt) st[++tot]=i;
        dv[i]=tot;cnt++;
        if(cnt==bsz) ed[tot]=i,cnt=0;
    }
    ed[tot]=n;
}

inline int add(const int &x,const int &y){return x+y>=ha?x+y-ha:x+y;}
inline int mns(const int &x,const int &y){return x-y<0?x-y+ha:x-y;}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
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
    for(int i=0;i<n;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int wn=(d>0)?omg[i]:iomg[i];
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=add(x,y);
                A[i+j+k]=mns(x,y);
                w=1ll*w*wn%ha;
            }
    }
    if(d<0) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv[n]%ha;
}

void prework(int x)
{
    int cnt=0;lpn++;
    static int val[N];
    for(;!vis[x];x=p[x])
    {
        loop[lpn].push_back(x);
        val[idx[x]=cnt++]=a[x];
        lpid[x]=lpn;
        vis[x]=1;
    }
    int len=1,l=0;
    while(len<=(cnt<<1)) len<<=1,l++;
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1);
    for(int b=1;b<=tot;b++)
    {
        memset(A,0,sizeof(int)*(len));
        memset(B,0,sizeof(int)*(len));
        for(int i=0;i<cnt;i++) A[i]=val[i];
        reverse(A,A+cnt);
        for(int i=1;i<=cnt;i++)
            B[i]=(loop[lpn][i-1]<=ed[b]);
        NTT(A,len,1);NTT(B,len,1);
        for(int i=0;i<len;i++)
            A[i]=1ll*A[i]*B[i]%ha;
        NTT(A,len,-1);
        for(int i=0;i<cnt;i++)
            sum[lpn][b].push_back(add(A[i],A[i+cnt]));
    }
}

int query(int x)
{
    if(x==0) return 0;
    int res=0;
    if(dv[x]>1)for(int i=1;i<=lpn;i++)
        res=add(res,sum[i][dv[x]-1][falun%loop[i].size()]);
    for(int i=st[dv[x]];i<=x;i++)
    {
        int d=lpid[i],len=loop[d].size();
        res=add(res,a[loop[d][(idx[i]-falun%len+len)%len]]);
    }
    return res;
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&seed,&y);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    bsz=sqrt(n*log(n)/log(2));
    divide();make_permutation();NTT_init();
    for(int i=1;i<=n;i++) if(!vis[i]) prework(i);
    int opt,x,y;
    while(m--)
    {
        scanf("%d",&opt);
        if(opt==1) scanf("%d",&x),falun+=x;
        if(opt==2)
        {
            scanf("%d%d",&x,&y);
            int ans=mns(query(y),query(x-1));
            printf("%d\n",ans);
        }
    }
    return 0;
}