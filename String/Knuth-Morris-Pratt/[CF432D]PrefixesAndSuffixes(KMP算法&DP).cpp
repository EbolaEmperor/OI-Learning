#include<bits/stdc++.h>
using namespace std;

char s[100010];
int nxt[100010];
int r[100010],cnt=0;
int f[100010];

int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1),j=0;
	for(int i=2;i<=n;i++)
	{
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
	for(int i=nxt[n];i;i=nxt[i]) r[++cnt]=i;
	cout<<cnt+1<<endl;
	for(int i=n;i>=1;i--) f[i]++,f[nxt[i]]+=f[i];
	for(int i=cnt;i>=1;i--) printf("%d %d\n",r[i],f[r[i]]);
	printf("%d %d\n",n,1);
	return 0;
}
