#include<bits/stdc++.h>
#define FR first
#define SE second
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

const int N=1000010;
typedef long long LL;
typedef pair<LL,int> pli;
priority_queue<pli> hole;
priority_queue<LL> mouse;
pli obj[N<<1];
LL ans=0;

void gaoH(pli p)
{
    while(p.SE&&!mouse.empty()&&p.FR<mouse.top())
    {
        LL delta=p.FR-mouse.top();
        ans+=delta;p.SE--;
        mouse.pop();
        hole.push(pli(p.FR+delta,1));
    }
    if(p.SE) hole.push(p);
}

void gaoM(pli p)
{
    LL w=INT64_MAX/100;
    if(!hole.empty())
    {
        pli tmp=hole.top();hole.pop();
        w=p.FR-tmp.FR;tmp.SE--;
        if(tmp.SE) hole.push(tmp);
    }
    mouse.push(p.FR+w);
    ans+=w;
}

int main()
{
    LL V=0;int n=read(),m=read();
    for(int i=1;i<=n;i++) obj[i]=pli(read(),-INT_MAX);
    for(int i=1;i<=m;i++) obj[n+i].FR=read(),V+=(obj[n+i].SE=read());
    if(V<n) return puts("-1"),0;
    sort(obj+1,obj+1+n+m);
    for(int i=1;i<=n+m;i++)
        if(obj[i].SE>-INT_MAX) gaoH(obj[i]);
        else gaoM(obj[i]);
    printf("%lld\n",ans);
    return 0;
}