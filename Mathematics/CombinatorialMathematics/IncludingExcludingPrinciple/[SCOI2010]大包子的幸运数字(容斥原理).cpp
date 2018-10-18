#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
ULL a,b;
ULL pw[15];
ULL num[2600],nm[2600];
int tot=0,cnt=0;
LL ans=0;

inline ULL gcd(ULL a,ULL b){return b?gcd(b,a%b):a;}

void Init(ULL x,int d)
{
	if(d>9) return;
	ULL z=num[++tot]=6ll*pw[d]+x;
	if(z>b){tot--;return;}
	ULL y=num[++tot]=8ll*pw[d]+x;
	if(y>b){tot--;return;}
	Init(z,d+1);Init(y,d+1);
}

void dfs(ULL lcm,int d,int chs)
{
	if(d>cnt)
	{
		if(chs==0) return;
		LL fg=(chs&1)?1:-1;
		ans+=fg*(b/lcm-a/lcm);
		return;
	}
	dfs(lcm,d+1,chs);
	ULL lm=lcm/gcd(lcm,nm[d])*nm[d];
	if(lm<=b) dfs(lm,d+1,chs+1);
}

int main()
{
	cin>>a>>b;
	a--;pw[0]=1;
	for(int i=1;i<=10;i++)
		pw[i]=pw[i-1]*10ll;
	Init(0ll,0);
	sort(num+1,num+1+tot);
	for(int i=1;i<=tot;i++)
	{
		nm[++cnt]=num[i];
		for(int j=1;j<i;j++)
			if(nm[cnt]%num[j]==0){cnt--;break;}
	}
	reverse(nm+1,nm+1+cnt);
	dfs(1ll,1,0);
	cout<<ans<<endl;
	return 0;
}
