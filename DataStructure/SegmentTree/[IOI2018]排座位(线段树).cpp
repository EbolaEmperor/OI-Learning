#include<bits/stdc++.h>
#include "seats.h"
using namespace std;

typedef pair<int,int> pii;
const int N=1000010;
int mn[N<<2],cmn[N<<2],tag[N<<2];
int *a[N],h,w,q,cnt;
int r[N],c[N];
pii pos[10];

void pushdown(int o)
{
    if(!tag[o]) return;
    tag[o<<1]+=tag[o];
    mn[o<<1]+=tag[o];
    tag[o<<1|1]+=tag[o];
    mn[o<<1|1]+=tag[o];
    tag[o]=0;
}

void build(int o,int l,int r)
{
    cmn[o]=r-l+1;
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void update(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr){tag[o]+=x;mn[o]+=x;return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
    if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
    mn[o]=min(mn[o<<1],mn[o<<1|1]);cmn[o]=0;
    if(mn[o<<1]==mn[o]) cmn[o]+=cmn[o<<1];
    if(mn[o<<1|1]==mn[o]) cmn[o]+=cmn[o<<1|1];
}

void gao(int x,int y,int d)
{
    int minv=h*w,val[4],tot=0;
    if(x>0) minv=min(minv,a[x-1][y]);
    if(y>0) minv=min(minv,a[x][y-1]);
    if(minv>a[x][y]) update(1,0,h*w-1,a[x][y],minv-1,d);
    if(x>0) val[tot++]=a[x-1][y];
    if(y>0) val[tot++]=a[x][y-1];
    if(x<h-1) val[tot++]=a[x+1][y];
    if(y<w-1) val[tot++]=a[x][y+1];
    if(tot<2) return;
    sort(val,val+tot);
    if(val[1]<a[x][y]) update(1,0,h*w-1,val[1],a[x][y]-1,d);
}

void addpos(int x)
{
    pos[cnt++]=pii(r[x],c[x]);
    if(r[x]>0) pos[cnt++]=pii(r[x]-1,c[x]);
    if(c[x]>0) pos[cnt++]=pii(r[x],c[x]-1);
    if(r[x]<h-1) pos[cnt++]=pii(r[x]+1,c[x]);
    if(c[x]<w-1) pos[cnt++]=pii(r[x],c[x]+1);
}

void give_initial_chart(int H,int W,vector<int> R,vector<int> C)
{
    h=H;w=W;build(1,0,h*w-1);
    for(int i=0;i<h;i++) a[i]=new int[w];
    for(int i=0;i<h*w;i++)
    {
        r[i]=R[i];
        c[i]=C[i];
        a[r[i]][c[i]]=i;
    }
    for(int i=0;i<h*w;i++) gao(r[i],c[i],1);
}

int swap_seats(int x,int y)
{
    cnt=0;
    addpos(x);addpos(y);
    sort(pos,pos+cnt);
    cnt=unique(pos,pos+cnt)-pos;
    for(int i=0;i<cnt;i++)
        gao(pos[i].first,pos[i].second,-1);
    swap(a[r[x]][c[x]],a[r[y]][c[y]]);
    swap(r[x],r[y]);
    swap(c[x],c[y]);
    for(int i=0;i<cnt;i++)
        gao(pos[i].first,pos[i].second,1);
    return (mn[1]==1)?cmn[1]:0;
}