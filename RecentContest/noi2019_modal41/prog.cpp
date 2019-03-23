#include<bits/stdc++.h>
using namespace std;

string alice(int n,const vector<int> &p,long long x)
{
    string res,xs;
    while(x) xs+='0'+(x&1),x>>=1;
    static int bad[150];
    memset(bad,0,sizeof(bad));
    for(int k : p) bad[k]=1;
    int pos=0;
    for(int i=0;i<n&&pos<xs.size();i+=3)
    {
        int cnt=bad[i]+bad[i+1]+bad[i+2];
        if(cnt>=2){res+="000";continue;}
        if(cnt==1||pos==xs.size()-1)
        {
            if(xs[pos]=='1'){res+=bad[i+2]?"110":"001";pos++;continue;}
            if(!bad[i]){res+="100";pos++;continue;}
        }
        if(xs[pos]=='0'&&xs[pos+1]=='0'){res+="010";pos+=2;continue;}
        if(xs[pos]=='0'&&xs[pos+1]=='1'){res+="011";pos+=2;continue;}
        if(xs[pos]=='1'&&xs[pos+1]=='0'){res+="101";pos+=2;continue;}
        if(xs[pos]=='1'&&xs[pos+1]=='1'){res+="111";pos+=2;continue;}
    }
    while(res.size()<n) res+="000";
    return res;
}

long long bob(const string &s)
{
    string ress;
    for(int i=0;i<s.size();i+=3)
    {
        string tmp=s.substr(i,3);
        if(tmp=="000") continue;
        if(tmp=="001"||tmp=="110") ress+="1";
        if(tmp=="100") ress+="0";
        if(tmp=="010") ress+="00";
        if(tmp=="011") ress+="01";
        if(tmp=="101") ress+="10";
        if(tmp=="111") ress+="11";
    }
    long long res=0;
    for(int i=ress.size()-1;i>=0;i--)
        res=res<<1|(ress[i]-'0');
    return res;
}
