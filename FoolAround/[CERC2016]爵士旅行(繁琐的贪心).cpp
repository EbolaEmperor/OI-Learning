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
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
inline bool readc()
{
    char c=Get();
    while(c!='O'&&c!='R') c=Get();
    return c=='R';
}
template<class I> inline void upmin(I &x,const I &y){if(y<x) x=y;}

typedef long long LL;
typedef pair<int,int> pii;
const int N=300010;
struct Type
{
    int u,v,ty;
    Type(int _u=0,int _v=0,int _ty=0):u(_u),v(_v),ty(_ty){}
    LL gethash(){return (LL)u*N*2+v*2+ty;}
};

unordered_map<LL,int> h;
map<pii,int> idx;
int n,m,pfm[N],d[N],cnt=0;
vector<int> V[N];
int stk[N];
bool del[N];
LL ans=0;

int val(pii pr,int d)
{
    LL tmp=Type(pr.FR,pr.SE,d).gethash();
    if(!h.count(tmp)) return INT_MAX;
    else return h[tmp];
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++) pfm[i]=read();
    int tot=read();
    for(int i=1;i<=tot;i++)
    {
        int x=read(),y=read(),z=readc(),w=read();
        if(!h.count(Type(x,y,z).gethash())) h[Type(x,y,z).gethash()]=w;
        else upmin(h[Type(x,y,z).gethash()],w);
    }
    for(int i=1;i<m;i++)
    {
        int x=pfm[i],y=pfm[i+1];
        if(x>y) swap(x,y),d[i]=1;
        if(!idx.count(pii(x,y))) idx[pii(x,y)]=++cnt;
        V[idx[pii(x,y)]].push_back(i);
    }
    for(auto mpr : idx)
    {
        if(!V[mpr.SE].size()) continue;
        pii pr=mpr.FR,ipr=pii(pr.SE,pr.FR);
        LL A=val(pr,0),B=val(ipr,0),AB=val(pr,1),BA=val(ipr,1),dd=0;
        upmin(A,AB);upmin(B,BA);upmin(AB,A+B);upmin(BA,B+A);
        if(AB>BA) swap(A,B),swap(AB,BA),dd=1;
        memset(del,0,sizeof(bool)*V[mpr.SE].size());
        for(int i=0,top=0;i<V[mpr.SE].size();i++)
        {
            if(d[V[mpr.SE][i]]==dd) stk[++top]=i;
            else if(top) del[stk[top]]=del[i]=1,top--,ans+=AB;
        }
        for(int i=0,top=0;i<V[mpr.SE].size();i++)
        {
            if(del[i]) continue;
            if(d[V[mpr.SE][i]]!=dd) stk[++top]=i;
            else if(top) del[stk[top]]=del[i]=1,top--,ans+=BA;
        }
        for(int i=0;i<V[mpr.SE].size();i++)
        {
            if(del[i]) continue;
            if(d[V[mpr.SE][i]]==dd) ans+=A;
            else ans+=B;
        }
    }
    printf("%lld\n",ans);
    return 0;
}