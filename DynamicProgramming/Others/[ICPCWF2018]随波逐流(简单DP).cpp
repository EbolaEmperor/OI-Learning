#include<bits/stdc++.h>
using namespace std;

const int N=2510;
string s[N];
int f[N*200],n;
int ans1,ans2;
int X[N],Y[N];

void init(int len)
{
    int x=1,y=0;
    for(int i=1;i<=n;i++)
    {
        if(y+s[i].size()>len)
            Y[i-1]=len+1,x++,y=0;
        y+=s[i].size()+1;
        X[i]=x;Y[i]=y;
    }
    Y[n]=len+1;
}

int idx(int x,int y,int m){return (x-1)*m+y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

int main()
{
    ios::sync_with_stdio(0);
    int mx=0;cin>>n;
    for(int i=1;i<=n;i++)
        cin>>s[i],mx=max(mx,(int)s[i].size());
    for(int len=mx;len<=n*80;len++)
    {
        init(len);
        for(int i=1;i<=n;i++)
        {
            if(Y[i]>len) continue;
            int x=X[i],y=Y[i],p=idx(x,y,len);
            if(x>1) upmax(f[p],f[idx(x-1,y,len)]);
            if(x>1) upmax(f[p],f[idx(x-1,y-1,len)]);
            if(x>1&&y<len) upmax(f[p],f[idx(x-1,y+1,len)]);
            if(++f[p]>ans2) ans2=f[p],ans1=len;
        }
        for(int i=1;i<=n;i++) f[idx(X[i],Y[i],len)]=0;
    }
    printf("%d %d\n",ans1,ans2);
    return 0;
}