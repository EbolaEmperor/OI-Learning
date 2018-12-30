#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=5003;
int memf[2][2][N<<1],*f[2][2];
int memg[2][2][N<<1],*g[2][2];
int memgs[N<<1],*gs=memgs+N;
char s[N],t[N];int n,m;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}

void falun_dafa_is_good(char *s,int *f[2][2],int n)
{
    f[0][1][0]=1;
    for(int i=n,p=1;i>=1;i--,p^=1)
        for(int j=i-n-1;j<=n-i+1;j++)
        {
            f[p][0][j]=f[p][1][j]=0;
            if(s[i]=='P'||s[i]=='?')
            {
                if(!j) for(int l=1;l<=n-i;l++) f[p][0][j]=add(f[p][0][j],add(f[p^1][0][l],f[p^1][1][l]));
                else if(j<0) f[p][0][j]=add(f[p][0][j],f[p^1][0][j+1]),f[p][1][j]=add(f[p][1][j],f[p^1][1][j+1]);
            }
            if(s[i]=='V'||s[i]=='?') f[p][0][j]=add(f[p][0][j],f[p^1][0][j-1]),f[p][1][j]=add(f[p][1][j],f[p^1][1][j-1]);
        }
}

int main()
{
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            f[i][j]=memf[i][j]+N,g[i][j]=memg[i][j]+N;
    scanf("%s%s",s+1,t+1);
    n=strlen(s+1);m=strlen(t+1);
    falun_dafa_is_good(s,f,n);
    falun_dafa_is_good(t,g,m);
    int ans=0,pf=n&1,pg=m&1,lim=min(n,m);
    for(int i=m;i>=-n;i--) gs[i]=add(gs[i+1],add(g[pg][0][i],g[pg][1][i]));
    for(int i=-n;i<=n;i++) ans=(ans+1ll*(f[pf][0][i]+f[pf][1][i])*gs[1-i])%ha;
    for(int i=-lim;i<=lim;i++) ans=(ans+(long long)f[pf][1][i]*g[pg][1][-i])%ha;
    printf("%d\n",ans);
    return 0;
}
