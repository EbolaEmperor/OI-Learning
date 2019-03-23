#include<bits/stdc++.h>
#include "sequence.hpp"
using namespace std;

vector<string> gao1(int n=10)
{
    vector<string> ans,ask;
    ans.resize(n);ask.resize(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            ask[j]=(i==j)?"1":"0";
        ans[i]=prod(ask);
    }
    return ans;
}

string numtostr(int n)
{
    if(n==0) return "0";
    string res;
    while(n) res+=(n%10+'0'),n/=10;
    reverse(res.begin(),res.end());
    return res;
}

vector<string> gao2(int n=25)
{
    vector<string> ans,ask;
    ans.resize(n);ask.resize(n);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<25;j++) ask[j]="0";
        ask[3*i]="10000";
        ask[3*i+1]="100";
        ask[3*i+2]="1";
        string tmp=prod(ask);
        int num=0;
        for(int j=0;j<tmp.size();j++)
            num=num*10+(tmp[j]-'0');
        ans[3*i+2]=numtostr(num%100);
        ans[3*i+1]=numtostr(num/100%100);
        ans[3*i]=numtostr(num/10000);
    }
    for(int j=0;j<25;j++) ask[j]="0";
    ask[24]="1";
    ans[24]=prod(ask);
    return ans;
}

string Mns(string a,string b)
{
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    vector<int> res(a.size());
    for(int i=0;i<a.size();i++) res[i]=(a[i]-'0');
    for(int i=0;i<b.size();i++) res[i]-=(b[i]-'0');
    for(int i=0;i<res.size();i++)
        if(res[i]<0) res[i]+=10,res[i+1]--;
    string ress;
    for(int x : res) ress+=(x+'0');
    reverse(ress.begin(),ress.end());
    return ress;
}

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

void delzero(string &s)
{
    int p=0;
    while(s[p]=='0') p++;
    s=s.substr(p,s.size()-p);
    if(s.empty()) s="0";
}

vector<string> gao3(int n=16)
{
    string _e49="10000000000000000000000000000000000000000000000000";
    vector<string> ask,g,ans;
    ans.resize(n);ask.resize(n);g.resize(8);
    for(int i=0;i<8;i++)
    {
        for(auto &c : ask) c="0";
        ask[2*i]="1";
        ask[2*i+1]=_e49;
        g[i]=prod(ask);
    }

    for(auto &c : ask) c="0";
    ask[1]="1";ask[3]="100000000";ask[5]="10000000000000000";ask[7]="1000000000000000000000000";
    string f1=prod(ask),h;
    for(int j=0;j<8;j++)
    {
        if((int)f1.size()-1-j<0) break;
        h+=f1[f1.size()-1-j];
    }
    if(h.empty()) h="0";
    reverse(h.begin(),h.end());
    for(int i=0;i<4;i++)
    {
        string tmp=Mns(g[i],Mul(h,_e49));
        for(int j=0;j<57;j++)
        {
            if((int)tmp.size()-1-j<0) break;
            ans[2*i]+=tmp[tmp.size()-1-j];
        }
        if(ans[2*i].empty()) ans[2*i]="0";
        reverse(ans[2*i].begin(),ans[2*i].end());
        tmp=Mns(g[i],ans[2*i]);
        ans[2*i+1]=tmp.substr(0,tmp.size()-49);
        if(i==3) break;
        f1=Mns(f1,ans[2*i+1]);
        f1=f1.substr(0,f1.size()-8);
        h=string();
        for(int j=0;j<8;j++)
        {
            if((int)f1.size()-1-j<0) break;
            h+=f1[f1.size()-1-j];
        }
        if(h.empty()) h="0";
        reverse(h.begin(),h.end());
    }

    for(auto &c : ask) c="0";
    ask[9]="1";ask[11]="100000000";ask[13]="10000000000000000";ask[15]="1000000000000000000000000";
    f1=prod(ask);h=string();
    for(int j=0;j<8;j++)
    {
        if((int)f1.size()-1-j<0) break;
        h+=f1[f1.size()-1-j];
    }
    if(h.empty()) h="0";
    reverse(h.begin(),h.end());
    for(int i=4;i<8;i++)
    {
        string tmp=Mns(g[i],Mul(h,_e49));
        for(int j=0;j<57;j++)
        {
            if((int)tmp.size()-1-j<0) break;
            ans[2*i]+=tmp[tmp.size()-1-j];
        }
        if(ans[2*i].empty()) ans[2*i]="0";
        reverse(ans[2*i].begin(),ans[2*i].end());
        tmp=Mns(g[i],ans[2*i]);
        ans[2*i+1]=tmp.substr(0,tmp.size()-49);
        if(i==7) break;
        f1=Mns(f1,ans[2*i+1]);
        f1=f1.substr(0,f1.size()-8);
        h=string();
        for(int j=0;j<8;j++)
        {
            if((int)f1.size()-1-j<0) break;
            h+=f1[f1.size()-1-j];
        }
        if(h.empty()) h="0";
        reverse(h.begin(),h.end());
    }

    for(auto &s : ans) delzero(s);
    return ans;
}

vector<string> guess(int n,int a,int b,int t)
{
	if(t==1) return gao1();
	if(t==2||t==3) return gao2();
    return gao3();
}