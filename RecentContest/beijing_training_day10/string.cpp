#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int ch[N][2],fa[N],val[N],tag[N];
int chs[N][26],prt[N],len[N];
int tot=1,lst=1;
struct Qry{int l,id;};
vector<Qry> q[N];
char s[N];
int n,m,ans[N];

// --------- Segment Tree ---------
struct SegmentTree
{
    int mx[N<<2],tag[N<<2];
    void update(int o,int l,int r,int nl,int nr,int x)
    {
        if(l>=nl&&r<=nr)
        {
            mx[o]=max(mx[o],x);
            tag[o]=max(tag[o],x);
            return;
        }
        int mid=(l+r)/2;
        if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
        if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
        mx[o]=max(max(mx[o<<1],mx[o<<1|1]),tag[o]);
    }
    int query(int o,int l,int r,int k)
    {
        if(l==r) return mx[o];
        int mid=(l+r)/2,res=tag[o];
        if(k<=mid) res=max(res,query(o<<1,l,mid,k));
        else res=max(res,query(o<<1|1,mid+1,r,k));
        return res;
    }
} t1,t2;

// --------- Link-Cut Tree ---------
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void push(int x,int v){val[x]=tag[x]=v;}
void pushdown(int x)
{
    if(tag[x])
    {
        if(ch[x][0]) push(ch[x][0],tag[x]);
        if(ch[x][1]) push(ch[x][1],tag[x]);
        tag[x]=0;
    }
}
void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nroot(y)) ch[z][ch[z][1]==y]=x;
    ch[y][k]=w;ch[x][k^1]=y;
    fa[y]=x;fa[x]=z;
    if(w) fa[w]=y;
}
void splay(int x)
{
    static int stk[N],top=0;
    int y=x,z;
    while(nroot(y)) stk[++top]=y,y=fa[y];
    pushdown(y);
    while(top) pushdown(stk[top--]);
    while(nroot(x))
    {
        y=fa[x];z=fa[y];
        if(nroot(y))
            rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
}
void access(int x,int r)
{
    int y=0;
    for(;x;y=x,x=fa[x])
    {
        splay(x);
        ch[x][1]=y;
        if(x!=1&&val[x])
        {
            t1.update(1,1,n,1,val[x]-len[x]+1,len[x]);
            if(len[x]>1) t2.update(1,1,n,val[x]-len[x]+2,val[x],val[x]);
        }
    }
    push(y,r);
}
void change(int x,int y){splay(x);val[y]=val[x];}

// --------- Suffix Automaton ---------
void insert(int c,int r)
{
    int p=lst,np=++tot;len[np]=len[p]+1;
    while(p&&!chs[p][c]) chs[p][c]=np,p=prt[p];
    if(!p) prt[np]=fa[np]=1,access(np,r);
    else
    {
        int q=chs[p][c];
        if(len[q]==len[p]+1) prt[np]=fa[np]=q,access(np,r);
        else
        {
            int nq=++tot;len[nq]=len[p]+1;
            memcpy(chs[nq],chs[q],sizeof(chs[nq]));
            change(q,nq);
            prt[nq]=fa[nq]=prt[q];
            prt[np]=fa[np]=nq;
            access(np,r);splay(q);
            prt[q]=fa[q]=nq;
            while(chs[p][c]==q) chs[p][c]=nq,p=prt[p];
        }
    }
    lst=np;
}

// --------- Main ---------
int query(int l,int r)
{
    int res1=t1.query(1,1,n,l);
    int res2=t2.query(1,1,n,l);
    return max(res1,res2-l+1);
}

int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1,l,r;i<=m;i++)
        scanf("%d%d",&l,&r),q[r].push_back({l,i});
    for(int i=1;i<=n;i++)
    {
        insert(s[i]-'a',i);
        for(auto p : q[i])
            ans[p.id]=query(p.l,i);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
