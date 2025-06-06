#include<bits/stdc++.h>
using namespace std;

const int S=(1<<24)+5;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
inline void prints(const char *s)
{
    int len=strlen(s);
    for(int i=0;i<len;i++) putc(s[i]);
    putc('\n');
}

const int ha=1e9+7;
const int N=4500010;
int ch[N][4],prt[N],len[N];
int lst=0,tot=0,rt;
char s[N],ans[N];
int n,k,nxt[N];

void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int idx(char c)
{
    if(c=='A') return 0;
    if(c=='C') return 1;
    if(c=='G') return 2;
    if(c=='T') return 3;
}

char chr(int c)
{
    if(c==0) return 'A';
    if(c==1) return 'C';
    if(c==2) return 'G';
    if(c==3) return 'T';
}

void insert(int c)
{
    int p=lst,np=++tot;len[np]=len[p]+1;
    while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
    if(!p) prt[np]=rt;
    else
    {
        int q=ch[p][c];
        if(len[p]+1==len[q]) prt[np]=q;
        else
        {
            int nq=++tot;len[nq]=len[p]+1;
            memcpy(ch[nq],ch[q],sizeof(ch[nq]));
            prt[nq]=prt[q];prt[q]=prt[np]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
        }
    }
    lst=np;
}

void dfs(int u,int d)
{
    if(!u) return;
    ans[d]='\0';prints(ans);
    for(int i=0;i<4;i++)
        ans[d]=chr(i),dfs(ch[u][i],d+1);
}

int getcnt()
{
    static int f[N],deg[N];
    for(int i=1;i<=tot;i++)
        for(int j=0;j<4;j++)
            if(ch[i][j]) deg[ch[i][j]]++;
    int ans=0;
    queue<int> q;f[1]=1;
    for(int i=1;i<=tot;i++)
        if(!deg[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        add(ans,f[u]);
        for(int i=0;i<4;i++)
        {
            int v=ch[u][i];
            if(!v) continue;
            add(f[v],f[u]);
            if(!--deg[v]) q.push(v);
        }
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        rt=lst=++tot;
        for(int j=0;j<len;j++) insert(idx(s[j]));
        for(int j=rt;j<=tot;j++) nxt[j]=tot+1;
    }
    for(int i=tot;i>=1;i--)
        for(int j=0;j<4;j++)
            if(!ch[i][j]) ch[i][j]=ch[nxt[i]][j];
    scanf("%d",&k);
    if(k==1) dfs(1,0),flush();
    printf("%d\n",getcnt());
    return 0;
}