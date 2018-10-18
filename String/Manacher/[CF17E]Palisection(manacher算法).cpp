#include<bits/stdc++.h>
#define Mod 51123987
using namespace std;
 
typedef long long LL;
const int N=2000010;
char s[N],ss[2*N];
int p[2*N];
LL sum=0;
LL bg[2*N],ed[2*N];
 
int manacher()
{
	int l=strlen(s),len=0;
	ss[len++]='$';ss[len++]='#';
	for(int i=0;i<l;i++)
		ss[len++]=s[i],ss[len++]='#';
	ss[len++]='?';
	int mx=0,id;
	for(int i=1;i<=len;i++)
	{
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i-p[i]]==ss[i+p[i]]) p[i]++;
		sum=(sum+p[i]/2)%Mod;
		if(i+p[i]>mx) mx=i+p[i],id=i;
	}
	return len;
}
 
int main()
{
	int n;
	scanf("%d%s",&n,s);
	int len=manacher();
	sum=(sum*(sum-1)/2)%Mod;
	for(int i=2;i<=len;i+=2)
		bg[i-p[i]+2]++,bg[i+2]--,
		ed[i]++,ed[i+p[i]]--;
	for(int i=1;i<=len;i+=2)
		bg[i-p[i]+2]++,bg[i+1]--,
		ed[i+1]++,ed[i+p[i]]--;
	for(int i=2;i<=len;i+=2)
		bg[i]=(bg[i]+bg[i-2])%Mod,
		ed[i]=(ed[i]+ed[i-2])%Mod;
	bg[len+1]=0;
	for(int i=len-1;i>0;i-=2)
		bg[i]=(bg[i]+bg[i+2])%Mod;
	for(int i=2;i<=len;i+=2)
		sum=((sum-ed[i]*bg[i+2]%Mod)+Mod)%Mod;
	cout<<sum<<endl;
	return 0;
}