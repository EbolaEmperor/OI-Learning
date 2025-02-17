#include<bits/stdc++.h>
using namespace std;
 
const int N=32010,M=4000010;
struct ANS{int l,r;} ans[M];
int a[N],n,tot=0;
int val[N];
 
int solve(int l,int r)
{
    if(l==r) return val[l];
    int mid=(l+r)/2;
    int L=solve(l,mid);
    int R=solve(mid+1,r);
    if(R&&L<mid-l+1)
    {
        ans[++tot]={l+L,mid+R};
        reverse(a+l+L,a+mid+R+1);
    }
    return L+R;
}
 
void Solve(int l,int r,int L,int R)
{
    if(l==r||L>=R) return;
    int mid=(l+r)/2;
    for(int i=L;i<=R;i++)
        val[i]=bool(a[i]<=mid);
    int cnt=solve(L,R);
    Solve(l,mid,L,L+cnt-1);
    Solve(mid+1,r,L+cnt,R);
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    Solve(0,32000,1,n);
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)
        printf("%d %d\n",ans[i].l,ans[i].r);
    return 0;
}