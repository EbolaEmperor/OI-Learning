#include<bits/stdc++.h>
#define R register
#define ha 1000000007
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
template<typename I> inline void read(I &x)
{
	x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
}
inline void readarr(bool *s)
{
	int tot=0;char c=Get();
	while(c!='#'&&c!='.') c=Get();
	while(c=='#'||c=='.') s[++tot]=(c=='#'),c=Get();
}

typedef long long LL;
const int N=1010;
bool black[N][N];
int n,m;
LL K;

struct Matrix
{
	int a[3][3];
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;
		for(R int i=0;i<3;i++)
			for(R int j=0;j<3;j++)
				for(R int k=0;k<3;k++)
					C[i][j]=(C[i][j]+1ll*A[i][k]*B[k][j])%ha;
		return C;
	}
	
	friend Matrix operator ^ (Matrix &A,LL b)
	{
		Matrix ans;
		for(R int i=0;i<3;i++) ans[i][i]=1;
		for(;b;b>>=1,A=A*A) if(b&1) ans=ans*A;
		return ans;
	}
};

int Pow(int a,LL b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int main()
{
	read(n);read(m);read(K);
	for(R int i=1;i<=n;i++) readarr(black[i]);
	int plugup=0,plugleft=0,blacknum=0;
	for(R int i=1;i<=n;i++)
		for(R int j=1;j<=m;j++)
			blacknum+=black[i][j];
	for(R int i=1;i<=n;i++) plugleft+=(black[i][1]&&black[i][m]);
	for(R int i=1;i<=m;i++) plugup+=(black[1][i]&&black[n][i]);
	int cnt1=0,cnt2=0;
	for(R int i=1;i<=n;i++)
		for(R int j=1;j<=m;j++)
		{
			cnt1+=(black[i][j]&&black[i+1][j]);
			cnt2+=(black[i][j]&&black[i][j+1]);
		}
	if(plugleft&&plugup||K==1) puts("1");
	else if(!plugleft&&!plugup) printf("%d\n",Pow(blacknum,K-1));
	else
	{
		if(!plugup&&plugleft)
		{
			swap(plugleft,plugup);
			swap(cnt1,cnt2);
		}
		Matrix A,B;
		A[0][0]=A[1][1]=blacknum;
		A[1][2]=1;A[2][2]=plugup;
		A=A^(K-2);
		B[0][0]=blacknum;
		B[1][0]=cnt1;
		B[2][0]=1ll*plugup*cnt1%ha;
		B=A*B;
		printf("%d\n",(B[0][0]-B[1][0]+ha)%ha);
	}
	return 0;
}
