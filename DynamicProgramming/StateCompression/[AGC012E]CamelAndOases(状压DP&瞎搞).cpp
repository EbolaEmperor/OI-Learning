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
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const int N=200010;
int n,V,X[N],dep=0;
int L[20][N],R[20][N];
int exL[N<<4],exR[N<<4];
pii seg[N];
bool ans[N];

int main()
{
    n=read();V=read();
    for(int i=1;i<=n;i++) X[i]=read();
    X[0]=-INF-V-1;X[n+1]=INF+V+1;
    for(int v=V;v>=0;v>>=1,dep++)
    {
        R[dep][n+1]=n+1;
        for(int i=1;i<=n;i++) L[dep][i]=(X[i]-X[i-1]<=v)?L[dep][i-1]:i;
        for(int i=n;i>=1;i--) R[dep][i]=(X[i+1]-X[i]<=v)?R[dep][i+1]:i;
        if(v==0){dep++;break;}
    }
    for(int i=1;i<=n;i++) seg[i]=pii(L[0][i],R[0][i]);
    int cnt=unique(seg+1,seg+1+n)-(seg+1);
    for(int i=0;i<(1<<dep);i++) exR[i]=n+1;
    for(int s=0;s<(1<<dep);s+=2)
        for(int i=0;i<dep;i++)
        {
            if(!(s&(1<<i))) continue;
            exL[s]=max(exL[s],R[i][exL[s^(1<<i)]+1]);
            exR[s]=min(exR[s],L[i][exR[s^(1<<i)]-1]);
        }
    if(cnt>dep) goto output;
    for(int i=1;i<=cnt;i++)
        for(int s=0;s<(1<<dep);s+=2)
            if(exL[s]>=seg[i].FR-1&&exR[(1<<dep)-1-s-1]<=seg[i].SE+1)
            {
                for(int j=seg[i].FR;j<=seg[i].SE;j++) ans[j]=1;
                break;
            }
    output: for(int i=1;i<=n;i++) puts(ans[i]?"Possible":"Impossible");
    return 0;
}