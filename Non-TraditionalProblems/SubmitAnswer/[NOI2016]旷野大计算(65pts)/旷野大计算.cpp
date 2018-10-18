#include<iostream>
#include<cstdio>
using namespace std;

int cnt=0;
int input()
{
	cout<<"I"<<endl;
	return ++cnt;
}
int left(int p,int k)
{
	printf("< %d %d\n",p,k);
	return ++cnt;
}
int right(int p,int k)
{
	printf("> %d %d\n",p,k);
	return ++cnt;
}
int addc(int p,double k)
{
	printf("C %d %.15lf\n",p,k);
	return ++cnt;
}
int add(int p,int q)
{
	printf("+ %d %d\n",p,q);
	return ++cnt;
}
int output(int p)
{
	printf("O %d\n",p);
	return ++cnt;
}
int dev(int p)
{
	printf("- %d\n",p);
	return ++cnt;
}
int S(int p)
{
	printf("S %d\n",p);
	return ++cnt;
}
int gp(int p)
{
	return S(left(p,2333));
}

int sgn(int x)
{return addc(left(S(left(x,2333)),1),-1);}


int Xor(int p,int q)
{
	int s=add(p,q);
	int tmp=left(dev(gp(addc(s,-1.5))),1);
	return add(s,tmp);
}

int ans[100];

int min0(int r)
{
    cout.setf(ios::fixed);
    cout.precision(30);
    int x=addc(r,1e-9);
    int p=gp(x);
    int py=left(p,151);
    int s=S(add(right(x,150),py));
    int bf=addc(dev(s),0.5);
    int m=left(bf,152);
    return dev(add(m,py));
}
int aid[23];
void relax(int a,int b)
{
    int s=add(aid[a],aid[b]);
    aid[a]=add(aid[a],min0(add(dev(aid[a]),aid[b])));
    aid[b]=add(s,dev(aid[a]));
}
int main()
{
    freopen("9.txt","w",stdout);
    for(int i=1;i<=16;i++) aid[i]=input();
    for(int i=1;i<=16;i++)
    {
        for(int j=i+1;j<=16;j++) relax(i,j);
    }
    for(int i=1;i<=16;i++) output(aid[i]);
}
