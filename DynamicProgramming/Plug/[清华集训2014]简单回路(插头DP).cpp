#include<bits/stdc++.h>
using namespace std;

const int ha=1000000007;
const int N=1010,M=310,S=5500;
int Hash[S],val[M],tot=0;
int n,m,k,bin[9],bb[9];
int match[M][9];
bool obs[N][9];
int f[N][9][M];
int g1[N][M],g2[N][M];
int cnt[M],a[M][M];
int b1[9],b2[9];
bool vis[2][9];

void gao(int stu)
{
    int sum=0;
    for(int i=0;i<=m;i++)
    {
        if(bb[i]==1) sum++;
        if(bb[i]==2) sum--;
        if(sum<0) return;
    }
    if(sum) return;
    val[Hash[stu]=++tot]=stu;
    int stk[9],top=0;
    for(int i=0;i<=m;i++)
    {
        if(bb[i]==1) stk[++top]=i;
        if(bb[i]==2) match[tot][i]=stk[top--];
    }
    for(int i=m;i>=0;i--)
    {
        if(bb[i]==2) stk[++top]=i;
        if(bb[i]==1) match[tot][i]=stk[top--];
    }
}

void prework(int p,int cur)
{
    if(p>m){gao(cur);return;}
    bb[p]=0;prework(p+1,cur);
    bb[p]=1;prework(p+1,cur+bin[p]);
    bb[p]=2;prework(p+1,cur+bin[p]*2);
}

inline void Add(int &x,const int &y){x=(x+y)>=ha?x+y-ha:x+y;}

void PlugDP()
{
    memset(f,0,sizeof(f));
    f[0][m][1]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=tot;j++)
            if(val[j]%3==0) f[i][0][j]=f[i-1][m][Hash[val[j]/3]];
        for(int j=1;j<=m;j++)
            for(int k=1;k<=tot;k++)
            {
                if(!f[i][j-1][k]) continue;
                int s=val[k];
                int plug1=s/bin[j-1]%3;
                int plug2=s/bin[j]%3;
                int other=s-plug1*bin[j-1]-plug2*bin[j];
                int p=max(plug1,plug2);
                if(obs[i][j])
                {
                    if(!plug1&&!plug2)
                        Add(f[i][j][k],f[i][j-1][k]);
                    continue;
                }
                if(!plug1&&!plug2)
                {
                    Add(f[i][j][k],f[i][j-1][k]);
                    int t=Hash[s+bin[j-1]+2*bin[j]];
                    Add(f[i][j][t],f[i][j-1][k]);
                }
                else if(!plug1||!plug2)
                {
                    Add(f[i][j][Hash[other+p*bin[j-1]]],f[i][j-1][k]);
                    Add(f[i][j][Hash[other+p*bin[j]]],f[i][j-1][k]);
                }
                else
                {
                    if(plug1==2&&plug2==1) Add(f[i][j][Hash[other]],f[i][j-1][k]);
                    if(plug1==1&&plug2==1) Add(f[i][j][Hash[other-bin[match[k][j]]]],f[i][j-1][k]);
                    if(plug1==2&&plug2==2) Add(f[i][j][Hash[other+bin[match[k][j-1]]]],f[i][j-1][k]);
                }
            }
    }
}

bool check(int x,int y)
{
    int sx=val[x],sy=val[y];
    if(sx%3||sy%3) return 0;
    for(int k=1;k<=m;k++)
    {
        if((sx/bin[k]%3==0)&&(sy/bin[k]%3>0)) return 0;
        if((sx/bin[k]%3>0)&&(sy/bin[k]%3==0)) return 0;
    }
    for(int k=1;k<=m;k++) b1[k]=sx/bin[k]%3;
    for(int k=1;k<=m;k++) b2[k]=sy/bin[k]%3;
    memset(vis,0,sizeof(vis));int sum=0;
    for(int k=1;k<=m;k++)
    {
        if(!b1[k]||vis[0][k]) continue;
        sum++;vis[0][k]=1;
        int p=0,mt=match[x][k];
        while(!vis[p][mt])
        {
            vis[p][mt]=1;
            if(!p)
            {
                if(!vis[0][match[x][mt]])
                    mt=match[x][mt];
                else p=1;
            }
            else
            {
                if(!vis[1][match[y][mt]])
                    mt=match[y][mt];
                else p=0;
            }
        }
    }
    return sum==1;
}

int main()
{
    int x,y,Q;
    scanf("%d%d%d",&n,&m,&k);
    bin[0]=1;
    for(int i=1;i<=8;i++)
        bin[i]=bin[i-1]*3;
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&x,&y);
        obs[x][y]=1;
    }
    prework(0,0);
    PlugDP();
    for(int i=1;i<n;i++)
        for(int j=1;j<=tot;j++)
            g1[i][j]=f[i+1][0][j];
    for(int i=1;i<=n/2;i++)
        for(int j=1;j<=m;j++)
            swap(obs[i][j],obs[n-i+1][j]);
    PlugDP();
    for(int i=1;i<n;i++)
        for(int j=1;j<=tot;j++)
            g2[i][j]=f[n-i+1][0][j];
    for(int i=1;i<=tot;i++)
    {
        cnt[i]=0;
        for(int j=1;j<=tot;j++)
            if(check(i,j)) a[i][++cnt[i]]=j;
    }
    for(scanf("%d",&Q);Q;Q--)
    {
        scanf("%d%d",&x,&y);
        int ans=0;
        for(int i=1;i<=tot;i++)
        {
            if(val[i]/bin[y]%3==0) continue;
            for(int j=1;j<=cnt[i];j++)
                ans=(ans+1ll*g1[x][i]*g2[x][a[i][j]])%ha;
        }
        printf("%d\n",ans);
    }
    return 0;
}