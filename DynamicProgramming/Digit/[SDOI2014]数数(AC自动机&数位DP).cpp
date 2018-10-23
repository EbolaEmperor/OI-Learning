#include<bits/stdc++.h>
using namespace std;

const int N=1510;
const int ha=1000000007;
int ch[N][10],fail[N],tot=0;
int f[2][N][2],m,nlen;
bool fuck[N];
char n[N];

void insert(char* _begin,char* _end)
{
    int o=0;
    for(;_begin!=_end;_begin++)
    {
        int t=*_begin-'0';
        if(!ch[o][t]) ch[o][t]=++tot;
        o=ch[o][t];
    }
    fuck[o]=1;
}

void getfail()
{
    queue<int> q;q.push(0);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        fuck[u]|=fuck[fail[u]];
        for(int i=0;i<10;i++)
            if(ch[u][i])
            {
                if(u) fail[ch[u][i]]=ch[fail[u]][i];
                q.push(ch[u][i]);
            }
            else ch[u][i]=ch[fail[u]][i];
    }
}

inline void add(int &x,const int &y){x=(x+y>=ha)?x+y-ha:x+y;}

int xi_jin_ping_is_good()
{
    int ans=0,k=0;
    for(int i=1;i<n[0]-'0';i++)
        add(f[k][ch[0][i]][0],1);
    add(f[k][ch[0][n[0]-'0']][1],1);
    for(int i=1;i<nlen;i++,k^=1)
    {
        memset(f[k^1],0,sizeof(f[k^1]));
        for(int j=1;j<10;j++)
            add(f[k^1][ch[0][j]][0],1);
        for(int p=0;p<=tot;p++)
        {
            if(fuck[p]) continue;
            if(f[k][p][0])for(int j=0;j<10;j++)
            {
                if(fuck[ch[p][j]]) continue;
                add(f[k^1][ch[p][j]][0],f[k][p][0]);
            }
            if(f[k][p][1])for(int j=0;j<n[i]-'0';j++)
            {
                if(fuck[ch[p][j]]) continue;
                add(f[k^1][ch[p][j]][0],f[k][p][1]);
            }
            if(fuck[ch[p][n[i]-'0']]) continue;
            add(f[k^1][ch[p][n[i]-'0']][1],f[k][p][1]);
        }
    }
    for(int i=0;i<=tot;i++)
    {
        if(fuck[i]) continue;
        add(ans,f[k][i][0]);
        add(ans,f[k][i][1]);
    }
    return ans;
}

int main()
{
    char s[N];
    scanf("%s%d",n,&m);
    nlen=strlen(n);
    for(int i=0;i<m;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        insert(s,s+len);
    }
    getfail();
    int ans=xi_jin_ping_is_good();
    printf("%d\n",ans);
    return 0;
}