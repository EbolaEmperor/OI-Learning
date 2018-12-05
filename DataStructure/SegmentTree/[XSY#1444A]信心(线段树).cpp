#include<bits/stdc++.h>
#define bg(x) x->first
#define ed(x) x->first+x->second
using namespace std;

const int N=100010;
int sum[N<<2],tag[N<<2];

void Add(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr)
    {
        sum[o]+=r-l+1;
        tag[o]++;
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) Add(o*2,l,mid,nl,nr);
    if(nr>mid) Add(o*2+1,mid+1,r,nl,nr);
    sum[o]=sum[o*2]+sum[o*2+1]+tag[o]*(r-l+1);
}

int Sum(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return sum[o];
    int mid=(l+r)/2,res=tag[o]*(nr-nl+1);
    if(nr<=mid) res+=Sum(o*2,l,mid,nl,nr);
    else if(nl>mid) res+=Sum(o*2+1,mid+1,r,nl,nr);
    else res+=Sum(o*2,l,mid,nl,mid)+Sum(o*2+1,mid+1,r,mid+1,nr);
    return res;
}

int n,q;
map<int,int> done[N];
map<int,int>::iterator it1,it2;

void Insert(int l,int r,int x)
{
    it1=done[x].lower_bound(l);
    int p=l-1;
    if(it1!=done[x].begin())
    {
        it1--;
        if(ed(it1)>l) l=bg(it1),p=ed(it1)-1;
        it1++;
    }
    while(it1!=done[x].end()&&bg(it1)<=r)
    {
        Add(1,1,n,p+1,bg(it1)-1);
        p=ed(it1)-1;
        it2=it1;it1++;
        done[x].erase(it2);
    }
    if(p<r) Add(1,1,n,p+1,r),p=r;
    done[x][l]=p-l+1;
}

int main()
{
    int opt,l,r,x;
    scanf("%d%d",&n,&q);
    while(q--)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==0) scanf("%d",&x),Insert(l,r,x);
        else printf("%d\n",Sum(1,1,n,l,r));
    }
    return 0;
}