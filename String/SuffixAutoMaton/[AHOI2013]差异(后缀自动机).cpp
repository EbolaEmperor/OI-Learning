#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1000010;
LL ans=0;
char s[N];
int ch[N][26],prt[N];
int len[N],cnt[N];
int lst=1,tot=1;
struct Edge{int to,next;} e[N];
int h[N],sum=0;

void add_edge(int u,int v){e[++sum].to=v;e[sum].next=h[u];h[u]=sum;}

void insert(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;cnt[lst]=1;
}

void dfs(int u,int fa)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;dfs(v,u);
		cnt[u]+=cnt[v];
	}
	len[u]-=len[fa];
	ans-=(LL)cnt[u]*(cnt[u]-1)*len[u];
}

int main()
{
	scanf("%s",s);
	int l=strlen(s);
	ans=(LL)l*(l-1)*(l+1)/2;
	for(int i=0;i<l;i++) insert(s[i]-'a');
	for(int i=2;i<=tot;i++) add_edge(prt[i],i);
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}
