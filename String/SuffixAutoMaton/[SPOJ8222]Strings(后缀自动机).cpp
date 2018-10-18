#include<bits/stdc++.h>
using namespace std;

const int MAXN=600000;
int ch[MAXN][26],prt[MAXN];
int len[MAXN],sz[MAXN];
int c[MAXN],a[MAXN];
char s[MAXN];
int tot=1,lst=1;
int ans[MAXN];

void insert(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[p]+1==len[q]) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;sz[lst]=1;
}

int main()
{
	scanf("%s",s);
	int l=strlen(s);
	for(int i=0;i<l;i++)
		insert(s[i]-'a');
	for(int i=1;i<=tot;i++) c[len[i]]++;
	for(int i=1;i<=tot;i++) c[i]+=c[i-1];
	for(int i=1;i<=tot;i++) a[c[len[i]]--]=i;
	for(int i=tot;i>=1;i--)
	{
		int p=a[i];
		sz[prt[p]]+=sz[p];
		ans[len[p]]=max(ans[len[p]],sz[p]);
	}
	for(int i=1;i<=l;i++) printf("%d\n",ans[i]);
	return 0;
}
