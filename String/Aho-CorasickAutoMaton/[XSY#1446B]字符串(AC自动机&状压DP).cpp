#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=1410;
int ch[N][2],fail[N],tot=0;
int stu[N],fa[N],fav[N];
int f[2][N][70],n,m,k;
char s[110];
bool vis[N];

inline void add(int &x,const int &y){x=x+y>=ha?x+y-ha:x+y;}

void insert(int st)
{
    int len=strlen(s),p=0;
    for(int i=0;i<len;i++)
    {
        int c=s[i]-'0';
        if(!ch[p][c])
        {
            ch[p][c]=++tot;
            fa[tot]=p;
            fav[tot]=c;
        }
        p=ch[p][c];
    }
    stu[p]|=st;
}

void build()
{
    queue<int> q;
    q.push(0);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        stu[u]|=stu[fail[u]];vis[u]=1;
        for(int i=0;i<2;i++)
        {
            int v=ch[u][i];
            if(!v) ch[u][i]=ch[fail[u]][i];
            else
            {
                if(u) fail[v]=ch[fail[u]][i];
                if(!vis[v]) q.push(v);
            }
        }
    }
}

int rstu(int x)
{
    int res=0;
    for(int y=x;y;y=fa[y])
    {
        x=ch[x][fav[y]^1];
        res|=stu[x];
    }
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%s",s);
        insert(1<<i);
        int l=strlen(s);
        reverse(s,s+l);
        for(int j=0;j<l;j++)
            s[j]=((s[j]-'0')^1)+'0';
        insert(1<<i);
    }
    build();f[0][0][0]=1;
    for(int i=1;i<=m;i++,k^=1)
    {
        memset(f[k^1],0,sizeof(f[k^1]));
        for(int u=0;u<=tot;u++)
            for(int st=0;st<1<<n;st++)
                for(int c=0;c<2;c++)
                {
                    int v=ch[u][c];
                    add(f[k^1][v][st|stu[v]],f[k][u][st]);
                }
    }
    int ans=0;
    for(int u=0;u<=tot;u++)
    {
        int t=rstu(u);
        for(int st=0;st<1<<n;st++)
            if((st|t)==(1<<n)-1) add(ans,f[k][u][st]);
    }
    printf("%d\n",ans);
    return 0;
}