#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int inv2=500000004;
const int N=500010;
int n,k0[N],k1[N],k2[N];
char s[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

struct SuffixArray
{
    int sa[N],rk[N],c[N];
    int x[N],y[N],tmp[N];
    int height[N],sh[21][N],lg2[N];
    void build(int n,int m)
    {
        for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
        for(int i=1;i<m;i++) c[i+1]+=c[i];
        for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=n;k<<=1)
        {
            int num=0;
            for(int i=n-k+1;i<=n;i++) y[++num]=i;
            for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
            for(int i=1;i<=n;i++) c[tmp[i]]++;
            for(int i=1;i<m;i++) c[i+1]+=c[i];
            for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
            num=1;swap(x,y);x[sa[1]]=1;
            for(int i=2;i<=n;i++)
                x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
            if(num==n) break;
            m=num;
        }
        for(int i=1;i<=n;i++) rk[sa[i]]=i;
        for(int i=1,k=0;i<=n;i++)
        {
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) k++;
            height[rk[i]]=k;
        }
        for(int i=1;i<=n;i++) sh[0][i]=height[i];
        for(int k=1;k<=20;k++)
            for(int i=1;i<=n;i++)
                sh[k][i]=min(sh[k-1][i],sh[k-1][i+(1<<k-1)]);
        for(int i=2;i<=n;i++)
            lg2[i]=lg2[i>>1]+1;
    }
    int lcp(int x,int y)
    {
        if(x==y) return n-x+1;
        int l=rk[x],r=rk[y];
        if(l>r) swap(l,r);l++;
        int len=r-l+1,k=lg2[len];
        return min(sh[k][l],sh[k][r-(1<<k)+1]);
    }
} A,B;

void gao(int d)
{
    for(int i=d<<1|1;i<=n;i+=d)
    {
        int y=min(A.lcp(i-d,i),d);
        int x=B.lcp(n-(i-1)+1,n-(i-d-1)+1);
        if(x+y<d+1||!y) continue;
        int t=i-x+d;
        if(t>=i)
        {
            t--;
            int w=max(d,x);
            int w1=mns(add(w,inv2),t),w0=1ll*inv2*mns(1ll*t*t%ha,1ll*t*(2*w+1)%ha)%ha;
            k0[t+1]=add(k0[t+1],w0);
            k1[t+1]=add(k1[t+1],w1);
            k2[t+1]=add(k2[t+1],inv2);
            k0[i+y]=mns(k0[i+y],w0);
            k1[i+y]=mns(k1[i+y],w1);
            k2[i+y]=mns(k2[i+y],inv2);
        }
        else
        {
            t=i-1-x+d;
            int w1=mns(add(d,inv2),t),w0=1ll*inv2*mns(1ll*t*t%ha,1ll*t*(2*d+1)%ha)%ha;
            k0[i]=add(k0[i],w0);
            k1[i]=add(k1[i],w1);
            k2[i]=add(k2[i],inv2);
            k0[i+y]=mns(k0[i+y],w0);
            k1[i+y]=mns(k1[i+y],w1);
            k2[i+y]=mns(k2[i+y],inv2);
        }
        
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    A.build(n,233);
    reverse(s+1,s+1+n);
    B.build(n,233);
    for(int i=1;i<=n;i++) gao(i);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        k0[i]=add(k0[i],k0[i-1]);
        k1[i]=add(k1[i],k1[i-1]);
        k2[i]=add(k2[i],k2[i-1]);
        ans=(ans+1ll*k2[i]*i%ha*i+1ll*k1[i]*i+k0[i])%ha;
        cout<<ans<<"\n";
    }
    return 0;
}
