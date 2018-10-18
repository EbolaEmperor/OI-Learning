#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=40000;
const int M=41357;
vector<int> factor;
bool mark[N+10];
int prm[N],tot=0;
int n,m,k;

void Init()
{
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]) prm[++tot]=i;
        for(int j=1;j<=tot&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
}

int Pow(int a,int b)
{
    int ans=1;
    if(b==-1) return -1;
    for(;b;b>>=1,a=1ll*a*a%m)
        if(b&1) ans=1ll*ans*a%m;
    return ans;
}

bool check(int n,int g)
{
    for(int x : factor)
        if(Pow(g,n/x)==1) return 0;
    return 1;
}

int findroot(int n)
{
    factor.clear();int m=n-1,g=2;
    for(int i=1;i<=tot&&prm[i]*prm[i]<=m;i++)
    {
        if(m%prm[i]) continue;
        factor.push_back(prm[i]);
        while(m%prm[i]==0) m/=prm[i];
    }
    if(m>1) factor.push_back(m);
    while(!check(n-1,g)) g++;
    return g;
}

struct Hash
{
    int h[M],nxt[N],key[N],val[N],tot;
    Hash()
    {
        memset(h,0,sizeof(h));tot=0;
        memset(key,0,sizeof(key));
        memset(val,0,sizeof(val));
        memset(nxt,0,sizeof(key));
    }
    bool exist(int x)
    {
        int s=x%M;
        for(int i=h[s];i;i=nxt[i])
            if(key[i]==x) return 1;
        return 0;
    }
    int& operator [] (const int &x)
    {
        int s=x%M,i;
        for(i=h[s];i;i=nxt[i])
            if(key[i]==x) return val[i];
        key[++tot]=x;
        nxt[tot]=h[s];
        h[s]=tot;
        return val[tot];
    }
};

int exGcd(int a,int b,LL &x,LL &y)
{
    if(b==0){x=1;y=0;return a;}
    int g=exGcd(b,a%b,x,y);
    LL t=x;x=y;y=t-(a/b)*x;
    return g;
}

int BSGS(int a,int b,int p)
{
    Hash lg;
    int m=ceil(sqrt(p)),base=1,d=1;
    for(int i=0;i<m;i++)
        lg[base]=i,base=1ll*base*a%p;
    for(int i=0;i<m;i++)
    {
        LL x,y;exGcd(d,p,x,y);
        x*=b;x=(x%p+p)%p;
        if(lg.exist(x)) return m*i+lg[x];
        d=1ll*d*base%p;
    }
    return -1;
}

vector<int> solve(int a,int b,int p)
{
    vector<int> ans;
    LL x,y;int g=exGcd(a,p,x,y);
    if(b%g){ans.push_back(-1);return ans;}
    x*=(b/g);y*=(b/g);
    LL c=p/g,tx=x=(x%c)+c%c;
    if(x>=0&&x<p) ans.push_back(x);
    while(x+c<p) if((x+=c)>=0) ans.push_back(x);
    while(tx-c>=0) if((tx-=c)<p) ans.push_back(tx);
    return ans;
}

int main()
{
    int T;Init();
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d%d",&m,&k,&n);
        int g=findroot(m),t=BSGS(g,n,m);
        if(t==-1){puts("No Solution");continue;}
        vector<int> ans=solve(k,t,m-1);
        for(int& x : ans) x=Pow(g,x);
        sort(ans.begin(),ans.end());
        if(ans[0]==-1){puts("No Solution");continue;}
        for(int x : ans) printf("%d ",x);puts("");
    }
    return 0;
}