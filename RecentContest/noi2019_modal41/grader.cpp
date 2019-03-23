#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
string alice(int n,const vector<int>&p,ll x);
ll bob(const string&s);
int main(){
	freopen("data.in","r",stdin);
	int Q,min_wa,n,k,i;
	ll x;
	vector<int>p;
	string s;
	scanf("%d",&Q);
	min_wa=41;
	for(int id=1;id<=Q;id++){
		scanf("%d%lld%d",&n,&x,&k);
		p.resize(k);
		for(i=0;i<k;i++)scanf("%d",&p[i]);
		s=alice(n,p,x);
		if((int)s.length()!=n)return 1;
		for(i=0;i<n;i++){
			if(s[i]!='0'&&s[i]!='1')return 1;
		}
		for(i=0;i<k;i++)s[p[i]]='0';
		if(x!=bob(s)) min_wa=min(min_wa,k);
	}
	printf("%d\n",min_wa-1);
}
