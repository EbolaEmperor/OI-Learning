#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=160;
const int MOD=998244353;
int f[N][N][N];
int suml[N][N][N],sumr[N][N][N];
int r[N];

int main()
{
	int n,mxr=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>r[i];
		mxr=max(mxr,r[i]+1);
	}
	memset(suml,0,sizeof(suml));
	memset(sumr,0,sizeof(sumr));
	for(int i=0;i<=mxr;i++)
	{
		suml[0][i][mxr]=1;
		sumr[0][0][i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		memset(f,0,sizeof(f));
		for(int x=1;x<=r[i];x++)
		{
			for(int l=0;l<x;l++)
				for(int r=x+1;r<=mxr;r++)
					f[x][l][r]=(suml[l][l][r]+sumr[r][l][r])%MOD;
			for(int r=x;r<=mxr;r++)
				f[x][x][x]=(f[x][x][x]+suml[x][mxr][r])%MOD;
			for(int y=0;y<=mxr;y++)
				if(x!=y) f[x][x][x]=(f[x][x][x]+suml[y][y][x]+sumr[y][x][y])%MOD;
		}
		memset(suml,0,sizeof(suml));
		memset(sumr,0,sizeof(sumr));
		for(int x=1;x<=r[i];x++)
			for(int l=0;l<=mxr;l++)
				for(int r=x;r<=mxr;r++)
					suml[x][l][r]=(f[x][l][r]+((l>0)?suml[x][l-1][r]:0))%MOD;
		for(int x=1;x<=r[i];x++)
			for(int l=0;l<=x;l++)
				for(int r=mxr;r>=0;r--)
					sumr[x][l][r]=(f[x][l][r]+sumr[x][l][r+1])%MOD;
	}
	int ans=0;
	for(int x=1;x<=r[n];x++)
		for(int l=0;l<=x;l++)
			for(int r=x;r<=mxr;r++)
				ans=(ans+f[x][l][r])%MOD;
	cout<<ans<<endl;
	return 0;
}
