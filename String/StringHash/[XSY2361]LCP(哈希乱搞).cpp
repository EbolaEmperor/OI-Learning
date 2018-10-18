#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=100010;
char s[N];
ULL f[N],p[N];

ULL Hash(int l,int r){return f[r]-f[l-1]*p[r-l+1];}

int main()
{
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
		f[i]=f[i-1]*26+s[i]-'a';
	p[0]=1;
	for(int i=1;i<=len;i++)
		p[i]=p[i-1]*26;
	int m,x,y,l,r;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&l,&r);
		int L=0,R=min(y-x+1,r-l+1);
		while(L<R)
		{
			int mid=(L+R)/2;
			if(Hash(x,x+mid-1)==Hash(l,l+mid-1)) L=mid+1;
			else R=mid-1;
		}
		if(Hash(x,x+L-1)!=Hash(l,l+L-1)) L--;
		printf("%d\n",L);
	}
	return 0;
}
