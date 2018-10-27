#include<bits/stdc++.h>
using namespace std;

unordered_map<int,int> val;

double query(int o,int mx)
{
    if(val[o]<=mx) return mx;
    double res=query(o<<1,max(mx,val[o]-val[o<<1]));
    res+=query(o<<1|1,max(mx,val[o]-val[o<<1|1]));
    return res/2;
}

int main()
{
    int h,n,x,y;
    static char opt[10];
    scanf("%d%d",&h,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",opt);
        if(opt[0]=='d') printf("%.5lf\n",query(1,0));
        else for(scanf("%d%d",&x,&y);x;x>>=1) val[x]+=y;
    }
    return 0;
}