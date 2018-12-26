#include<bits/stdc++.h>
using namespace std;

double s[50000][28][28];
double deal[28][28];
int ans[50000];

int solve()
{
    double mx=1e9;int mxid;
    for(int T=0;T<50000;T++)
    {
        double cnt=0;
        for(int i=0;i<28;i++)
            for(int j=0;j<28;j++)
                cnt+=fabs(s[T][i][j]-deal[i][j]);
        if(cnt<mx) mx=cnt,mxid=T;
    }
    return ans[mxid];
}

int main()
{
    freopen("training.in","r",stdin);
    for(int T=0;T<50000;T++)
        for(int i=0;i<28;i++)
            for(int j=0;j<28;j++)
                scanf("%lf",s[T][i]+j);
    freopen("training.out","r",stdin);
    for(int i=0;i<50000;i++) scanf("%d",ans+i);
    freopen("data.in","r",stdin);
    freopen("ans.out","w",stdout);
    for(int T=0;T<1000;T++)
    {
        for(int i=0;i<28;i++)
            for(int j=0;j<28;j++)
                scanf("%lf",deal[i]+j);
        cerr<<T<<endl;
        printf("%d\n",solve());
    }
    return 0;
}