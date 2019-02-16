#include<bits/stdc++.h>
#include "shop.h"
using namespace std;

bool leq(int a,int b)
{
    int s[1]={a},t[1]={b};
    return query(s,1,t,1);
}
bool leq(int a,int b,int c)
{
    int s[1]={a},t[2]={b,c};
    return query(s,1,t,2);
}
bool geq(int a,int b){return !leq(a,b);}
bool geq(int a,int b,int c){return !leq(a,b,c);}

void gao1(int n,int k,int *ans)
{
    static int id[100000];
    for(int i=0;i<n;i++) id[i]=i;
    if(leq(0,n-1)) reverse(id,id+n);
    int l=0,r=n,mid;
    while(l+1<r)
    {
        mid=(l+r)/2;
        if(mid<n-1&&leq(id[0],id[mid],id[mid+1])) l=mid;
        else r=mid;
    }
    if((l+1&1)!=k) ans[id[r]]=1;
    for(int i=0;i<=l;i++) ans[id[i]]=1;
}

void gao2(int n,int k,int *ans)
{
    static int id[100000],tot=0;
    int a=0,x=1,y=2;  // let them satisfy: a ≥ y ≥ x
    id[tot++]=a;
    for(int i=3;i<=n;i++)
    {
        if(geq(x,y)) swap(x,y);
        if(geq(a,x,y)) x=i;  // x must be 0 if (a ≥ x + y)
        else id[tot++]=a=y,y=i;  // y cannot be less than a if (a ≤ x + y)
    }
    // the array id will show a monotone nondecrease. make it reversed.
    reverse(id,id+tot);
    int l=0,r=tot,mid;
    while(l+1<r)
    {
        mid=(l+r)/2;
        if(mid<tot-1&&leq(id[0],id[mid],id[mid+1])) l=mid;
        else r=mid;
    }
    for(int i=0;i<=l;i++) ans[id[i]]=1;
    x=(x<n)?x:y;
    if((l+1&1)!=k) ans[leq(x,id[r])?id[r]:x]=1;
    else if(leq(a,x,id[r])) ans[x]=ans[id[r]]=1;
}

void find_price(int task_id,int N,int K,int *ans)
{
    if(N<=2||task_id==3) gao1(N,K,ans);
    else gao2(N,K,ans);
}