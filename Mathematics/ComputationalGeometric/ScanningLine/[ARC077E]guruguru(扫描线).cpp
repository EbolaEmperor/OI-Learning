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

typedef long long LL;
const int N=100010;
struct Seg{int l,r,extra;} seg[N<<1];
vector<Seg> R[N];
int n,m,a[N],tot=0;

int main()
{
    int cross=0,p=1;
    LL ans=INT64_MAX,cur=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++)
        if(a[i]<a[i+1])
        {
            seg[++tot]={a[i],a[i+1],0};
            R[a[i+1]].push_back(seg[tot]);
            cur+=a[i+1]-a[i];
        }
        else
        {
            seg[++tot]={a[i],m,0};
            R[m].push_back(seg[tot]);
            seg[++tot]={0,a[i+1],m-a[i]};
            R[a[i+1]].push_back(seg[tot]);
            cur+=a[i+1]+m-a[i];
        }
    sort(seg+1,seg+1+tot,[](Seg a,Seg b){return a.l<b.l;});
    for(int i=0;i<=m;i++)
    {
        cur-=cross;
        ans=min(ans,cur);
        for(Seg s : R[i])
        {
            cur+=s.extra+i-s.l-1;
            cross--;
        }
        while(p<=tot&&seg[p].l<=i)
        {
            Seg s=seg[p];
            cur-=s.extra+i-s.l-1;
            cross++;p++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}