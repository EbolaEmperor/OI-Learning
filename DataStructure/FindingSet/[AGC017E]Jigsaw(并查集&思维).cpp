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

const int N=410;
int n,h,in[N],out[N];
int fa[N];
bool ok[N];

int find(const int &x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main()
{
    n=read();h=read();
    for(int i=1;i<=(h<<1);i++) fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        int A=read(),B=read(),C=read(),D=read();
        int x=C?C+h:A,y=D?D:B+h;
        out[x]++;in[y]++;
        x=find(x);y=find(y);
        if(x!=y) fa[x]=y;
    }
    for(int i=1;i<=h;i++) if(in[i]>out[i]) return !puts("NO");
    for(int i=h+1;i<=(h<<1);i++) if(in[i]<out[i]) return !puts("NO");
    for(int i=1;i<=(h<<1);i++) if(in[i]!=out[i]||!in[i]&&!out[i]) ok[find(i)]=1;
    for(int i=1;i<=(h<<1);i++) if(fa[i]==i&&!ok[i]) return !puts("NO");
    return !puts("YES");
}