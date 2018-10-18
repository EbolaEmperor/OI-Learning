#include<bits/stdc++.h>
using namespace std;

char s[100010];
char ss[200010];
int p[200010];

int manacher()
{
	int l=strlen(s),len=0;
	ss[len++]='$';ss[len++]='#';
	for(int i=0;i<l;i++)
		ss[len++]=s[i],ss[len++]='#';
	ss[len]='\0';
	int mx=0,id,ans=-1;
	for(int i=1;i<len;i++)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i+p[i]]==ss[i-p[i]]) p[i]++;
		if(mx<i+p[i]) mx=i+p[i],id=i;
		ans=max(ans,p[i]-1);
	}
	return ans;
}

int main()
{
	while(~scanf("%s",s))
		printf("%d\n",manacher());
	return 0;
}
