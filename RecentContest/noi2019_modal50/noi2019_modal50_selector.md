---
title: 【NOI2019模拟赛（五十）】博士的选取器
date: 2019-03-25
tag: [CDQ分治,动态规划(DP)]
---

### 题意简述

给定一个长为$n$的序列$a$，你需要将其划分成若干段，每一段的代价是段内最大值，最小化总代价

<!--more-->

此外，还有一个限制$m$，要求每段的总和不超过$m$

### 题解

设$f_i$表示前$i$个数的最小划分代价，不难得出：

$$f_i=\min_{j=0}^{i-1}\left(f_j+\max_{k=j+1}^ia_k\right)$$

这个dp式子非常经典，直接CDQ分治即可

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=0x3f3f3f3f3f3f3f3fll;
inline void upmin(LL &x,const LL &y){if(y<x) x=y;}
inline void upmax(LL &x,const LL &y){if(y>x) x=y;}

const int N=300010;
int n,a[N];
LL m,sum[N],f[N];

void cdq(int l,int r)
{
    static LL mnf[N];
    static int mxa[N];
    if(l==r) return;
    int mid=(l+r)/2;
    cdq(l,mid);
    mxa[mid]=a[mid];mxa[mid+1]=a[mid+1];mnf[mid]=f[mid];
    for(int i=mid-1;i>=l;i--) mnf[i]=min(mnf[i+1],f[i]);
    for(int i=mid-1;i>=l;i--) mxa[i]=max(mxa[i+1],a[i]);
    for(int i=mid+2;i<=r;i++) mxa[i]=max(mxa[i-1],a[i]);
    int p1=l,p2=mid+1;
    for(int i=mid+1;i<=r;i++)
    {
        while(sum[i]-sum[p1]>m) p1++;
        while(p2-1>l&&mxa[p2-1]<=mxa[i]) p2--;
        if(p1>mid) break;
        upmin(f[i],mxa[i]+mnf[max(p1,p2-1)]);
    }
    p1=r;p2=mid;
    for(int i=mid+1;i<=r;i++) mnf[i]=INF;
    for(int i=mid;i>l;i--)
    {
        while(sum[p1]-sum[i-1]>m) p1--;
        while(p2<r&&mxa[p2+1]<=mxa[i]) p2++;
        if(p1<=mid) break;
        upmin(mnf[min(p1,p2)],f[i-1]+mxa[i]);
    }
    for(int i=r;i>mid;i--)
        upmin(f[i],mnf[i]),upmin(mnf[i-1],mnf[i]);
    cdq(mid+1,r);
}

int main()
{
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    memset(f,0x3f,sizeof(f));
    f[0]=0;cdq(0,n);
    printf("%lld\n",f[n]);
    return 0;
}
```