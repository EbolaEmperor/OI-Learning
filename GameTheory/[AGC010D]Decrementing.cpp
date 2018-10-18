#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int a[N],n,cnt[2];

bool gao()
{
    for(int i=1;i<=n;i++)
        if(a[i]&1) a[i]--;
    cnt[0]=cnt[1]=0;
    int gcd=a[1];
    for(int i=2;i<=n;i++)
        gcd=__gcd(a[i],gcd);
    for(int i=1;i<=n;i++)
        cnt[(a[i]/=gcd)&1]++;
    if(cnt[0]&1) return 1;
    else if(cnt[1]>1) return 0;
    else
    {
        for(int i=1;i<=n;i++)
            if(a[i]==1) return cnt[0]&1?1:0;
        return gao()^1;
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        cnt[a[i]&1]++;
    }
    if(cnt[0]&1) puts("First");
    else if(cnt[1]>1) puts("Second");
    else
    {
        for(int i=1;i<=n;i++)
            if(a[i]==1){puts(cnt[0]&1?"First":"Second");return 0;}
        puts(gao()^1?"First":"Second");
    }
    return 0;
}