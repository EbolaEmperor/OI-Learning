#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=30,M=15000010;
int p1[N],p2[N],*p,k,n;
int cnt1=0,cnt2=0,*cc;
LL R,cnt=0,ans=0;
LL num1[M],num2[M],*num;

void dfs(LL now,int pos)
{
    num[++(*cc)]=now;
    for(int i=pos;i<=n;i++)
    {
        if((long double)now*p[i]>R) break;
        dfs(now*p[i],i);
    }
}

int main()
{
    scanf("%d%lld",&k,&R);
    for(int i=1;i<=k;i++) scanf("%d",p1+i);
    sort(p1+1,p1+1+k);
    int tot1=0,tot2=0;
    for(int i=1;i<=k;i++)
        if(i&1) p1[++tot1]=p1[i];
        else p2[++tot2]=p1[i];
    n=tot1;p=p1;cc=&cnt1;num=num1;dfs(1,1);
    n=tot2;p=p2;cc=&cnt2;num=num2;dfs(1,1);
    sort(num1+1,num1+1+cnt1);sort(num2+1,num2+1+cnt2);
    for(int i=1,cur=cnt2;i<=cnt1;i++)
    {
        while((long double)num1[i]*num2[cur]>R) cur--;
        cnt+=cur;ans=max(ans,num1[i]*num2[cur]);
    }
    printf("%lld\n%lld\n",ans,cnt);
    return 0;
}