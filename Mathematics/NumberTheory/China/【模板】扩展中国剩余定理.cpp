#include<bits/stdc++.h>
using namespace std;

typedef __int128 LLL;
struct Equ{LLL b,m;};

LLL read()
{
	LLL x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return x;
}
void write(LLL x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

LLL ExGcd(LLL a,LLL b,LLL &x,LLL &y)
{
	if(b==0){x=1;y=0;return a;}
	LLL g=ExGcd(b,a%b,x,y);
	LLL t=x;x=y;y=t-(a/b)*y;
	return g;
}

Equ ExCRT(Equ a1,Equ a2)
{
	LLL k1,k2;
	LLL g=ExGcd(a1.m,a2.m,k1,k2);
	LLL c=a2.b-a1.b;
	if(c%g!=0) puts("No!"),exit(0);
	k1=k1*(c/g)%(a2.m/g);
	LLL x=k1*a1.m+a1.b;
	LLL lcm=a1.m/g*a2.m;
	x=(x%lcm+lcm)%lcm;
	return Equ{x,lcm};
}

int main()
{
	int n;
	Equ last,now;
	scanf("%d",&n);
	last.m=read();last.b=read();
	for(int i=2;i<=n;i++)
	{
		now.m=read();now.b=read();
		last=ExCRT(last,now);
	}
	write(last.b);
	return 0;
}
