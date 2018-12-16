#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
inline char readc()
{
    char c=Get();
    while(c!='U'&&c!='D') c=Get();
    return c;
}

typedef long long LL;
const int N=2010;
int num[N][N],n;
int f[N][N],bit[N][N];
LL ans=0;

inline int lowbit(int x){return x&-x;}
void add(int d,int p,int x){for(;p<=n+1;p+=lowbit(p)) bit[d][p]+=x;}
int query(int d,int p){int res=d?0:-n;for(;p;p-=lowbit(p)) res+=bit[d][p];return res;}

int change1(int x,int y)
{
    int l=y,r=y,cnt=0;
    while(r<n&&query(x,r)+1>query(x-1,r+1)) r++;
    add(x,l,1);add(x,r+1,-1);cnt+=r-l+1;
    for(int i=x+1;i<=n;i++)
    {
        while(r<n&&query(i,r)+1>query(i-1,r+1)) r++;
        while(query(i,l-1)>=query(i-1,l)) l++;
        if(l>r) break;
        add(i,l,1);add(i,r+1,-1);
        cnt+=r-l+1;
    }
    return cnt;
}

int change2(int x,int y)
{
    int l=y,r=y,cnt=0;
    while(r<n&&query(x,r)-1>=query(x-1,r+1)) r++;
    add(x,l,-1);add(x,r+1,1);cnt+=r-l+1;
    for(int i=x+1;i<=n;i++)
    {
        while(r<n&&query(i,r)-1>=query(i-1,r+1)) r++;
        while(query(i,l-1)>query(i-1,l)) l++;
        if(l>r) break;
        add(i,l,-1);add(i,r+1,1);
        cnt+=r-l+1;
    }
    return cnt;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            num[i][j]=read();
            f[i][j]=max(f[i-1][j],f[i][j-1])+num[i][j];
            add(i,j,f[i][j]);add(i,j+1,-f[i][j]);
            ans+=f[i][j];
        }
    printf("%lld\n",ans);
    char opt;int x,y;
    for(int T=1;T<=n;T++)
    {
        opt=readc();x=read();y=read();
        if(opt=='U') ans+=change1(x,y);
        else ans-=change2(x,y);
        printf("%lld\n",ans);
    }
    return 0;
}