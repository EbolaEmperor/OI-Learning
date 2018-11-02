#include<bits/stdc++.h>
using namespace std;

const int N=260;
int T[N][N],n;
int pos[N];

int gao()
{
    static int idx[N];
    for(int i=1;i<=n;i++) idx[i]=i;
    random_shuffle(idx+1,idx+1+n);
    int res1=0,res2=0;
    for(int i=1;i<=n;i++)
    {
        int nxt1=res1,nxt2=res2,x=idx[i];
        for(int j=1;j<i;j++)
        {
            int y=idx[j];
            if(pos[y]==1) nxt1=max(nxt1,T[x][y]);
            else nxt2=max(nxt2,T[x][y]);
        }
        int delta1=nxt1-res1,delta2=nxt2-res2;
        if(delta1<delta2) res1=nxt1,pos[x]=1;
        else res2=nxt2,pos[x]=2;
    }
    return res1+res2;
}

int main()
{
    srand(time(0));
    while(~scanf("%d",&n))
    {
        memset(T,0,sizeof(T));
        for(int i=1,x;i<=n;i++)
            for(int j=1;j<=n-i;j++)
            {
                scanf("%d",&x);
                T[i][i+j]=x;
                T[i+j][i]=x;
            }
        int ans=0x7fffffff,tms=5000;
        while(tms--) ans=min(ans,gao());
        printf("%d\n",ans);
    }
    return 0;
}