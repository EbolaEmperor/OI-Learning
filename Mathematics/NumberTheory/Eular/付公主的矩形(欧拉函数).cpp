#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define Max 1000100
using namespace std;

int phi[Max],cnt=0,ans=0,n;
bool mark[Max];
int prime[Max],tot=0;

void getphi()
{
    memset(mark,0,sizeof(mark));
    phi[1]=1;
    for(int i=2;i<=n+1;i++)
    {
       if(!mark[i])
       {
           prime[++tot]=i;
           phi[i]=i-1;
       }
	   if(n%(i-1)==0) ans+=phi[i];
       for(int j=1;j<=tot&&i*prime[j]<=n+1;j++)
       {
           mark[i*prime[j]]=1;
           if(i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j];
           else phi[i*prime[j]]=phi[i]*(prime[j]-1);
       }
    }
}

int main()
{
	cin>>n;
	getphi();
	cout<<(ans+1)/2<<endl;
	return 0;
}
