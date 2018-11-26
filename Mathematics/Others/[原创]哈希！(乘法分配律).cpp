#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=10000010;
int n,base,p,pw[N];
char s[N];

int Pow(int a,int b,int p)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

int gethash()
{
    int val=0,len=strlen(s);
    for(int i=0;i<len;i++)
        val=(1ll*val*base+s[i])%p;
    return val;
}

int solve(int k,int n)
{
    int ans=0;
    while(n)
    {
        while(n&&k<p) k*=base,n--;
        if(n==0) return (ans+k/p)%ha;
        int y=k%p,x=k-y;k=y;
        ans=(ans+1ll*x/p*pw[n])%ha;
    }
    return ans;
}

int main()
{
    scanf("%d%d%d%s",&n,&base,&p,s);
    pw[0]=1;
    for(int i=1;i<=n;i++)
        pw[i]=1ll*pw[i-1]*base%ha;
    int ans=solve(1,n);
    if(Pow(base,n,p)>gethash()) ans++;
    printf("%d\n",ans%ha);
    return 0;
}
