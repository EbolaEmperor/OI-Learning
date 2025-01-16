#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL a,b,c,k[100];

bool ispow(LL a,LL b)
{
    while(a%b==0) a/=b;
    return a==1;
}

int Main()
{
    if(a==1&&b==1&&c==1) return -1;
    if(a==b) return b==c?2:0;
    if(a>b) return b==c?1:0;
    if(b>=c) return b==c?1:0;
    if(a==1&&ispow(c,b)) return 1;
    LL x=c;int n=0;
    while(x) k[++n]=x%b,x/=b;
    LL y=0;x=1;
    for(int i=1;i<=n;i++)
        y+=k[i]*x,x*=a;
    return y==b;
}

int main()
{
    while(cin>>a>>b>>c)
    {
        int ans=Main();
        if(ans==-1) puts("infinity");
        else printf("%d\n",ans);
    }
    return 0;
}