#include<bits/stdc++.h>
using namespace std;

int n,m,a[3010];
int sum[3010];
int f[3010][3010];
int q[3010],head,tail;

inline int min(int a,int b){return a<b?a:b;}
inline double k(int x,int y,int z){return (double)(f[x][y]-f[x][z]+sum[y]*sum[y]-sum[z]*sum[z])/(double)(sum[y]-sum[z]);}

int main()
{
	cin>>n>>m;
	sum[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		sum[i]=sum[i-1]+a[i];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++) f[1][i]=sum[i]*sum[i];
	for(int l=2;l<=m;l++)
	{
		head=1,tail=0;
		for(int i=1;i<=n;i++)
		{
			while(head<tail&&k(l-1,q[head],q[head+1])<2*sum[i]) head++;
			int j=q[head];
			f[l][i]=f[l-1][j]+(sum[j]-sum[i])*(sum[j]-sum[i]);
			while(head<tail&&k(l-1,q[tail-1],q[tail])>k(l-1,q[tail],i)) tail--;
			q[++tail]=i;
		}
	}
	cout<<m*f[m][n]-sum[n]*sum[n]<<endl;
	return 0;
}
