#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

priority_queue<int> q;
int a[200010];

int main()
{
    int n=read();long long ans=0;
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++)
    {
        q.push(-a[i]);ans+=a[i];
        if(i&1) ans+=2ll*q.top(),q.pop();
    }
    cout<<ans<<endl;
    return 0;
}