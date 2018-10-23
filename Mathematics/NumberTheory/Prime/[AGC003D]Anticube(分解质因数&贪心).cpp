#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline LL read()
{
    LL x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=100010;
LL a[N],b[N][2];
bool mask[3010];
int prm[3010],tot=0,n;
unordered_map<LL,int> cc;
unordered_map<LL,bool> fucked;

LL maxc(const LL &a,const LL &b){return cc[a]>cc[b]?a:b;}

void preprework()
{
    for(int i=2;i<=2200;i++)
    {
        if(mask[i]) continue;
        prm[++tot]=i;
        for(int j=i;j<=2200;j+=i)
            mask[j]=1;
    }
}

void prework()
{
    for(int i=1;i<=n;i++)
    {
        LL x=1,y=1;
        for(int j=1;j<=tot;j++)
        {
            if(a[i]%prm[j]) continue;
            int cnt=0;
            while(a[i]%prm[j]==0)
                a[i]/=prm[j],cnt++;
            if(!(cnt%=3)) continue;
            for(int k=1;k<=cnt;k++) x=x*prm[j];
            for(int k=cnt+1;k<=3;k++) y=y*prm[j];
        }
        LL t=(LL)sqrt(a[i]);
        if(t*t==a[i]) x=x*t*t,y=y*t;
        else x=x*a[i],y=y*a[i]*a[i];
        b[i][0]=x;b[i][1]=y;
        if(!cc.count(x)) cc[x]=1;
        else cc[x]++;
    }
}

int main()
{
    LL ans=0;n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    preprework();prework();
    for(int i=1;i<=n;i++)
    {
        LL c1=b[i][0],c2=b[i][1];
        if(fucked[c1]||fucked[c2]) continue;
        LL x=maxc(c1,c2);fucked[x]=1;
        ans+=(x==1)?1:cc[x];
    }
    cout<<ans<<endl;
    return 0;
}