#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353;
unordered_map<LL,int> f,g,h;

int G(LL n) //长为n的线段树中所有左子区间的总长 
{
    if(g.count(n)) return g[n];
    else return g[n]=((n+1)/2+G(n/2)+G((n+1)/2))%ha;
}

int H(LL n) //长为n的线段树中所有右子区间的总长 
{
    if(h.count(n)) return h[n];
    else return h[n]=(n/2+H(n/2)+H((n+1)/2))%ha;
}

int F(LL n) //长为n的线段树的答案 
{
    if(f.count(n)) return f[n];
    else return f[n]=(F(n/2)+(n/2)%ha*G((n+1)/2)+F((n+1)/2)+(n+1)/2%ha*H(n/2)+n-1)%ha;
}

int main()
{
    g[1]=h[1]=0;
    f[1]=1;
    LL n;
    cin>>n;
    cout<<F(n)<<endl;
    return 0;
}
