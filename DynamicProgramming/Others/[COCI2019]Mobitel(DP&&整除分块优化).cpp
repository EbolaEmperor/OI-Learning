#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=310,M=2010;
int f[2][N][M];
int val[M],idx[M*M],a[N][N];
int r,c,n,tot=0;

inline int udiv(const int &x,const int &y){return (x-1)/y+1;}
inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
    scanf("%d%d%d",&r,&c,&n);
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            scanf("%d",a[i]+j);
    for(int i=1;i<=n;i++)
        if(i==1||udiv(n,i)!=udiv(n,i-1))
            val[idx[udiv(n,i)]=++tot]=udiv(n,i);
    int pp=0;
    f[pp][1][idx[udiv(n,a[1][1])]]=1;
    for(int i=1;i<=r;i++,pp^=1)
    {
        memset(f[pp^1],0,sizeof(f[pp^1]));
        for(int j=1;j<=c;j++)
            for(int k=1;k<=tot;k++)
            {
                if(!f[pp][j][k]) continue;
                if(j<c) add(f[pp][j+1][idx[udiv(val[k],min(val[k],a[i][j+1]))]],f[pp][j][k]);
                if(i<r) add(f[pp^1][j][idx[udiv(val[k],min(val[k],a[i+1][j]))]],f[pp][j][k]);
            }
    }
    cout<<f[pp^1][c][tot]<<endl;
    return 0;
}