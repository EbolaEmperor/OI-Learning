#include<bits/stdc++.h>
using namespace std;
 
const int N=100010;
const int V=10010,S=325;
int a[N],n,m,L[S],tot=0;
int cnt[S][V],sum[S][N];
 
void modify(int p,int x)
{
    for(int i=p/S+1;i<=tot;i++)
    {
        sum[i][cnt[i][a[p]]]--;
        cnt[i][a[p]]--;
        cnt[i][x]++;
        sum[i][cnt[i][x]]++;
    }
    a[p]=x;
}
 
int query1(int p)
{
    int ans=cnt[p/S][a[p]];
    for(int i=L[p/S+1];i<=p;i++)
        ans+=(a[i]==a[p]);
    return ans;
}
 
int query2(int p)
{
    int c=query1(p),B=p/S;
    int ans=sum[B][c];
    for(int i=L[B+1];i<=p;i++)
    {
        cnt[B][a[i]]++;
        ans+=(cnt[B][a[i]]==c);
    }
    for(int i=L[B+1];i<=p;i++)
        cnt[B][a[i]]--;
    return ans;
}
 
int query(int x,int y)
{
    if(x==1) return a[y];
    return (x&1)?query2(y):query1(y);
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        int id=i/S+1;
        if(!L[id])
        {
            L[id]=i;tot++;
            memcpy(cnt[id],cnt[id-1],sizeof(cnt[id]));
            memcpy(sum[id],sum[id-1],sizeof(sum[id]));
        }
        cnt[id][a[i]]++;
        sum[id][cnt[id][a[i]]]++;
    }
    scanf("%d",&m);
    int opt,x,y;
    while(m--)
    {
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==1) modify(y,x);
        else printf("%d\n",query(x,y));
    }
    return 0;
}