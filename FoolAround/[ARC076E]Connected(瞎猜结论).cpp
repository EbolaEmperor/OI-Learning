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
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=100010;
typedef pair<int,int> pii;
vector<pii> a[5];
stack<int> st;
bool vis[N];
int R,C,n;

pii check(int x,int y)
{
    if(x==0) return pii(1,y);
    if(y==C) return pii(2,x);
    if(x==R) return pii(3,y);
    if(y==0) return pii(4,x);
    return pii(0,0);
}

int main()
{
    int x1,y1,x2,y2;pii d1,d2;
    R=read();C=read();n=read();
    for(int i=1;i<=n;i++)
    {
        x1=read();y1=read();x2=read();y2=read();
        d1=check(x1,y1);d2=check(x2,y2);
        if(!d1.first||!d2.first) continue;
        a[d1.first].push_back(pii(d1.second,i));
        a[d2.first].push_back(pii(d2.second,i));
    }
    sort(a[1].begin(),a[1].end());
    sort(a[2].begin(),a[2].end());
    sort(a[3].begin(),a[3].end(),[](pii x,pii y){return x>y;});
    sort(a[4].begin(),a[4].end(),[](pii x,pii y){return x>y;});
    for(int i=1;i<=4;i++)for(pii x : a[i])
    {
        int y=x.second;
        if(!vis[y]) st.push(y),vis[y]=1;
        else if(st.top()!=y) return !puts("NO");
        else st.pop();
    }
    puts("YES");
    return 0;
}