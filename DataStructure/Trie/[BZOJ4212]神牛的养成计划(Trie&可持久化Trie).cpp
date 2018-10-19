#include<bits/stdc++.h>
using namespace std;

const int N=2200010,M=2010;
int dfn[N],idx[N],dfc=0,n,m;
int in[N],out[N];
char *s[M],ss[N];

namespace Trie1
{
    int ch[N][26],val[N],root=0,tot=0;
    void insert(int &o,char* s,int d,int x)
    {
        if(!o) o=++tot;
        if(!d){val[o]=x;return;}
        insert(ch[o][(*s)-'a'],s+1,d-1,x);
    }
    int query(int o,char* s,int d)
    {
        if(!d) return o;
        return query(ch[o][(*s)-'a'],s+1,d-1);
    }
    void dfs(int o)
    {
        in[o]=dfc+1;
        if(val[o]) idx[dfn[val[o]]=++dfc]=val[o];
        for(int i=0;i<26;i++)if(ch[o][i])dfs(ch[o][i]);
        out[o]=dfc;
    }
}

namespace Trie2
{
    int rt[M],ch[N][26],val[N],tot=0;
    void insert(int &o,int p,char* s,int d)
    {
        val[o=++tot]=val[p]+1;
        memcpy(ch[o],ch[p],sizeof(ch[o]));
        if(!d) return;
        insert(ch[o][(*s)-'a'],ch[p][(*s)-'a'],s+1,d-1);
    }
    int query(int L,int R,char* s,int d)
    {
        if(!d) return val[R]-val[L];
        return query(ch[L][(*s)-'a'],ch[R][(*s)-'a'],s+1,d-1);
    }
}

using Trie1::root;
using Trie2::rt;

int main()
{
    int ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss);
        int len=strlen(ss);
        s[i]=new char[len+1];
        sprintf(s[i],ss);
        Trie1::insert(root,s[i],len,i);
        reverse(s[i],s[i]+len);
    }
    Trie1::dfs(root);
    for(int i=1;i<=n;i++)
        Trie2::insert(rt[i],rt[i-1],s[idx[i]],strlen(s[idx[i]]));
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ss);
        int len=strlen(ss);
        for(int i=0;i<len;i++) ss[i]=(ss[i]-'a'+ans)%26+'a';
        int x=Trie1::query(root,ss,len);
        scanf("%s",ss);
        len=strlen(ss);
        reverse(ss,ss+len);
        for(int i=0;i<len;i++) ss[i]=(ss[i]-'a'+ans)%26+'a';
        ans=Trie2::query(rt[in[x]-1],rt[out[x]],ss,len);
        printf("%d\n",ans);
    }
    return 0;
}