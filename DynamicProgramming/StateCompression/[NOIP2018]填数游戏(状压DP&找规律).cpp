#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
int f[2][10][260],n,m,nm;
int len[1000020],tot;

void add(int &x,const int &y){x=x+y>=ha?x+y-ha:x+y;}
int dwn(int t,int x){return t>tot-n+1?x:x-1;}
int rght(int t,int x){return t>tot-n+1?x+1:x;}
bool in(int x,int s){return s&(1<<x-1);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    cin>>n>>m;
    if(n>m) swap(n,m);
    if(n==1)
    {
        printf("%d\n",Pow(2,m));
        return 0;
    }
    if(m>n+1) nm=m,m=n+1;
    tot=n+m-1;
    for(int i=1;i<=n;i++) len[i]=i;
    for(int i=n+1;i<=m;i++) len[i]=n;
    for(int i=m+1;i<=tot;i++) len[i]=tot-i+1;
    f[1][0][1]=f[1][1][1]=1;
    for(int i=2;i<=tot;i++)
    {
        int k=i&1;
        memset(f[k],0,sizeof(f[k]));
        for(int s=0;s<(1<<len[i-1]);s++)
            for(int j=0;j<=len[i-1];j++)
            {
                if(!f[k^1][j][s]) continue;
                for(int y=0;y<=len[i];y++)
                {
                    bool flag=1;
                    for(int x=1;x<len[i];x++)
                        if(x!=y&&!in(rght(i,x),s)){flag=0;break;}
                    if(!flag) continue;
                    int t=0;
                    for(int k=1;k<=len[i];k++)
                    {
                        int d=dwn(i,k),r=rght(i,k);
                        if(d<1&&in(r,s)) t|=1<<k-1;
                        else if(r>len[i-1]&&in(d,s)) t|=1<<k-1;
                        else if(d!=j&&in(d,s)&&in(r,s)) t|=1<<k-1;
                    }
                    add(f[k][y][t],f[k^1][j][s]);
                }
            }
    }
    int ans=0;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            add(ans,f[tot&1][i][j]);
    if(nm) ans=1ll*ans*Pow(3,nm-m)%ha;
    printf("%d\n",ans);
    return 0;
}