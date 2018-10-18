#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int ch[N][2],dis[N];
struct Node
{
	int w,v;
	Node(int a=0,int b=0):w(a),v(b){}
	friend bool operator < (const Node &a,const Node &b){return a.w>b.w;}
} val[N];
int stk[2];

int Merge(int a,int b)
{
	if(a==0||b==0) return a+b;
	if(val[b]<val[a]) swap(a,b);
	ch[a][1]=Merge(ch[a][1],b);
	if(dis[ch[a][0]]<dis[ch[a][1]]) swap(ch[a][0],ch[a][1]);
	dis[a]=dis[ch[a][1]]+1;
	return a;
}

int main()
{
	int n,x,cas=0;
	static char opt[10],s1[5],s2[5];
	while(~scanf("%d",&n)&&n)
	{
		printf("Case #%d:\n",++cas);
		int tot=0;stk[0]=stk[1]=0;
		while(n--)
		{
			scanf("%s%s",opt,s1);
			if(opt[1]=='u')
			{
				scanf("%d",&x);
				int A=s1[0]-'A';
				val[++tot]=Node(tot,x);
				ch[tot][0]=ch[tot][1]=0;
				if(!stk[A]) stk[A]=tot;
				else stk[A]=Merge(stk[A],tot);
			}
			if(opt[1]=='o')
			{
				int A=s1[0]-'A',ans=val[stk[A]].v;
				stk[A]=Merge(ch[stk[A]][0],ch[stk[A]][1]);
				printf("%d\n",ans);
			}
			if(opt[1]=='e')
			{
				scanf("%s",s2);
				int A=s1[0]-'A',B=s2[0]-'A';
				stk[A]=Merge(stk[A],stk[B]);
				stk[B]=0;
			}
		}
	}
}
