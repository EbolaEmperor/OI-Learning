#include<bits/stdc++.h>
#define Mod 19260817
using namespace std;

typedef long long LL;
LL inv(LL a)
{
	LL b=Mod-2,ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return ans;
}

void read(LL &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x*10+c-'0')%Mod,c=getchar();
}

int main()
{
	LL a,b;
	read(a);read(b);
	if(a==0) puts("0");
	else if(b==0) puts("Angry!");
	else cout<<(a*inv(b)%Mod)<<endl;
	return 0;
}
