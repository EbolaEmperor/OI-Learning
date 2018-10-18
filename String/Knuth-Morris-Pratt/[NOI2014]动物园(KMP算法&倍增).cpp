#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
const int N=1000010;
int nxt[20][N],num[N];
char s[N];

int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",s+1);
		int l=strlen(s+1),j=0;
		LL ans=1;
		memset(nxt,0,sizeof(nxt));
		memset(num,0,sizeof(num));
		num[0]=0;num[1]=1;
		for(int i=2;i<=l;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[0][j];
			if(s[i]==s[j+1]) j++;
			nxt[0][i]=j;num[i]=num[j]+1;
		}
		for(int k=1;k<=19;k++)
			for(int i=1;i<=l;i++)
				nxt[k][i]=nxt[k-1][nxt[k-1][i]];
		for(int i=1;i<=l;i++)
		{
			int p=i;
			for(int k=19;k>=0;k--)
				if(nxt[k][p]>i/2) p=nxt[k][p];
			if(p!=i) ans=ans*((LL)num[nxt[0][p]]+1)%Mod;
			else ans=ans*(LL)num[i]%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
