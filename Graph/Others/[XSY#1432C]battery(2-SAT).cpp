#include<bits/stdc++.h>
using namespace std;

const int VERTI=0,HORIZ=1;
const int UP=0,DOWN=1,LEFT=2,RIGHT=3;
typedef pair<int,int> pii;
const int N=60,M=10010;
struct Edge{int to,next;} e[M<<2];
int h[M],esum,st;
vector<pii> p[N][N];
bool vis[M],inq[N][N],cant[M];
stack<int> path;
char s[N][N];
int T,n,m;

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

inline int idx(int x,int y){return (x-1)*m+y;}
inline int no(int x){return (x&1)?(x+1):(x-1);}
inline bool outgrid(int x,int y){return x<1||x>n||y<1||y>m;}

void turn1(int &x)
{
    if(x==UP) x=RIGHT;
    else if(x==DOWN) x=LEFT;
    else if(x==LEFT) x=DOWN;
    else if(x==RIGHT) x=UP;
}

void turn2(int &x)
{
    if(x==UP) x=LEFT;
    else if(x==DOWN) x=RIGHT;
    else if(x==LEFT) x=UP;
    else if(x==RIGHT) x=DOWN;
}

void gogogo(int &x,int &y,const int &dr)
{
    if(dr==UP) x--;
    if(dr==DOWN) x++;
    if(dr==LEFT) y--;
    if(dr==RIGHT) y++;
}

bool trans(int &tx,int &ty,int &dr,vector<pii> &rcb)
{
    while(1)
    {
        if(outgrid(tx,ty)) break;
        if(s[tx][ty]=='#') break;
        if(s[tx][ty]=='|'||s[tx][ty]=='-') return 0;
        if(s[tx][ty]=='/') turn1(dr);
        if(s[tx][ty]=='\\') turn2(dr);
        if(s[tx][ty]=='.'&&!inq[tx][ty]) rcb.push_back(pii(tx,ty)),inq[tx][ty]=1;
        gogogo(tx,ty,dr);
    }
    return 1;
}

void gao_verti(int x,int y)
{
    int tx=x-1,ty=y,dr=UP;
    vector<pii> rcb;
    if(!trans(tx,ty,dr,rcb))
    {
        cant[idx(x,y)*2-VERTI]=1;
        for(pii pp : rcb) inq[pp.first][pp.second]=0;
        return;
    }
    tx=x+1,ty=y,dr=DOWN;
    if(!trans(tx,ty,dr,rcb))
    {
        cant[idx(x,y)*2-VERTI]=1;
        for(pii pp : rcb) inq[pp.first][pp.second]=0;
        return;
    }
    for(pii pp : rcb) p[pp.first][pp.second].push_back(pii(idx(x,y),VERTI));
    for(pii pp : rcb) inq[pp.first][pp.second]=0;
}

void gao_horiz(int x,int y)
{
    int tx=x,ty=y-1,dr=LEFT;
    vector<pii> rcb;
    if(!trans(tx,ty,dr,rcb))
    {
        cant[idx(x,y)*2-HORIZ]=1;
        for(pii pp : rcb) inq[pp.first][pp.second]=0;
        return;
    }
    tx=x,ty=y+1,dr=RIGHT;
    if(!trans(tx,ty,dr,rcb))
    {
        cant[idx(x,y)*2-HORIZ]=1;
        for(pii pp : rcb) inq[pp.first][pp.second]=0;
        return;
    }
    for(pii pp : rcb) p[pp.first][pp.second].push_back(pii(idx(x,y),HORIZ));
    for(pii pp : rcb) inq[pp.first][pp.second]=0;
}

bool dfs(int u)
{
    if(vis[u]) return 1;
    if(vis[no(u)]) return 0;
    if(cant[u]) return 0;
    vis[u]=1;path.push(u);
    for(int t=h[u];t;t=e[t].next)
        if(!dfs(e[t].to)) return 0;
    return 1;
}

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        fflush(stdout);
        scanf("%d%d",&n,&m);
        st=n*m*2+1;esum=0;
        memset(h,0,sizeof(h));
        memset(cant,0,sizeof(cant));
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]+1);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                p[i][j].clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(s[i][j]!='|'&&s[i][j]!='-') continue;
                gao_verti(i,j);gao_horiz(i,j);
            }
        bool falun=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(s[i][j]!='.') continue;
                if(p[i][j].empty()){falun=0;break;}
                if(p[i][j].size()==1) add_edge(st,p[i][j][0].first*2-p[i][j][0].second);
                else
                {
                    pii p1=p[i][j][0],p2=p[i][j][1];
                    if(p1.first==p2.first) continue;
                    add_edge(p1.first*2-(p1.second^1),p2.first*2-p2.second);
                    add_edge(p2.first*2-(p2.second^1),p1.first*2-p1.second);
                }
            }
            if(!falun) break;
        }
        if(!falun){puts("IMPOSSIBLE");continue;}
        memset(vis,0,sizeof(vis));
        while(!path.empty()) path.pop();
        if(!dfs(st)){puts("IMPOSSIBLE");continue;}
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(s[i][j]!='|'&&s[i][j]!='-') continue;
                while(!path.empty()) path.pop();
                if(dfs(idx(i,j)*2-VERTI)) continue;
                while(!path.empty()) vis[path.top()]=0,path.pop();
                if(dfs(idx(i,j)*2-HORIZ)) continue;
                falun=0;break;
            }
            if(!falun) break;
        }
        if(!falun){puts("IMPOSSIBLE");continue;}
        puts("POSSIBLE");
        for(int i=1;i<=n;i++,puts(""))
            for(int j=1;j<=m;j++)
            {
                if(s[i][j]!='|'&&s[i][j]!='-') putchar(s[i][j]);
                else if(vis[idx(i,j)*2-VERTI]) putchar('|');
                else putchar('-');
            }
    }
    return 0;
}