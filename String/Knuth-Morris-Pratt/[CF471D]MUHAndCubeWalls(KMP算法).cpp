#include<bits/stdc++.h>
using namespace std;

int s1[200010],s2[200010];
int nxt[200010];
int n,m;

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",s1+i);
	for(int i=1;i<=m;i++) scanf("%d",s2+i);
	if(m==1){cout<<n<<endl;return 0;}
	for(int i=1;i<n;i++) s1[i]=s1[i+1]-s1[i];
	for(int i=1;i<m;i++) s2[i]=s2[i+1]-s2[i];
	int j=0;
	for(int i=2;i<m;i++)
	{
		while(j&&s2[i]!=s2[j+1]) j=nxt[j];
		if(s2[i]==s2[j+1]) j++;
		nxt[i]=j;
	}
	int ans=0;j=0;
	for(int i=1;i<n;i++)
	{
		while(j&&s1[i]!=s2[j+1]) j=nxt[j];
		if(s1[i]==s2[j+1]) j++;
		if(j==m-1) j=nxt[j],ans++;
	}
	cout<<ans<<endl;
	return 0;
}
