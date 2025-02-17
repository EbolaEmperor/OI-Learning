#include<bits/stdc++.h>
using namespace std;

const int N=2100;
char t[N];
int n,m,pre[N][N],prec[N][N],ansp;
int ch[N][10],fail[N],pos[N],cnt[N],tot=0;
double val[N];

void insert(char *s,double v)
{
    int o=0,len=strlen(s);
    for(int i=0;i<len;i++)
    {
        int j=s[i]-'0';
        if(!ch[o][j]) ch[o][j]=++tot;
        o=ch[o][j];
    }
    cnt[o]++;
    val[o]+=v;
}

void getfail()
{
    queue<int> q;
    for(int c=0;c<10;c++)
        if(ch[0][c]) q.push(ch[0][c]);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        cnt[u]+=cnt[fail[u]];
        val[u]+=val[fail[u]];
        for(int c=0;c<10;c++)
        {
            int v=ch[u][c];
            if(!v) ch[u][c]=ch[fail[u]][c];
            else fail[v]=ch[fail[u]][c],q.push(v);
        }
    }
}

bool check(double x)
{
    double lgx=log(x);
    static double f[N][N];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=tot;j++)
            f[i][j]=-1e18;
    f[0][0]=0.0;
    for(int i=0;i<n;i++)
        if(t[i]=='.')
        {
            for(int j=0;j<=tot;j++)
                if(f[i][j]>-1e8)for(int c=0;c<10;c++)
                {
                    int u=ch[j][c];
                    double tmp=f[i][j]+val[u]-lgx*cnt[u];
                    if(tmp>f[i+1][u]) f[i+1][u]=tmp;
                }
        }
        else
        {
            int c=t[i]-'0';
            for(int j=0;j<=tot;j++)
                if(f[i][j]>-1e8)
                {
                    int u=ch[j][c];
                    double tmp=f[i][j]+val[u]-lgx*cnt[u];
                    if(tmp>f[i+1][u]) f[i+1][u]=tmp;
                }
        }
    double mx=-1e18;
    for(int i=0;i<=tot;i++)
        if(f[n][i]>mx) mx=f[n][i],ansp=i;
    return mx>0;
}

void gao(double x)
{
    double lgx=log(x);
    static double f[N][N];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=tot;j++)
            f[i][j]=-1e18;
    f[0][0]=0.0;
    for(int i=0;i<n;i++)
        if(t[i]=='.')
        {
            for(int j=0;j<=tot;j++)
                for(int c=0;c<10;c++)
                {
                    int u=ch[j][c];
                    double tmp=f[i][j]+val[u]-lgx*cnt[u];
                    if(tmp>f[i+1][u])
                    {
                        f[i+1][u]=tmp;
                        pre[i+1][u]=j;
                        prec[i+1][u]=c;
                    }
                }
        }
        else
        {
            int c=t[i]-'0';
            for(int j=0;j<=tot;j++)
            {
                int u=ch[j][c];
                double tmp=f[i][j]+val[u]-lgx*cnt[u];
                if(tmp>f[i+1][u])
                {
                    f[i+1][u]=tmp;
                    pre[i+1][u]=j;
                    prec[i+1][u]=c;
                }
            }
        }
    double mx=-1e18;
    for(int i=0;i<=tot;i++)
        if(f[n][i]>mx) mx=f[n][i],ansp=i;
}

void print(int p,int d)
{
    if(d==0) return;
    print(pre[d][p],d-1);
    printf("%d",prec[d][p]);
}

int main()
{
    scanf("%d%d%s",&n,&m,t);
    for(int i=0;i<m;i++)
    {
        static char s[N];
        static double v;
        scanf("%s%lf",s,&v);
        insert(s,log(v));
    }
    getfail();
    double l=1,r=1e9,mid;
    for(int i=1;i<=35;i++)
    {
        mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    gao(l);
    print(ansp,n);
    return 0;
}
