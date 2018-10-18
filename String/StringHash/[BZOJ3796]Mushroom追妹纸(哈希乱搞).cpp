#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=50010,hs=10007;
char s1[N],s2[N],s3[N];
int base[N],h1[N],h2[N],h3;
ULL Base[N],H1[N],H2[N],H3;
int nxt1[N],nxt2[N];
int len1,len2,len3;
int h[hs],nxt[N],tot;
ULL stu[N];
 
ULL gethash(ULL *h,int l,int r){return h[r]-(l>0?h[l-1]:0)*Base[r-l+1];}
int gethash2(int *h,int l,int r){return (h[r]-(l>0?h[l-1]:0)*base[r-l+1]%hs+hs)%hs;}
 
void push(ULL s,int ss)
{
	int i;for(i=h[ss];nxt[i];i=nxt[i]);
	if(i) nxt[i]=++tot;
	else h[ss]=++tot;
	stu[tot]=s;
}

bool find(ULL s,int ss)
{
	for(int i=h[ss];i;i=nxt[i])
		if(stu[i]==s) return 1;
	return 0;
}

bool check(int x)
{
	memset(h,0,sizeof(h));tot=0;
	memset(nxt,0,sizeof(nxt));
	memset(stu,0,sizeof(stu));
	for(int i=0;i+x<=len1;i++)
	  if(nxt1[i]==len1||i+x<nxt1[i]+len3)
	    push(gethash(H1,i,i+x-1),gethash2(h1,i,i+x-1));
	for(int i=0;i+x<=len2;i++)
	  if(nxt2[i]==len2||i+x<nxt2[i]+len3)
	    if(find(gethash(H2,i,i+x-1),gethash2(h2,i,i+x-1))) return 1;
	return 0;
}

int main()
{
	scanf("%s%s%s",s1,s2,s3);
	len1=strlen(s1);len2=strlen(s2);len3=strlen(s3);
	for(int i=0;i<len1;i++) h1[i]=(h1[i-1]*233+s1[i]-'a')%hs;
	for(int i=0;i<len2;i++) h2[i]=(h2[i-1]*233+s2[i]-'a')%hs;
	for(int i=0;i<len1;i++) H1[i]=H1[i-1]*2309+s1[i]-'a';
	for(int i=0;i<len2;i++) H2[i]=H2[i-1]*2309+s2[i]-'a';
	for(int i=0;i<len3;i++) h3=(h3*233+s3[i]-'a')%hs,H3=H3*2309+s3[i]-'a';
	base[0]=Base[0]=1;nxt1[len1]=len1;nxt2[len2]=len2;
	for(int i=1;i<N;i++) base[i]=base[i-1]*233%hs,Base[i]=Base[i-1]*2309;
	for(int i=len1-1;i>=0;i--) nxt1[i]=i+len3<=len1&&gethash2(h1,i,i+len3-1)==h3&&gethash(H1,i,i+len3-1)==H3?i:nxt1[i+1];
	for(int i=len2-1;i>=0;i--) nxt2[i]=i+len3<=len2&&gethash2(h2,i,i+len3-1)==h3&&gethash(H2,i,i+len3-1)==H3?i:nxt2[i+1];
	
	int l=0,r=min(len1,len2),ans;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
