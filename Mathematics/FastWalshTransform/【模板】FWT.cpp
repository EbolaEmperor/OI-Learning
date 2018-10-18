#include<bits/stdc++.h>
#define ha 998244353
#define inv2 499122177
using namespace std;

const int N=140010;
const int OR=1,AND=2,XOR=3;
int a[N],b[N],f[N],g[N],n;

void FWT(int *a,int n,bool IFWT,int ty)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(IFWT)
				{
					if(ty==OR) a[i+j+k]=(y-x+ha)%ha;
					if(ty==AND) a[j+k]=(x-y+ha)%ha;
					if(ty==XOR) a[j+k]=1ll*(x+y)*inv2%ha,a[i+j+k]=1ll*(x-y+ha)*inv2%ha;
				}
				else
				{
					if(ty==OR) a[i+j+k]=(x+y)%ha;
					if(ty==AND) a[j+k]=(x+y)%ha;
					if(ty==XOR) a[j+k]=(x+y)%ha,a[i+j+k]=(x-y+ha)%ha; 
				}
			} 
}

void gao(int ty)
{
	memcpy(f,a,sizeof(f));
	memcpy(g,b,sizeof(g));
	FWT(g,n,0,ty);
	FWT(f,n,0,ty);
	for(int i=0;i<n;i++)
		f[i]=1ll*f[i]*g[i]%ha;
	FWT(f,n,1,ty);
	for(int i=0;i<n;i++)
		printf("%d ",f[i]);
	puts("");
}

int main()
{
	scanf("%d",&n);
	n=1<<n;
	for(int i=0;i<n;i++) scanf("%d",a+i);
	for(int i=0;i<n;i++) scanf("%d",b+i);
	gao(OR);gao(AND);gao(XOR);
	return 0;
}
