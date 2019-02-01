#include<bits/stdc++.h>
using namespace std;

const int N=50010;
struct Query{int l,r,t,id;} qry[N];
struct Change{int t,p,pre,aft;} chg[N];
int n,m,col[N],q,cg,sz;
int cnt[1000010],ans=0,l,r,t;
int res[N];

bool operator < (const Query &a,const Query &b)
{
    if(a.l/sz!=b.l/sz) return a.l/sz<b.l/sz;
    if(a.r/sz!=b.r/sz) return a.r/sz<b.r/sz;
    return ((a.r/sz)&1)?a.t<b.t:a.t>b.t;
}

inline void del(int x){if((--cnt[x])==0) ans--;}
inline void ins(int x){if((++cnt[x])==1) ans++;}

void change(int x,bool d)
{
    int p=chg[x].p;
    if(p<l||p>r)
    {
        col[p]=d?chg[x].aft:chg[x].pre;
        return;
    }
    del(col[p]);
    col[p]=d?chg[x].aft:chg[x].pre;
    ins(col[p]);
}

int main()
{
    scanf("%d%d",&n,&m);
    sz=max(pow(n,2.0/3.0),1.0);
    for(int i=1;i<=n;i++) scanf("%d",col+i);
    for(int i=1;i<=m;i++)
    {
        static char opt[5];
        scanf("%s",opt);
        if(opt[0]=='Q')
        {
            int l,r;
            scanf("%d%d",&l,&r);
            qry[++q]={l,r,i};
            qry[q].id=q;
        }
        else
        {
            int p,c;
            scanf("%d%d",&p,&c);
            chg[++cg].p=p;
            chg[cg].t=i;
            chg[cg].pre=col[p];
            chg[cg].aft=col[p]=c;
        }
    }
    sort(qry+1,qry+1+q);l=1,r=0,t=cg;
    for(int i=1;i<=q;i++)
    {
        while(t<cg&&chg[t].t<qry[i].t) change(++t,1);
        while(chg[t].t>qry[i].t) change(t--,0);
        while(l<qry[i].l) del(col[l++]);
        while(l>qry[i].l) ins(col[--l]);
        while(r<qry[i].r) ins(col[++r]);
        while(r>qry[i].r) del(col[r--]);
        res[qry[i].id]=ans;
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",res[i]);
    return 0;
}