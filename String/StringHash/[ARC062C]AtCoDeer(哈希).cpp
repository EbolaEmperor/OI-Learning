#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL A=1000,B=1000000,C=1000000000ll;
int col[410][4];
LL num[4];
unordered_map<LL,LL> cnt;

LL gethash(int x1,int x2,int x3,int x4){return x1+A*x2+B*x3+C*x4;}

void add(int x1,int x2,int x3,int x4,int k)
{
	cnt[gethash(x1,x2,x3,x4)]+=k;
	cnt[gethash(x2,x3,x4,x1)]+=k;
	cnt[gethash(x3,x4,x1,x2)]+=k;
	cnt[gethash(x4,x1,x2,x3)]+=k;
}

void add(LL x,int k)
{
	int x1=x%A;x/=A;
	int x2=x%A;x/=A;
	int x3=x%A;x/=A;
	int x4=x%A;x/=A;
	add(x1,x2,x3,x4,k);
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&col[i][0],&col[i][1],&col[i][2],&col[i][3]);
		add(col[i][0],col[i][1],col[i][2],col[i][3],1);
	}
	LL ans=0;
	for(int i=1;i<n;i++)
	{
		add(col[i][0],col[i][1],col[i][2],col[i][3],-1);
		for(int j=i+1;j<=n;j++)
		{
			add(col[j][0],col[j][1],col[j][2],col[j][3],-1);
			for(int k=0;k<4;k++)
			{
				for(int l=0;l<4;l++) num[l]=gethash(col[i][l],col[j][(k+5-l)&3],col[j][(k+4-l)&3],col[i][(l+1)&3]);
				if(!cnt[num[0]]||!cnt[num[1]]||!cnt[num[2]]||!cnt[num[3]]) continue;
				LL res=1;
				for(int l=0;l<4;l++) res*=cnt[num[l]],add(num[l],-1);
				for(int l=0;l<4;l++) add(num[l],1);
				ans+=res;
			}
			add(col[j][0],col[j][1],col[j][2],col[j][3],1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}