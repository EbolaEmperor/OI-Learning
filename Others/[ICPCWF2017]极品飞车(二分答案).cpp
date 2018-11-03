#include<bits/stdc++.h>
using namespace std;

const int N=1010;
int n,t,d[N],s[N];

bool check(double x)
{
    double res=0.0;
    for(int i=1;i<=n;i++)
        res+=(double)d[i]/(s[i]+x);
    return res<t;
}

int main()
{
    double l=-1e5,r=1e9,mid;
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",d+i,s+i);
        l=max(l,(double)-s[i]);
    }
    while(r-l>1e-7)
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    printf("%.7lf\n",l);
    return 0;
}