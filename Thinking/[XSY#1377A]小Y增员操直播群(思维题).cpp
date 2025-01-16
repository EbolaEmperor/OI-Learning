#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> lft[N];
int cur[N];
int T,n,m;

int divide(int l,int r)
{
    if(l==r) return cur[l]==lft[l].size()?0:-1;
    int mid=(l+r)/2;
    if(cur[r]==lft[r].size()) return -1;
    int p=lft[r][cur[r]++],len=p-l+1;
    if(p<l||p>mid) return -1;
    if((r-l+1)%2==0&&p==mid)
    {
        for(int i=1;i<len;i++)
        {
            int q=r-i;
            if(cur[q]==lft[q].size()) return -1;
            if(q-lft[q][cur[q]++]!=r-p) return -1;
        }
        int L=divide(l,p);
        if(L==-1) return -1;
        int R=divide(p+1,r);
        if(R==-1) return -1;
        return max(L,R)+1;
    }
    if(cur[r-len]==lft[r-len].size()) return -1;
    int u=lft[r-len][cur[r-len]],sz=u-l+1;
    if(u<l||u>mid) return -1;
    for(int i=u+1;i<r;i++)
    {
        if(cur[i]==lft[i].size()) return -1;
        if(lft[i][cur[i]++]!=(i-l)%sz+l) return -1;
    }
    int L=divide(l,u);
    if(L==-1) return -1;
    int R=divide(u+1,r);
    if(R==-1) return -1;
    return max(L,R)+1;
}

int gao()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) lft[i].clear(),cur[i]=0;
    bool falun=0;
    for(int i=0,x,y;i<m;i++)
    {
        scanf("%d%d",&x,&y);
        if(x>y) swap(x,y);
        if(x==y) falun=1;
        lft[y].push_back(x);
    }
    if(falun) return -1;
    for(int i=0;i<n;i++)
        sort(lft[i].begin(),lft[i].end());
    return divide(0,n-1);
}

int main()
{
    scanf("%d",&T);
    while(T--) printf("%d\n",gao());
    return 0;
}