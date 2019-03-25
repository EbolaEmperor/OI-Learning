---
title: 【NOI2019模拟赛（五十）】期望
date: 2019-03-25
tag: [概率与期望,Matrix-Tree定理,最小生成树]
---

### 题意简述

给定一个$n$个点$m$条边的图，每条边有长度和价值

<!--more-->

定义一颗生成树的价值为所有树边的价值之和。假设每种最小生成树的选取概率都是相等的，求最小生成树的期望价值

$n\leq 10^4,m\leq 2\times 10^5$，同种价值的边最多$30$条

### 题解

我们可以计算出每条边的选取概率，然后得到这条边的贡献，根据期望的线性可加性，把全部加起来即为答案

于是问题转化为：求包含某条边的最小生成树数量$\div$所有最小生成树数量

考虑`kruskal`算法的过程。不论价值相同的边如何排列、如何选择，做完所有价值$\leq w$的边后，最后得到的连通性一定是相同的，于是我们可以把每种价值的边拿出来独立考虑

把价值为$w$的边和相关的点拿出来，每个连通块分别跑`Matrix-Tree`求出生成树数量，这实际上就是这个连通块内所有价值为$w$的边的合法选择方案数，再减去删去某条边后的合法选择方案数，得到的就是包含这条边的合法选择方案数。后者除以前者，就是我们要求的东西。跑完后把同一个连通块缩点，再继续进行`kruskal`

JSOI2008有一道最小生成树计数模板，如果一些地方我说的不够清楚，可以先去看看那题的`Matrix-Tree`做法，再倒回来看本题

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long double LD;
const int N=200010;
struct Edge{int u,v,w,c;} e[N],cur[35];
LD mat[35][35],g[35][35];
int fa[N],ffa[N],n,m;
LD ans=0;

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int ffind(int x){return ffa[x]==x?x:ffa[x]=ffind(ffa[x]);}

LD gauss(int n)
{
    LD res=1;
    for(int i=1;i<n;i++)
    {
        int p=i;
        while(p<n&&fabs(mat[p][i])<1e-6) p++;
        if(p>=n) return 0;
        if(p!=i)
        {
            for(int j=1;j<n;j++)
                swap(mat[p][j],mat[i][j]);
            res=-res;
        }
        res*=mat[i][i];
        for(int j=i+1;j<n;j++)
        {
            LD t=mat[j][i]/mat[i][i];
            for(int k=i;k<n;k++)
                mat[j][k]-=t*mat[i][k];
        }
    }
    return res;
}

void gao(int m)
{
    static int idx[N],vtx[65];
    int tot=0;
    memset(mat,0,sizeof(mat));
    for(int i=1;i<=m;i++)
    {
        int u=cur[i].u,v=cur[i].v;
        u=find(u);v=find(v);
        if(!idx[u]) vtx[idx[u]=++tot]=u;
        if(!idx[v]) vtx[idx[v]=++tot]=v;
        cur[i].u=idx[u];
        cur[i].v=idx[v];
    }
    for(int i=1;i<=tot;i++) ffa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int u=cur[i].u,v=cur[i].v;
        u=ffind(u);v=ffind(v);
        if(u!=v) ffa[u]=v;
    }
    for(int i=1;i<=tot;i++)
    {
        if(ffa[i]!=i) continue;
        static int ind[65],vx[35];
        int sum=0;
        for(int j=1;j<=tot;j++)
            if(ffind(j)==i) vx[ind[j]=++sum]=j;
        memset(g,0,sizeof(g));
        for(int j=1;j<=m;j++)
        {
            if(ffind(cur[j].u)!=i) continue;
            int u=ind[cur[j].u],v=ind[cur[j].v];
            g[u][u]++;g[v][v]++;
            g[u][v]--;g[v][u]--;
        }
        memcpy(mat,g,sizeof(mat));
        LD res=gauss(sum);
        for(int j=1;j<=m;j++)
        {
            if(ffind(cur[j].u)!=i) continue;
            int u=ind[cur[j].u],v=ind[cur[j].v];
            memcpy(mat,g,sizeof(mat));
            mat[u][u]--;mat[v][v]--;
            mat[u][v]++;mat[v][u]++;
            ans+=(LD)cur[j].c*(res-gauss(sum))/res;
        }
    }
    for(int i=1;i<=tot;i++) idx[vtx[i]]=0;
}

void kruskal()
{
    sort(e+1,e+1+m,[](Edge a,Edge b){return a.w<b.w;});
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,cnt=0;i<=m;i++)
    {
        cur[++cnt]=e[i];
        if(e[i+1].w==e[i].w) continue;
        gao(cnt);
        for(int j=i;j>i-cnt;j--)
        {
            int u=e[j].u,v=e[j].v;
            u=find(u);v=find(v);
            if(u!=v) fa[u]=v;
        }
        cnt=0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].w,&e[i].c);
    kruskal();
    printf("%.5Lf\n",ans);
    return 0;
}
```