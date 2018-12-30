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

typedef pair<int,int> pii;
const int N=300010;
int belong[N],n,k,all;
int cnt[N],sum[N],w[N];
int dis[20][20];
pii a[20];

void dis_init()
{
    memset(dis,0x3f,sizeof(dis));
    for(int u=0;u<n;u++)
    {
        int s=belong[u];cnt[s]++;
        for(int i=0;i<k;i++)if(s&(1<<i))
            for(int j=0;j<k;j++)if((s&(1<<j))&&i!=j)
                dis[i][j]=w[i];
    }
    for(int i=0;i<k;i++) dis[i][i]=0;
    for(int l=0;l<k;l++)
        for(int i=0;i<k;i++)
            for(int j=0;j<k;j++)
                dis[i][j]=min(dis[i][j],dis[i][l]+dis[l][j]);
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            dis[i][j]+=w[j];
}

void sum_init()
{
    memcpy(sum,cnt,sizeof(sum));
    for(int t=1;t<all;t<<=1)
        for(int s=0;s<all;s++)
            if(s&t) sum[s]+=sum[s^t];
}

long long gao(int s)
{
    for(int i=0;i<k;i++)
    {
        a[i]=pii(INT_MAX,i);
        for(int j=0;j<k;j++)
        {
            if(!(s&(1<<j))) continue;
            a[i].first=min(a[i].first,dis[j][i]);
        }
    }
    sort(a,a+k);
    long long res=0;int cur=0;
    for(int i=k-1;i>=0;i--)
    {
        int x=1<<a[i].second;cur|=x;
        res+=1ll*a[i].first*(sum[cur]-sum[cur^x]);
    }
    return res-a[0].first;
}

int main()
{
    n=read();k=read();all=1<<k;
    for(int i=0,s;i<k;i++)
    {
        w[i]=read();s=read();
        for(int j=0;j<s;j++)
            belong[read()-1]|=1<<i;
    }
    dis_init();sum_init();
    long long ans=0;
    for(int s=0;s<all;s++)
        if(cnt[s]) ans+=gao(s)*cnt[s];
    printf("%lld\n",ans/2);
    return 0;
}
