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

const int N=310;
int A[N][N],n,m;
int pos[N],cnt[N];
bool vis[N];

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            A[i][j]=read();
    for(int i=1;i<=n;i++) pos[i]=1;
    int ans=INT_MAX;
    while(true)
    {
        int mx=0,cc=0;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            while(vis[A[i][pos[i]]]) pos[i]++;
            if(!A[i][pos[i]]) continue;
            cnt[A[i][pos[i]]]++;
            if(cnt[A[i][pos[i]]]>mx)
                cc=A[i][pos[i]],mx=cnt[cc];
        }
        if(!mx) break;
        ans=min(ans,mx);
        vis[cc]=1;
        for(int i=1;i<=n;i++)
            if(A[i][pos[i]]==cc) pos[i]++;
    }
    printf("%d\n",ans);
    return 0;
}