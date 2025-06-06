#include<bits/stdc++.h>
using namespace std;

const int N=2000010;
vector<int> g[N],nodes[N];
int ch[N][26],len[N],prt[N],pr[N];
int jmp[20][N],lst=1,tot=1,val[N];
int n,m,na,nb,a[N],b[N],deg[N],vis[N];
long long f[N];
int alen[N],blen[N];
char s[N];

void insert(int c,int k)
{
    int p=lst,np=++tot;len[np]=len[p]+1;
    while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
    if(!p) prt[np]=1;
    else
    {
        int q=ch[p][c];
        if(len[p]+1==len[q]) prt[np]=q;
        else
        {
            int nq=++tot;len[nq]=len[p]+1;
            memcpy(ch[nq],ch[q],sizeof(ch[nq]));
            prt[nq]=prt[q];prt[np]=prt[q]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
        }
    }
    pr[k]=lst=np;
}

void build_jump()
{
    for(int i=1;i<=tot;i++)
        jmp[0][i]=prt[i];
    for(int k=1;k<=18;k++)
        for(int i=1;i<=tot;i++)
            jmp[k][i]=jmp[k-1][jmp[k-1][i]];
}

int getnode(int l,int r)
{
    int u=pr[r];
    for(int k=18;k>=0;k--)
        if(len[jmp[k][u]]>=r-l+1) u=jmp[k][u];
    return u;
}

void build_graph()
{
    int pktot=tot;
    for(int i=1;i<=pktot;i++)
    {
        sort(nodes[i].begin(),nodes[i].end(),[](int a,int b){return (a>0?alen[a]:blen[-a])>(b>0?alen[b]:blen[-b]);});
        int cur=i;
        for(int x : nodes[i])
        {
            int xlen=(x>0)?alen[x]:blen[-x];
            if(xlen<len[cur])
            {
                int pre=cur;cur=++tot;
                prt[cur]=prt[pre];
                prt[pre]=cur;
                len[cur]=xlen;
            }
            if(x>0) g[cur].push_back(a[x]=++tot),deg[a[x]]++;
            else b[-x]=cur;
        }
        nodes[i].clear();
    }
    for(int i=2;i<=tot;i++)
        if(prt[i]) g[prt[i]].push_back(i),deg[i]++;
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        g[a[x]].push_back(b[y]);
        deg[b[y]]++;
    }
    for(int i=1;i<=na;i++) val[a[i]]=alen[i];
}

long long topo()
{
    queue<int> q;
    long long ans=0;
    for(int i=1;i<=tot;i++)
        if(!deg[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=1;f[u]+=val[u];
        ans=max(ans,f[u]);
        for(int v : g[u])
        {
            f[v]=max(f[v],f[u]);
            if(!--deg[v]) q.push(v);
        }
    }
    for(int i=1;i<=tot;i++)
        if(!vis[i]) return -1;
    return ans;
}

void clear()
{
    memset(pr,0,sizeof(int)*(n+1));
    memset(val,0,sizeof(int)*(tot+1));
    memset(len,0,sizeof(int)*(tot+1));
    memset(prt,0,sizeof(int)*(tot+1));
    memset(deg,0,sizeof(int)*(tot+1));
    memset(vis,0,sizeof(int)*(tot+1));
    memset(f,0,sizeof(long long)*(tot+1));
    for(int i=0;i<=tot;i++)
        g[i].clear(),memset(ch[i],0,sizeof(ch[i]));
    lst=tot=1;
}

void _main_()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    reverse(s+1,s+1+n);
    for(int i=1;i<=n;i++)
        insert(s[i]-'a',i);
    build_jump();
    scanf("%d",&na);
    for(int i=1,l,r;i<=na;i++)
    {
        scanf("%d%d",&l,&r);
        if(l>r) continue;
        l=n-l+1;r=n-r+1;
        alen[i]=l-r+1;
        nodes[getnode(r,l)].push_back(i);
    }
    scanf("%d",&nb);
    for(int i=1,l,r;i<=nb;i++)
    {
        scanf("%d%d",&l,&r);
        if(l>r) continue;
        l=n-l+1;r=n-r+1;
        blen[i]=l-r+1;
        nodes[getnode(r,l)].push_back(-i);
    }
    build_graph();
    printf("%lld\n",topo());
    clear();
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--) _main_();
    return 0;
}