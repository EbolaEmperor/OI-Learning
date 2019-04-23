#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int ha=1e9+7;
const int N=500010;
int n,a[N],b[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    int inv100=Pow(100,ha-2);
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=1ll*read()*inv100%ha,b[i]=1ll*read()*inv100%ha;
    int ans=a[1],f=0;
    for(int i=1;i<n;i++)
    {
        int t=(b[i]+1ll*a[i]*f)%ha;
        int tmp=Pow((1-1ll*t*b[i+1]%ha+ha)%ha,ha-2);
        ans=1ll*ans*a[i+1]%ha*tmp%ha;
        f=1ll*t*a[i+1]%ha*tmp%ha;
    }
    cout<<ans<<endl;
    return 0;
}
