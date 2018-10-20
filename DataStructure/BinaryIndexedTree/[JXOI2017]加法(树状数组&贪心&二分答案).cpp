#include<bits/stdc++.h>
#define FR first
#define SE second
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

typedef pair<int,int> pii;
typedef long long LL;
const int N=200010;
pii seg[N];
int n,m,k,a;
int A[N];
LL bit[N];
priority_queue<pii> pq;

inline int lowbit(const int &x){return x&-x;}
void add(int p,int x){for(;p<=n+1;p+=lowbit(p))bit[p]+=x;}
LL qry(int p){LL res=0;for(;p;p-=lowbit(p))res+=bit[p];return res;}

bool check(int x)
{
    memset(bit,0,sizeof(LL)*(n+3));
    for(int i=1;i<=n;i++)
        add(i,A[i]),add(i+1,-A[i]);
    int p=1,ans=0;
    while(!pq.empty()) pq.pop();
    for(int i=1;i<=n;i++)
    {
        while(p<=m&&seg[p].FR<=i) pq.push(pii(seg[p].SE,seg[p].FR)),p++;
        while(qry(i)<x)
        {
            if(pq.empty()) return 0;
            pii t=pq.top();pq.pop();
            if(t.FR<i) return 0;
            add(t.SE,a);add(t.FR+1,-a);
            if(++ans>k) return 0;
        }
    }
    return 1;
}

int main()
{
    for(int T_T=read();T_T;T_T--)
    {
        int l=INT_MAX;
        n=read();m=read();k=read();a=read();
        for(int i=1;i<=n;i++) l=min(l,A[i]=read());
        for(int i=1;i<=m;i++) seg[i].FR=read(),seg[i].SE=read();
        sort(seg+1,seg+1+m);
        int r=l+k*a,mid;
        while(l<=r)
        {
            mid=(l+r)/2;
            if(check(mid)) l=mid+1;
            else r=mid-1;
        }
        printf("%d\n",check(l)?l:l-1);
    }
    return 0;
}