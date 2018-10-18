#include<bits/stdc++.h>
using namespace std;

const int base=32767,M=2000000;
int nxt[M],head[base+10];
int res[2][M],state[2][M];
int ans=-1e8,n,m,k=0,ptr,nptr;
int a[110][15];
int bin[15],tot[2];

inline void upmax(int &x,const int &y){if(y>x) x=y;}

void push(int s,int num)
{
	int p=s&base;
	for(int t=head[p];t;t=nxt[t])
		if(state[k][t]==s)
		{
			upmax(res[k][t],num);
			return;
		}
	tot[k]++;
	state[k][tot[k]]=s;
	res[k][tot[k]]=num;
	nxt[tot[k]]=head[p],head[p]=tot[k];
}

int find(int s,int j,int ty)
{
	if(ty==1)
	{
		int cnt=1;
		for(int v=j+1;v<=m;v++)
		{
			int ss=(s>>bin[v])&3;
			if(ss==1) cnt++;
			if(ss==2) cnt--;
			if(!cnt) return v;
		}
	}
	else
	{
		int cnt=1;
		for(int v=j-2;v>=0;v--)
		{
			int ss=(s>>bin[v])&3;
			if(ss==2) cnt++;
			if(ss==1) cnt--;
			if(!cnt) return v;
		}
	}
	
}

int replace(int s,int p,int x)
{
	int q=(s>>bin[p])&3;
	return s-(q<<bin[p])+(x<<bin[p]);
}

void gao(int i,int j)
{
	for(int u=1;u<=tot[k^1];u++)
	{
		int s=state[k^1][u],num=res[k^1][u];
		if(s>=(1<<bin[m+1])) continue;
		int p=(s>>bin[j-1])&3,q=(s>>bin[j])&3;
		int falun=s-(p<<bin[j-1])-(q<<bin[j]);
		if(p==0&&q==0)
		{
			push(s,num);
			push(s+(1<<bin[j-1])+(2<<bin[j]),num+a[i][j]);
			push(s+(3<<bin[j-1]),num+a[i][j]);
			push(s+(3<<bin[j]),num+a[i][j]);
		}
		else if(p==0&&q>0)
		{
			push(s,num+a[i][j]);
			push(s+(q<<bin[j-1])-(q<<bin[j]),num+a[i][j]);
			if(q!=3) push(replace(s-(q<<bin[j]),find(s,j,q),3),num+a[i][j]);
			else if(!falun) upmax(ans,num+a[i][j]);
		}
		else if(p>0&&q==0)
		{
			push(s,num+a[i][j]);
			push(s-(p<<bin[j-1])+(p<<bin[j]),num+a[i][j]);
			if(p!=3) push(replace(s-(p<<bin[j-1]),find(s,j,p),3),num+a[i][j]);
			else if(!falun) upmax(ans,num+a[i][j]);
		}
		else if(p==q&&p!=3){push(replace(s-(p<<bin[j-1])-(q<<bin[j]),find(s,j,p),p),num+a[i][j]);}
		else if(p==2&&q==1){push(s-(p<<bin[j-1])-(q<<bin[j]),num+a[i][j]);}
		else if(p==3&&q==3){if(!falun)upmax(ans,num+a[i][j]);}
		else if(p==1&&q==2){if(!falun)upmax(ans,num+a[i][j]);}
		else if(p==3&&q!=3){push(replace(s-(p<<bin[j-1])-(q<<bin[j]),find(s,j,q),3),num+a[i][j]);}
		else if(p!=3&&q==3){push(replace(s-(p<<bin[j-1])-(q<<bin[j]),find(s,j,p),3),num+a[i][j]);}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]),upmax(ans,a[i][j]);
	for(int i=0;i<=9;i++) bin[i]=(i<<1);
	tot[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			k^=1;tot[k]=0;
			memset(head,0,sizeof(head));
			gao(i,j);
		}
		for(int j=1;j<=tot[k];j++)
			state[k][j]<<=2;
	}
	printf("%d\n",ans);
	return 0;
}
