#include<bits/stdc++.h>
#define base 65535
using namespace std;
 
typedef unsigned long long ULL;
const int N=200010;
char s1[N],s2[N];
ULL p1[N],p2[N];
int cnt[65550];
 
void write(ULL x)
{
	if(x>>1) write(x>>1);
	putchar((x&1)+'0');
}
 
int main()
{
	scanf("%s%s",s1+1,s2+1);
	int n=strlen(s1+1),m=strlen(s2+1),q;
	for(int i=n;i>=1;i--)
		p1[i]=p1[i+1]>>1|(s1[i]=='1'?1ll<<63:0);
	for(int i=m;i>=1;i--)
		p2[i]=p2[i+1]>>1|(s2[i]=='1'?1ll<<63:0);
	for(int i=1;i<(1<<16);i++)
		for(int j=0;j<16;j++)
			cnt[i]+=bool(i&(1<<j));
	for(scanf("%d",&q);q;q--)
	{
		int x1,x2,len,ans=0;
		scanf("%d%d%d",&x1,&x2,&len);
		x1++;x2++;
		while(len>=64)
		{
			ans += __builtin_popcountll(p1[x1]^p2[x2]);
			x1+=64;x2+=64;len-=64;
		}
		while(len>0)
		{
			ans += (s1[x1]-'0')^(s2[x2]-'0');
			x1++;x2++;len--;
		}
		printf("%d\n",ans);
	}
	return 0;
}
