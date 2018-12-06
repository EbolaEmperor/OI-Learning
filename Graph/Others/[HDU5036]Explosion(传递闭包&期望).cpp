#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*Tl;
inline char Get()
{
    if(H==Tl) Tl=(H=buf)+fread(buf,1,S,stdin);
    if(H==Tl) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=1010;
bitset<N> T[N];

int main()
{
    int t=read(),n,m,x;
    for(int cas=1;cas<=t;cas++)
    {
        n=read();
        for(int i=1;i<=n;i++)
        {
            m=read();
            T[i].reset();
            T[i][i]=1;
            for(int j=1;j<=m;j++)
                T[i][read()]=1;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(T[j][i]) T[j]|=T[i];
        double ans=0;
        for(int i=1;i<=n;i++)
        {
            int cnt=0;
            for(int j=1;j<=n;j++)
                if(T[j][i]) cnt++;
            ans+=1.0/cnt;
        }
        printf("Case #%d: %.5lf\n",cas,ans);
    }
    return 0;
}