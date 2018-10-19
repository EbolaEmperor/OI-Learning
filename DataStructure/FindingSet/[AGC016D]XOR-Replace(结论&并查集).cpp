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

const int N=100010;
int a[N],b[N],n;
int _a[N<<1],_b[N];
int fa[N<<1],sz[N<<1];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main()
{
    n=read();
    int xora=0,xorb=0,ans=0;
    for(int i=1;i<=n;i++) xora^=(_a[i]=a[i]=read());
    for(int i=1;i<=n;i++) xorb^=(_b[i]=b[i]=read());
    a[++n]=xora;b[n]=xorb;_a[n]=a[n];_b[n]=b[n];
    sort(_a+1,_a+1+n);sort(_b+1,_b+1+n);
    for(int i=1;i<=n;i++) if(_a[i]!=_b[i]) return !puts("-1");
    for(int i=1;i<n;i++) ans+=(a[i]!=b[i]);
    if(ans==0) return !puts("0");
    for(int i=1;i<=n;i++) _a[i+n]=_b[i];
    sort(_a+1,_a+1+n);
    int hs=unique(_a+1,_a+1+n)-(_a+1);
    for(int i=1;i<=hs;i++) fa[i]=i,sz[i]=1;
    for(int i=1;i<=n;i++)
    {
        a[i]=lower_bound(_a+1,_a+1+hs,a[i])-_a;
        b[i]=lower_bound(_a+1,_a+1+hs,b[i])-_a;
        int x=find(a[i]),y=find(b[i]);
        if(x!=y) fa[x]=y,sz[y]+=sz[x];
    }
    if(a[n]==b[n]&&sz[find(a[n])]==1) ans++;
    for(int i=1;i<=n;i++) ans+=(fa[i]==i&&sz[i]>1);
    cout<<ans-1<<endl;
    return 0;
}