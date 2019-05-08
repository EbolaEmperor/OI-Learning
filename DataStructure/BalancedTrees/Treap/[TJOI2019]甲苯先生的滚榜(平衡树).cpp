#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=1000010;
struct{int lc,rc,sz,cnt,rnd,ac,tme;} tr[N];
int m,n,ac[N],tme[N],rt,tot;

unsigned seed,last=7;
unsigned read(){return (seed=seed*17+last)%m+1;}

inline void maintain(int x){tr[x].sz=tr[tr[x].lc].sz+tr[tr[x].rc].sz+tr[x].cnt;}
inline int newnode(int ac,int tme){tr[++tot]={0,0,1,1,rand(),ac,tme};return tot;}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    if(tr[x].rnd<tr[y].rnd)
    {
        tr[x].rc=merge(tr[x].rc,y);
        maintain(x);
        return x;
    }
    else
    {
        tr[y].lc=merge(x,tr[y].lc);
        maintain(y);
        return y;
    }
}

pii split(int x,int ac,int tme)
{
    if(!x) return pii(0,0);
    if(tr[x].ac>ac||tr[x].ac==ac&&tr[x].tme<tme)
    {
        pii t=split(tr[x].rc,ac,tme);
        tr[x].rc=t.first;
        maintain(x);
        return pii(x,t.second);
    }
    else
    {
        pii t=split(tr[x].lc,ac,tme);
        tr[x].lc=t.second;
        maintain(x);
        return pii(t.first,x);
    }
}

void remove(int ac,int tme)
{
    pii t1=split(rt,ac,tme);
    pii t2=split(t1.second,ac,tme+1);
    int a=t1.first,b=t2.first,c=t2.second;
    tr[b].cnt--;tr[b].sz--;
    if(!tr[b].cnt) rt=merge(a,c);
    else rt=merge(merge(a,b),c);
}

void insert(int ac,int tme)
{
    pii t1=split(rt,ac,tme);
    pii t2=split(t1.second,ac,tme+1);
    int a=t1.first,b=t2.first,c=t2.second;
    if(b) tr[b].cnt++,tr[b].sz++,rt=merge(merge(a,b),c);
    else rt=merge(merge(a,newnode(ac,tme)),c);
}

int getrank(int ac,int tme)
{
    pii t=split(rt,ac,tme);
    int res=tr[t.first].sz;
    rt=merge(t.first,t.second);
    return res;
}

int main()
{
    int qwq;srand(time(0));
    scanf("%d",&qwq);
    while(qwq--)
    {
        scanf("%d%d%d",&m,&n,&seed);
        memset(ac,0,sizeof(ac));
        memset(tme,0,sizeof(tme));
        memset(tr,0,sizeof(tr));
        rt=tot=0;
        while(n--)
        {
            int x=read(),y=read();
            if(ac[x]) remove(ac[x],tme[x]);
            ac[x]++;tme[x]+=y;
            insert(ac[x],tme[x]);
            last=getrank(ac[x],tme[x]);
            printf("%u\n",last);
        }
    }
    return 0;
}