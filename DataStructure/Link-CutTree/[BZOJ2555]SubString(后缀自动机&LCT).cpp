#include<bits/stdc++.h>
using namespace std;

const int N=1200010;
int son[N][2];
int fa[N],w[N],tag[N];
int sta[N],top=0;

bool nroot(int x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
void add(int x,int k){if(x) tag[x]+=k,w[x]+=k;}
void pushdown(int x)
{
	if(tag[x])
	{
		add(son[x][0],tag[x]);
		add(son[x][1],tag[x]);
		tag[x]=0;
	}
}

void rotate(int x)
{
	int y=fa[x],z=fa[y],k=(son[y][1]==x),w=son[x][k^1];
	if(nroot(y)) son[z][son[z][1]==y]=x;
	son[x][k^1]=y;
	son[y][k]=w;
	if(w) fa[w]=y;
	fa[y]=x;
	fa[x]=z;
}

void splay(int x)
{
	int y=x,z;
	sta[top++]=y;
	while(nroot(y)) sta[top++]=y=fa[y];
	while(top) pushdown(sta[top-1]),top--;
	while(nroot(x))
	{
		y=fa[x];z=fa[y];
		if(nroot(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
		rotate(x);
	}
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		son[x][1]=y;
		y=x;x=fa[x];
	}
}

void link(int x,int y)
{
	fa[x]=y;
	access(y);
	splay(y);
	add(y,w[x]);
}

void cut(int x)
{
	access(x);
	splay(x);
	add(son[x][0],-w[x]);
	fa[son[x][0]]=0;
	son[x][0]=0;
}

int n;
char s[3000010],opt[10];
string chars;
int ch[N][26],prt[N];
int len[N];
int tot=1,lst=1;

void getQ(int mask)
{
	scanf("%s",s);
	chars=s;
	for(int j=0;j<chars.length();j++) 
	{
		mask=(mask*131+j)%chars.length();
		char t=chars[j];
		chars[j]=chars[mask];
		chars[mask]=t;
	}
}

void insert(int c)
{
	int p=lst,np=++tot;
	len[np]=len[p]+1;w[np]=1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1,link(np,1);
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q,link(np,q);
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];link(nq,prt[q]);
			cut(q);prt[q]=nq;link(q,nq);
			prt[np]=nq;link(np,nq);
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
}

int main()
{
	int mask=0,Q;
	scanf("%d%s",&Q,s);
	int l=strlen(s);
	for(int i=0;i<l;i++) insert(s[i]-'A');
	while(Q--)
	{
		scanf("%s",opt);
		getQ(mask);l=chars.length();
		if(opt[0]=='A')
			for(int i=0;i<l;i++)
				insert(chars[i]-'A');
		else
		{
			int p=1,ans=0;
			for(int i=0;i<l;i++)
			{
				if(!(p=ch[p][chars[i]-'A'])){ans=0;break;}
				if(i+1==l) splay(p),ans=w[p];
			}
			printf("%d\n",ans);
			mask^=ans;
		}
	}
	return 0;
}
