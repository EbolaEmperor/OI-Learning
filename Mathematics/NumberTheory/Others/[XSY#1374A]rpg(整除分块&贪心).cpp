#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned __int128 LLL;

void print(LLL a)
{
    if(a==0) return;
    print(a/10);
    putchar(a%10+'0');
}

int main()
{
    LL n,k,x=1;
    LLL pre=0,ans=-1;
    cin>>n>>k;k--;
    while(x<=k)
    {
        LLL w=k/x,d=k/w;
        ans=min(ans,pre+w*n*(n+1)/2);
        pre+=n*w*(d-x+1);x=d+1;
    }
    ans=min(ans,pre);
    print(ans);puts("");
    return 0;
}