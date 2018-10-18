#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

char s[5010];
int D[10010],ans=0;
int f[5010][2][2];

inline void Add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

void dp(int lim)
{
	int m=lim/2;
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	for(int i=0;i<m;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				if(f[i][j][k]) for(int x=0;x<=9;x++)
				{
					int kl=x+D[i+1]+k,y=kl%10;kl/=10;
					int jl=j*10+x-y-D[lim-i];
					if(jl<0||jl>1) continue;
					if(!i&&(!x||!y)) continue;
					Add(f[i+1][jl][kl],f[i][j][k]);
				}
	if(lim&1)
	{
		int mid=(lim+1)/2;
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				if(f[m][j][k]) for(int x=0;x<=9;x++)
				{
					int y=x+k+D[mid];
					if(x==y%10&&y/10==j)
						Add(ans,f[m][j][k]);
				}
	}
	else for(int j=0;j<2;j++) Add(ans,f[m][j][j]);
}

int main()
{
	scanf("%s",s+1);
	int len=strlen(s+1);
	reverse(s+1,s+1+len);
	for(int i=1;i<=len;i++)
		D[i]=s[i]-'0';
	for(int i=max(2,len);i<=2*len;i++) dp(i);
	printf("%d\n",ans);
	return 0;
}
