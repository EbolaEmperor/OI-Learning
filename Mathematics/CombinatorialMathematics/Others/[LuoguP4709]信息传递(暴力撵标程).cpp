#include<bits/stdc++.h>
#define Mod 998244353
#define pb push_back
using namespace std;

typedef long long LL;
const int N=100005;
vector<int> g[N],w[N];
int n,a[N],num[N],ans=1;
int fac[N],ifac[N],f[N];
bool vis[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%Mod)
		if(b&1) ans=1ll*ans*a%Mod;
    return ans;
}

int P(int x,int y){return 1ll*fac[x]*ifac[x-y]%Mod;}

int work(int x)
{
    int ans=0;
    while(!vis[x])
		ans++,vis[x]=1,x=a[x];
    return ans;
}

void solve()
{
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%Mod;
    ifac[n]=Pow(fac[n],Mod-2);
    for(int i=n;i;i--) ifac[i-1]=1ll*ifac[i]*i%Mod;
    for(int i=1;i<=n;i++)
		if(!vis[i]) num[work(i)]++;
    for(int i=n;i;i--) g[i/__gcd(i,n)].pb(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<g[i].size();j++)
			w[i].pb(Pow(i,g[i][j]/i-1));
    for(int i=1;i<=n;i++) 
		if(num[i])
		{
	        int T=num[i]*i,now;
	        f[0]=1;
	        for(int j=i;j<=T;j+=i){
	            f[j]=0;
	            for(int l=g[i].size()-1;l>=0;l--){
	                now=g[i][l];
	                if(now>j) break;
	                f[j]=(f[j]+1ll*f[j-now]*P(j/i-1,now/i-1)%Mod*w[i][l]%Mod)%Mod;
	            }
	        }
	        ans=1ll*ans*f[T]%Mod;
	    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
		scanf("%d",a+i);
    solve();
    printf("%d\n",ans);
    return 0;
}
