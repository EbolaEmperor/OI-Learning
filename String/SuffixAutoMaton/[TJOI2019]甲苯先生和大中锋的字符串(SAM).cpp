#include<bits/stdc++.h>
using namespace std;

const int N=200010;
vector<int> g[N];
int ch[N][26],prt[N],len[N],cnt[N];
int tot=1,lst=1;
char s[N];
int qwq,n,k,c[N];

void insert(int c)
{
    int p=lst,np=++tot;
    len[np]=len[p]+1;
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
            prt[nq]=prt[q];prt[q]=prt[np]=nq;
            while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
        }
    }
    cnt[np]++;
    lst=np;
}

void dfs(int u)
{
    for(int v : g[u])
        dfs(v),cnt[u]+=cnt[v];
    if(cnt[u]!=k) return;
    c[len[prt[u]]+1]++;
    c[len[u]+1]--;
}

int main()
{
    scanf("%d",&qwq);
    while(qwq--)
    {
        scanf("%s%d",s+1,&k);
        n=strlen(s+1);
        for(int i=1;i<=n;i++)
            insert(s[i]-'a');
        for(int i=2;i<=tot;i++)
            g[prt[i]].push_back(i);
        dfs(1);
        int mx=1,ans=-1;
        for(int i=1;i<=n;i++)
            if((c[i]+=c[i-1])>=mx) mx=c[i],ans=i;
        printf("%d\n",ans);
        for(int i=1;i<=tot;i++)
        {
            memset(ch[i],0,sizeof(ch[i]));
            len[i]=cnt[i]=prt[i]=0;
            g[i].clear();
        }
        lst=tot=1;
        memset(c,0,sizeof(int)*(n+1));
    }
    return 0;
}