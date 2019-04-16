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
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void printd(int d,double x)
{
    long long t=(long long)floor(x),f=t;
    while(t) qu[++qr]=t%10,t/=10;
    while(qr) putc(qu[qr--]+'0');
    putc('.');x-=f;
    while(d--)
    {
        double y=x*10;x*=10;
        int c=(int)floor(y);
        putc(c+'0');x-=c;
    }
}

typedef long long LL;
typedef pair<LL,double> pld;
const int N=500010;
LL t[N],v[N];
pld q[N];
int l=1,r=0;

int main()
{
    int n=read(),L=read();
    for(int i=1;i<=n;i++)
        t[i]=read(),v[i]=read();
    int sum=0;double cur=0;
    for(int i=1;i<=n;i++)
    {
        while(v[i]+sum>L)
        {
            int pour=min(v[i]+sum-L,q[l].FR);
            sum-=pour;
            q[l].FR-=pour;
            cur-=q[l].SE*pour;
            if(!q[l].FR) l++;
        }
        q[++r]=pld(v[i],t[i]);
        sum+=v[i];cur+=1ll*t[i]*v[i];
        while(l<r&&q[r].SE<q[r-1].SE)
        {
            q[r-1].SE=(q[r-1].SE*q[r-1].FR+q[r].SE*q[r].FR)/(q[r-1].FR+q[r].FR);
            q[r-1].FR+=q[r].FR;r--;
        }
        printd(7,cur/L);putc('\n');
    }
    flush();
    return 0;
}