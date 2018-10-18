#include<bits/stdc++.h>
using namespace std;

const int N=40000;
int prm[N+10],tot=0;
bool mark[N+10];
int n,p[N],cnt=0;

void Init()
{
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]) prm[++tot]=i;
        for(int j=1;j<=tot&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
    int m=n-1;
    for(int i=1;i<=tot&&prm[i]*prm[i]<=m;i++)
    {
        if(m%prm[i]) continue;
        p[++cnt]=prm[i];
        while(!m%prm[i]) m/=prm[i];
    }
}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%n)
        if(b&1) ans=1ll*ans*a%n;
    return ans;
}

bool check(int g)
{
    for(int i=1;i<=cnt;i++)
        if(Pow(g,(n-1)/p[i])==1) return 0;
    return 1;
}

int getroot()
{
    int g=2;
    while(!check(g)) g++;
    return g;
}

int main()
{
    scanf("%d",&n);Init();
    printf("%d\n",getroot());
    return 0;
}