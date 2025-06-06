#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=800010;
char s1[N],s2[N];
int ch[N][26],prt[N],len[N];
int lst=1,tot=1,cnt1[N],cnt2[N];
int c[N],a[N];

void insert(int c)
{
	int p=lst,np=++tot;
	len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
}

void count()
{
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<tot;i++) c[i+1]+=c[i];
	for(int i=1;i<=tot;i++) a[c[len[i]]--]=i;
	for(int i=tot;i>=1;i--)
		cnt1[prt[a[i]]]+=cnt1[a[i]],
		cnt2[prt[a[i]]]+=cnt2[a[i]];
}

int main()
{
	scanf("%s%s",s1,s2);
	int l1=strlen(s1),l2=strlen(s2),p=1;
	for(int i=0;i<l1;i++)
	{
		insert(s1[i]-'a');
		p=ch[p][s1[i]-'a'];
		cnt1[p]++;
	}
	lst=p=1;
	for(int i=0;i<l2;i++)
	{
		insert(s2[i]-'a');
		p=ch[p][s2[i]-'a'];
		cnt2[p]++;
	}
	count();
	LL ans=0;
	for(int i=1;i<=tot;i++)
		ans+=(LL)(len[i]-len[prt[i]])*cnt1[i]*cnt2[i];
	cout<<ans<<endl;
	return 0;
}
