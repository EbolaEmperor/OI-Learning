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
char obuf[S],*oS=obuf,*oT=obuf+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void Put(char c){*oS++=c;if(oS==oT) flush();}
inline void print(int x)
{
    if(!x) Put('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) Put(qu[qr--]);
    Put(' ');
}

const int N=1000010;
int arrL[N<<2],*li=arrL+N,l[N];
int arrR[N<<2],*ri=arrR+N,r[N];
int dead[N];

inline int gao(int *arr,int p,int k)
{
    arr[p+k]=arr[p];
    return arr[p];
}

int main()
{
    int n=read(),m=read();
    for(int i=1;i<=n;i++) li[i]=ri[i]=i;
    li[0]=1;ri[n+1]=n;
    for(int i=1;i<N;i++) li[n+i]=n+1;
    for(int i=1;i<=m;i++)
    {
        int x=read();
        int lt=gao(li,x,2);
        int rt=gao(ri,x,-2);
        if(lt<=rt) dead[lt]++,dead[rt+2]--;
        li++;gao(li,0,2);
        ri--;gao(ri,n+1,-2);
    }
    for(int i=1;i<=n;i++)
        for(int j=li[i];j<li[i+2];j+=2)
            l[j]=i;
    for(int i=n;i>=1;i--)
        for(int j=ri[i];j>ri[i-2];j-=2)
            r[j]=i;
    for(int i=3;i<=n;i+=2) dead[i]+=dead[i-2];
    for(int i=4;i<=n;i+=2) dead[i]+=dead[i-2];
    for(int i=1;i<=n;i++)
        print(dead[i]?0:(r[i]-l[i])/2+1);
    flush();
    return 0;
}