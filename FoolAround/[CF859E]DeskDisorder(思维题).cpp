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

const int ha=1e9+7;
const int N=200010;
int fa[N],cnt[N],cmt[N],n;
bool self[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main()
{
    n=read();
    for(int i=1;i<=2*n;i++) fa[i]=i,cnt[i]=1;
    for(int i=1;i<=n;i++)
    {
        int x=read(),y=read();
        if(x==y) self[find(x)]=1;
        x=find(x);y=find(y);
        if(x!=y)
        {
            fa[y]=x;
            cnt[x]+=cnt[y];
            cmt[x]+=cmt[y]+1;
            self[x]|=self[y];
        }
        else cmt[x]++;
    }
    int ans=1;
    for(int i=1;i<=2*n;i++)
    {
        if(fa[i]!=i) continue;
        if(cmt[i]!=cnt[i]) ans=1ll*ans*cnt[i]%ha;
        else if(!self[i]) ans=2ll*ans%ha;
    }
    printf("%d\n",ans);
    return 0;
}