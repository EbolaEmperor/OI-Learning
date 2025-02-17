#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int n,m,len[N];
queue<int> s1,s2,s3;
int ans[3][N];
int idx,pos,rest;

void gao3()
{
    int p=s3.front();s3.pop();
    if(!rest)
    {
        ans[0][pos]=ans[1][pos]=ans[2][pos]=p;
        len[p]-=3;pos++;idx=0;
    }
    else
    {
        ans[2-idx][pos]=ans[1][pos]=p;
        len[p]-=2;pos++;idx=2-idx;
    }
    while(len[p])
    {
        if(!s2.empty())
        {
            int q=s2.front();s2.pop();
            ans[2-idx][pos]=ans[1][pos]=q;
            ans[idx][pos]=p;
            len[q]-=2;len[p]--;
            pos++;rest=0;
        }
        else if(len[p]>1)
        {
            int q=s1.front();s1.pop();
            ans[1][pos]=ans[2-idx][pos]=p;
            ans[idx][pos]=q;
            len[p]-=2;len[q]--;
            pos++;rest=0;
            idx=2-idx;
        }
        else ans[idx][pos]=p,len[p]--,rest=1;
    }
}

void gao2()
{
    int p=s2.front();s2.pop();
    if(!rest)
    {
        ans[0][pos]=ans[1][pos]=p;
        len[p]-=2;
        if(!s2.empty())
        {
            int q=s2.front();s2.pop();
            ans[2][pos]=q;ans[2][++pos]=q;
            len[q]-=2;rest=1;idx=2;
        }
        else
        {
            int q=s1.front();s1.pop();
            ans[2][pos]=q;len[q]--;
            rest=0;pos++;
        }
    }
    else
    {
        ans[2-idx][pos]=ans[1][pos]=p;
        len[p]-=2;rest=0;pos++;
    }
}

void gao1()
{
    if(!rest)
    {
        int p=s1.front();s1.pop();
        ans[0][pos]=p;len[p]--;
        p=s1.front();s1.pop();
        ans[1][pos]=p;len[p]--;
        p=s1.front();s1.pop();
        ans[2][pos]=p;len[p]--;
        pos++;
    }
    else
    {
        int p=s1.front();s1.pop();
        ans[2-idx][pos]=p;len[p]--;
        p=s1.front();s1.pop();
        ans[1][pos]=p;len[p]--;
        pos++;rest=0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    if(m<n) return puts("no"),0;
    puts("yes");
    for(int i=1;i<=m;i++)
    {
        scanf("%d",len+i);
        if(len[i]==1) s1.push(i);
        if(len[i]==2) s2.push(i);
        if(len[i]>=3) s3.push(i);
    }
    while(!s3.empty()) gao3();
    while(!s2.empty()) gao2();
    while(!s1.empty()) gao1();
    for(int i=0;i<3;i++,puts(""))
        for(int j=0;j<n;j++)
            printf("%d ",ans[i][j]);
    return 0;
}