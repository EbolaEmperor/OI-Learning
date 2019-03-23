//���Ƿ���ѡ�ֵĽ����� 
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
//ע��ʵ�ʲ��Ե�ʱ��һ����ʹ����Щ�������������Ҫʹ�ÿ������п���ȥ 
namespace Helper_Functions
{
std::string Mul(std::string a,std::string b)
{
	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());
	std::vector<int> v(a.size()+b.size()+30);
	for(int i=0;i<(int)a.size();++i)
		for(int j=0;j<(int)b.size();++j)
			v[i+j]+=(a[i]-'0')*(b[j]-'0');
	for(int i=0;i+1<(int)v.size();++i)
		v[i+1]+=v[i]/10,v[i]%=10;
	while(v.size()&&!v.back()) v.pop_back();
	std::string s;
	for(int i=0;i<(int)v.size();++i)
		s.push_back(v[i]+48);
	reverse(s.begin(),s.end());
	if(s=="") s="0"; return s;
}
std::string Add(std::string a,std::string b)
{
	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());
	std::vector<int> v(a.size()+b.size()+3);
	for(int i=0;i<(int)a.size();++i)
		v[i]+=a[i]-'0';
	for(int i=0;i<(int)b.size();++i)
		v[i]+=b[i]-'0';
	for(int i=0;i+1<(int)v.size();++i)
		v[i+1]+=v[i]/10,v[i]%=10;
	while(v.size()&&!v.back()) v.pop_back();
	std::string s;
	for(int i=0;i<(int)v.size();++i)
		s.push_back(v[i]+48);
	reverse(s.begin(),s.end());
	if(s=="") s="0"; return s;
}
bool validate(std::string t)
{
	if(t=="0") return 1;
	if(!t.size()) return 0;
	for(int i=0;i<(int)t.size();++i)
		if(t[i]<'0'||t[i]>'9') return 0;
	if(t[0]=='0') return 0;
	return 1;
}
}
int n_,cq=0,b_; std::string v_[233];
#define Fail(aug) {puts(aug); exit(0);}
std::string prod(std::vector<std::string> q)
{
	++cq; using namespace Helper_Functions;
	if(cq>10) Fail("you're out of queries!");
	if((int)q.size()!=n_) Fail("vector size !=n");
	std::string g="0";
	for(int i=0;i<n_;++i)
	{
		if(!validate(q[i]))
			Fail("your argument is not a valid number");
		if((int)q[i].size()>b_)
			Fail("query number is too long");
		g=Add(g,Mul(q[i],v_[i]));
	}
	return g;
}
std::vector<std::string> guess(int,int,int,int);
int main()
{
	freopen("ex_s5.in","r",stdin);
	int a,t; using namespace Helper_Functions;
	std::cin>>n_>>a>>b_>>t;
	for(int i=0;i<n_;++i)
	{
		std::cin>>v_[i];
		if(!validate(v_[i])||(int)v_[i].size()>a)
			throw "invalid input";
	} 
	std::vector<std::string> g=guess(n_,a,b_,t);
	if((int)g.size()!=n_) Fail("vector size !=n");
	for(int i=0;i<n_;++i)
		if(g[i]!=v_[i])
		{
			printf("Wrong answer on %d\n",i);
			Fail("return value is wrong");
		}
	printf("Well done! You made %d queries.\n",cq);
}
