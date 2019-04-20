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

const int ha=998244353,N=15;
int n,k,e[N][N],ie[N][N],pw3[N],lg2[5000];
int f[N][600000];

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}
inline int lowbit(const int &x){return x&-x;}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    n=read();k=read();
    for(int i=1;i<=n*(n-1);i++)
    {
        static int u,v,p,q;
        u=read()-1;v=read()-1;p=read();q=read();
        e[u][v]=1ll*p*Pow(q,ha-2)%ha;
        ie[u][v]=Pow(1-e[u][v]+ha,ha-2);
    }
    pw3[0]=1;
    for(int i=1;i<=n;i++)
        pw3[i]=pw3[i-1]*3;
    for(int i=0;i<=n;i++) lg2[1<<i]=i;
    int all=pw3[n-1];
    for(int s=0;s<(1<<n-1);s++)
    {
        int tmp=1,t=0;
        for(int i=0;i<n;i++)
            if(s>>i&1) tmp=1ll*tmp*e[0][i+1]%ha,t+=2*pw3[i];
            else tmp=1ll*tmp*(1-e[0][i+1]+ha)%ha;
        f[1][t]=tmp;
    }
    for(int i=1;i<k;i++)
        for(int s=0;s<all;s++)
        {
            if(!f[i][s]) continue;
            static int v0[N],v1[N],v2[N],psb[N];
            int tot0=0,tot1=0,tot2=0,t=s,nxt=0;
            for(int j=1;j<n;j++,t/=3)
            {
                if(t%3==0) v0[tot0++]=j;
                else if(t%3==1) v1[tot1++]=j,nxt+=pw3[j-1];
                else if(t%3==2) v2[tot2++]=j,nxt+=pw3[j-1];
            }
            int cur=f[i][s];
            for(int j=0;j<tot0;j++)
            {
                int noblack=1,inv=1;
                for(int l=0;l<tot2;l++)
                    noblack=1ll*noblack*(1-e[v2[l]][v0[j]]+ha)%ha,
                    inv=1ll*inv*ie[v2[l]][v0[j]]%ha;
                psb[j]=1ll*(1-noblack+ha)*inv%ha;
                cur=1ll*cur*noblack%ha;
            }
            for(int ss=0;ss<(1<<tot0);ss++)
            {
                int tmp=cur,tnxt=nxt;
                for(int tt=ss;tt;tt-=lowbit(tt))
                    tmp=1ll*tmp*psb[lg2[lowbit(tt)]]%ha,tnxt+=2*pw3[v0[lg2[lowbit(tt)]]-1];
                add(f[i+1][tnxt],tmp);
            }
        }
    int ans=0;
    for(int s=0;s<all;s++)
    {
        bool flag=1;int t=s;
        for(int i=0;i<n-1;i++,t/=3)
            if(t%3==0){flag=0;break;}
        if(flag) add(ans,f[k][s]);
    }
    printf("%d\n",ans);
    return 0;
}
