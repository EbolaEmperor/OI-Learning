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
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int N=500010;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppp;
priority_queue<ppp> q;
int mn[N<<2],mnid[N<<2],leaf;
int n,K,L,R;
int sum[N];

void build()
{
    for(leaf=1;leaf<=n+2;leaf<<=1);
    memset(mn,0x3f,sizeof(mn));leaf++;
    for(int i=0;i<=n;i++) mn[leaf+i]=sum[i],mnid[leaf+i]=i;
    for(int i=leaf-2;i;i--)
    {
        if(mn[i<<1]<mn[i]) mn[i]=mn[i<<1],mnid[i]=mnid[i<<1];
        if(mn[i<<1|1]<mn[i]) mn[i]=mn[i<<1|1],mnid[i]=mnid[i<<1|1];
    }
}
int query(int l,int r)
{
    if(l>r) return -1;
    int res=INT_MAX,ans;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) if(mn[l^1]<res) res=mn[l^1],ans=mnid[l^1];
        if(r&1) if(mn[r^1]<res) res=mn[r^1],ans=mnid[r^1];
    }
    return ans;
}

int main()
{
    n=read();K=read();L=read();R=read();
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+read();
    build();
    for(int i=L;i<=n;i++)
    {
        int l=max(i-R,0),x=query(l,i-L);
        q.push(ppp(pii(sum[i]-sum[x],i),pii(l,i-L)));
    }
    long long ans=0;
    for(int i=1;i<=K;i++)
    {
        pii p1=q.top().first,p2=q.top().second;q.pop();
        int p=p1.second;ans+=p1.first;
        int x=query(p2.first,p2.second);
        int y1=query(p2.first,x-1),y2=query(x+1,p2.second);
        if(~y1) q.push(ppp(pii(sum[p]-sum[y1],p),pii(p2.first,x-1)));
        if(~y2) q.push(ppp(pii(sum[p]-sum[y2],p),pii(x+1,p2.second)));
    }
    cout<<ans<<endl;
    return 0;
}