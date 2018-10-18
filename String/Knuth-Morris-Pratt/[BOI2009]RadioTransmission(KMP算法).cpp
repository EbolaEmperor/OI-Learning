#include<bits/stdc++.h>
using namespace std;

char s[1000010];
int nxt[1000010];

int main()
{
	int n,j=0;
	scanf("%d%s",&n,s+1);
	for(int i=2;i<=n;i++)
	{
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
	cout<<n-nxt[n]<<endl;
	return 0;
}
