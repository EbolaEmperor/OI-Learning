#include<cstdio>

namespace IO
{
	#define read input_integer
	template <typename T> void input_integer(T &x)
	{
		x=0;
		char c=getchar();
		T fg=1;
		while(c!='-'&&(!(c>='0'&&c<='9'))) c=getchar();
		if(c=='-') fg=-1,c=getchar();
		while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
		x*=fg;
	}
	template <typename T> void input_real(T &x)
	{
		long long integer;
		input_integer<long long>(integer);
		x=(T)integer;
		long long n=1;
		char c=getchar();
		while(c>='0'&&c<='9') n*=10,x+=(T)(c-'0')/n,c=getchar();
	}
	template <typename T> void output(T x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) output<T>(x/10);
		putchar(x%10+'0');
	}
	template <typename T> void outputln(T x)
	{
		output<T>(x);
		putchar('\n');
	}
}

template <typename T> T max(T x,T y){return x>y?x:y;}

using namespace IO;

int c[2010],s[2010];
int f[2010][2010];

int main()
{
	int n;
	read<int>(n);
	for(int i=n;i>=1;i--) read<int>(c[i]);
	s[0]=0;
	for(int i=1;i<=n;i++) s[i]=s[i-1]+c[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			f[i][j]=f[i][j-1];
			int x=2*j;
			if(x<=i) f[i][j]=max<int>(f[i][j],s[i]-f[i-x][x]);
			if(--x<=i) f[i][j]=max<int>(f[i][j],s[i]-f[i-x][x]);
		}
	outputln<int>(f[n][1]);
	return 0;
}
