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

const int N=10000010;
const int ha=998244353;
int fa[N],sz[N],inv[N],n,ans=0;

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
    n=read();inv[1]=1;sz[1]=1;
    for(int i=2;i<=n;i++) sz[i]=1,fa[i]=read();
    for(int i=2;i<=n;i++) inv[i]=ha-1ll*(ha/i)*inv[ha%i]%ha;
    for(int i=n;i>=2;i--) sz[fa[i]]+=sz[i];
    for(int i=1;i<=n;i++) add(ans,inv[sz[i]]);
    printf("%d\n",ans);
    return 0;
}