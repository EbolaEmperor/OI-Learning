#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=50000;
unordered_map<int,LL> f;
LL _f[N];

LL F(int w)
{
    if(w<N) return _f[w];
    if(f.count(w)) return f[w];
    LL res=0;
    for(int k=2,dv;k<=w;k=dv+1)
    {
        dv=w/(w/k);
        res+=F(w/k)*(dv-k+1);
    }
    return f[w]=res;
}

int main()
{
    _f[1]=1;
    for(int w=2;w<N;w++)
        for(int k=2,dv;k<=w;k=dv+1)
        {
            dv=w/(w/k);
            _f[w]+=_f[w/k]*(dv-k+1);
        }
    int n;cin>>n;
    cout<<F(n)<<endl;
    return 0;
}