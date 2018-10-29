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
const int N=100010;
int a[N],cnt0=0,tot=0,n;
int ch[N*20][2],sum[N*20],sz=0,rt[N];
int L[N],R[N],Hash[N],hs=0;
stack<pii> st;

void prework()
{
    for(int i=1;i<=tot;i++)
    {
        while(!st.empty()&&st.top().FR<a[i]) st.pop();
        L[i]=st.empty()?1:st.top().SE+1;
        st.push(pii(a[i],i));
    }
    while(!st.empty()) st.pop();
    for(int i=tot;i>=1;i--)
    {
        while(!st.empty()&&st.top().FR<=a[i]) st.pop();
        R[i]=st.empty()?tot:st.top().SE-1;
        st.push(pii(a[i],i));
    }
}

void insert(int &o,int p,int l,int r,int k)
{
    sum[o=++sz]=sum[p]+1;
    if(l==r) return;
    ch[o][0]=ch[p][0];
    ch[o][1]=ch[p][1];
    int mid=(l+r)/2;
    if(k<=mid) insert(ch[o][0],ch[p][0],l,mid,k);
    else insert(ch[o][1],ch[p][1],mid+1,r,k);
}

int query(int L,int R,int l,int r,int x)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(x<=mid) return query(ch[L][0],ch[R][0],l,mid,x);
    else return sum[ch[R][0]]-sum[ch[L][0]]+query(ch[L][1],ch[R][1],mid+1,r,x);
}

void xi_jin_ping_is_good()
{
    long long ans=0;
    for(int i=1;i<=tot;i++) Hash[i]=a[i];
    sort(Hash+1,Hash+1+tot);
    hs=unique(Hash+1,Hash+1+tot)-(Hash+1);
    for(int i=1;i<=tot;i++)
        a[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
    for(int i=1;i<=tot;i++) insert(rt[i],rt[i-1],1,hs,a[i]);
    for(int i=1;i<=tot;i++)
    {
        if(i-L[i]<=R[i]-i)for(int j=L[i];j<=i;j++)
        {
            int d=Hash[a[i]]/Hash[a[j]];
            int x=lower_bound(Hash+1,Hash+1+hs,d)-Hash;
            if(Hash[x]>d) x--;
            if(x) ans+=query(rt[i-1],rt[R[i]],1,hs,x);
        }
        else for(int j=i;j<=R[i];j++)
        {
            int d=Hash[a[i]]/Hash[a[j]];
            int x=lower_bound(Hash+1,Hash+1+hs,d)-Hash;
            if(Hash[x]>d) x--;
            if(x) ans+=query(rt[L[i]-1],rt[i],1,hs,x);
        }
    }
    ans+=1ll*cnt0*n-1ll*cnt0*(cnt0-1)/2;
    printf("%lld\n",ans%998244353);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        int x=read();
        if(!x) cnt0++;
        else a[++tot]=x;
    }
    prework();
    xi_jin_ping_is_good();
    return 0;
}