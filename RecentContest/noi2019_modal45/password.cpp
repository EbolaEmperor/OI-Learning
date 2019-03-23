#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
int a[N],b[N],c[N],d[N],n;
int bitcnt[N];
LL S=0;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<=n;i++) d[i]=b[i]+c[i],S+=d[i];
    if(S%(2*n)) return puts("-1"),0;S/=2*n;
    for(int i=1;i<=n;i++)
    {
        int tmp=d[i]-S;
        if(tmp%n) return puts("-1"),0;
        a[i]=tmp/n;
    }
    for(int i=1;i<=n;i++)
        for(int k=0,x=a[i];k<30;k++)
            bitcnt[k]+=x&1,x>>=1;
    for(int i=1;i<=n;i++)
    {
        LL sum1=0,sum2=0;int x=a[i];
        for(int k=0;k<30;k++,x>>=1)
        {
            if(x&1) sum1+=(LL)bitcnt[k]*(1<<k);
            if(x&1) sum2+=(LL)n*(1<<k);
            else sum2+=(LL)bitcnt[k]*(1<<k);
        }
        if(sum1!=b[i]||sum2!=c[i]) return puts("-1"),0;
    }
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    return puts(""),0;
}