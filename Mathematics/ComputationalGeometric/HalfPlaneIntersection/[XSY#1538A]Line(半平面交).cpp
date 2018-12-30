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
const int N=200010;
struct Line
{
    LL k,b;
    Line(LL _k=0,LL _b=0):k(_k),b(_b){}
    bool operator < (const Line &a) const{return k==a.k?b<a.b:k<a.k;}
    LL get(const LL &x){return k*x+b;}
} l[N],r[N],sl[N],sr[N];
int n,top1=0,top2=0;

inline double gaox(const Line &a,const Line &b){return (double)(b.b-a.b)/(double)(a.k-b.k);}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        l[i]=Line(1-i,read());
        r[i]=Line(1-i,read());
    }
    sort(l+1,l+1+n);sort(r+1,r+1+n);
    for(int i=1;i<=n;i++)
    {
        while(top1>1&&gaox(sl[top1-1],l[i])<gaox(sl[top1],sl[top1-1])) top1--;
        sl[++top1]=l[i];
    }
    for(int i=n;i>=1;i--)
    {
        while(top2>1&&gaox(sr[top2-1],r[i])<gaox(sr[top2],sr[top2-1])) top2--;
        sr[++top2]=r[i];
    }
    LL ans=0,p1=1,p2=1,p=ceil(gaox(sl[1],sr[1]));
    while(p1<top1||p2<top2)
    {
        LL x1=p1<top1?floor(gaox(sl[p1],sl[p1+1])):2e9;
        LL x2=p2<top2?floor(gaox(sr[p2],sr[p2+1])):2e9;
        if(x1<x2)
        {
            if(x1<p){p1++;continue;}
            LL yl1=sl[p1].get(p),yr1=sr[p2].get(p);
            LL yl2=sl[p1].get(x1),yr2=sr[p2].get(x1);
            ans+=(yr1-yl1+1+yr2-yl2+1)*(x1-p+1)/2;
            p1++;p=x1+1;
        }
        else
        {
            if(x2<p){p2++;continue;}
            LL yl1=sl[p1].get(p),yr1=sr[p2].get(p);
            LL yl2=sl[p1].get(x2),yr2=sr[p2].get(x2);
            ans+=(yr1-yl1+1+yr2-yl2+1)*(x2-p+1)/2;
            p2++;p=x2+1;
        }
    }
    LL x=floor(gaox(sl[top1],sr[top2]));
    if(x>=p)
    {
        LL yl1=sl[top1].get(p),yr1=sr[top2].get(p);
        LL yl2=sl[top1].get(x),yr2=sr[top2].get(x);
        ans+=(yr1-yl1+1+yr2-yl2+1)*(x-p+1)/2;
    }
    printf("%lld\n",ans);
    return 0;
}
