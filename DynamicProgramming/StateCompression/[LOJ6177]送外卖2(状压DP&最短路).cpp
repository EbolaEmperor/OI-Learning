#include<bits/stdc++.h>
using namespace std;

const int N=23,Q=11;
const int INF=0x3f3f3f3f;
int dis[N][N],n,m,q,ans=0;
int s[Q],t[Q],l[Q],r[Q];
int f[N][60000],pw3[Q];

inline void upmin(int &x,const int &y){if(y<x) x=y;}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        upmin(dis[u][v],w);
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                upmin(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=q;i++)
        scanf("%d%d%d%d",s+i,t+i,l+i,r+i);
    memset(f,0x3f,sizeof(f));
    f[1][0]=0;pw3[0]=1;
    for(int i=1;i<=q;i++)
        pw3[i]=pw3[i-1]*3;
    for(int stu=0;stu<pw3[q];stu++)
        for(int i=1;i<=n;i++)
        {
            if(f[i][stu]==INF) continue;
            int cnt=0;
            for(int j=1;j<=q;j++)
            {
                int cur=stu/pw3[j-1]%3;
                if(cur==0) upmin(f[s[j]][stu+pw3[j-1]],max(f[i][stu]+dis[i][s[j]],l[j]));
                if(cur==1&&f[i][stu]+dis[i][t[j]]<=r[j]) upmin(f[t[j]][stu+pw3[j-1]],f[i][stu]+dis[i][t[j]]);
                if(cur==2) cnt++;
            }
            ans=max(ans,cnt);
        }
    printf("%d\n",ans);
    return 0;
}