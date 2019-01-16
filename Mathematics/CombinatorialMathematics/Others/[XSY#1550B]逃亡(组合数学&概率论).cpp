#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=12000000;
int fac[N],ifac[N];
int n,m,p[25];
int sum[N],f[N];
unordered_map<int,int> g;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void init(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%ha;
	ifac[n]=Pow(fac[n],ha-2);
	for(int i=n-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}
int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    scanf("%d%d",&n,&m);init(n);
    for(int i=0;i<=n;i++)
    {
        if(i) sum[i]=sum[i-1];
        if((i&1)==(n&1)) sum[i]=add(sum[i],C(n,(n-i)>>1));
    }
    int ivall=Pow(Pow(2,ha-2),n);
    for(int i=1;i<=n;i++)
        f[i]=1ll*mns(add(sum[i],sum[i-1]),sum[0])*ivall%ha;
    for(int i=1;i<=m;i++) scanf("%d",p+i);
    sort(p+1,p+1+m);
    int ans=0;
    for(int pos=p[1]-n,i=1;i<=m;i++,pos=max(pos,p[i]-n))
        for(;pos<=p[i]+n;pos++)
        {
            int res=1;
            for(int i=1;i<=m;i++)
            {
                int d=abs(pos-p[i]);
                if(d>n) continue;
                res=1ll*res*f[d]%ha;
            }
            ans=add(ans,mns(1,res));
        }
    printf("%d\n",ans);
	return 0;
}