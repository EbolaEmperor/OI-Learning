#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

typedef long long LL;
const int N=100010;
bool Type[N];
int f[N],p[N];
LL len[N];

int Pow(int a,int b)
{
    int ans=1;a%=ha;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    LL h,pos;int n,a,b;
    static char ty[5];
    scanf("%lld%d",&h,&n);
    len[n+1]=h;
    for(int i=1;i<=n;i++)
    {
        scanf("%s%lld%d%d",ty,len+i,&a,&b);
        Type[i]=(ty[0]=='X');
        p[i]=1ll*a*Pow(b,ha-2)%ha;
    }
    for(int i=0;i<=n;i++) len[i]=len[i+1]-len[i];
    f[n]=1;
    for(int i=n-1;i>=0;i--)
    {
        if(Type[i+1]) f[i]=1ll*f[i+1]*Pow(p[i+1],ha-2)%ha;
        else f[i]=1ll*(f[i+1]-1ll*f[i+1]*p[i+1]+p[i+1])%ha;
    }
    int ans=0;
    for(int i=0;i<=n;i++) ans=(ans+len[i]%ha*f[i])%ha;
    printf("%d\n",(ans+ha)%ha);
    return 0;
}