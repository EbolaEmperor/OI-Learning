#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
template <class I>inline void print(I x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}
inline void prints(const char *s)
{
    int len=strlen(s);
    for(int i=0;i<len;i++) putc(s[i]);
    putc('\n');
}

typedef long long LL;
const int N=1000010;
vector<int> ans;
int fa[N],ToT,n,m,k,done;
int bp[N],bcnt;
int bit[N];
char s[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline int lowbit(const int &x){return x&-x;}
void reset(int len){memset(bit,0,sizeof(int)*(len+1));n=len;}
void add(int p,int x){for(p++;p<=n;p+=lowbit(p)) bit[p]+=x;}
int presum(int p){int res=0;for(p++;p;p-=lowbit(p)) res+=bit[p];return res;}
int sum(int l,int r){return presum(r)-presum(l-1);}

void gao(int num,int p1,int p2,int l1,int r1,int l2,int r2,int p=0)
{
    ans.clear();p=find(p);
    done+=num;print(num);putc(' ');
    ans.push_back(p1);ans.push_back(p2);
    for(int i=2;i<num;i++,p=find(p))
    {
        while(1)
        {
            if(p==n) p=find(0);
            else if(p>=l1&&p<=r1) p=find(r1);
            else if(p>=l2&&p<=r2) p=find(r2);
            else break;
        }
        ans.push_back(p);
        fa[p]=find(p+1);
        add(p,-1);
    }
    sort(ans.begin(),ans.end());
    for(int x : ans) print(x),putc(' ');putc('\n');
}

void solve()
{
    for(int i=1;i<=m-2;i++)
    {
        int p1=bp[2*i-1],p2=bp[2*i];
        if(sum(p1,p2)>=k-2) gao(max(k,2),p1,p2,0,p1,p2,n);
        else gao(max(k,2),p1,p2,p1,p2,p1,p2);
    }
    int p1=bp[2*m-3],p2=bp[2*m-2],p3=bp[2*m-1],p4=bp[2*m];
    int s1=sum(0,p1),s2=sum(p1,p2),s3=sum(p2,p3),s4=sum(p3,p4),s5=sum(p4,n-1);
    if(s2+s4<=s1+s3+s5)
    {
        int len=s4+2;len=max(k*((len-1)/k+1),2);
        gao(len,p1,p2,p1,p2,p1,p2,p3);
        gao(n-done,p3,p4,p3,p4,p3,p4,p1);
    }
    else
    {
        int len=s1+s5+2;len=max(k*((len-1)/k+1),2);
        gao(len,p2,p3,p2,p3,p2,p3,p4);
        gao(n-done,p1,p4,0,p1,p4,n,p2);
    }
}

int main()
{
    for(scanf("%d",&ToT);ToT;ToT--)
    {
        scanf("%d%d%d%s",&n,&m,&k,s);
        bcnt=0;reset(n);
        for(int i=0;i<n;i++)
        {
            if(s[i]=='B') bp[++bcnt]=i;
            else add(i,1);
        }
        if(n%k!=0||bcnt<2*m||n<(LL)m*max(k,2)){prints("No");continue;}
        if(m==1)
        {
            bool flag=(s[0]=='B'&&s[n-1]=='B');
            for(int i=0;i<n-1;i++) flag|=(s[i]=='B'&&s[i+1]=='B');
            if(!flag){prints("No");continue;}
            prints("Yes");print(n);putc(' ');
            for(int i=0;i<n;i++) print(i),putc(' ');putc('\n');
        }
        else
        {
            for(int i=0;i<=n;i++) fa[i]=i;
            for(int i=1;i<=m*2;i++) fa[bp[i]]=bp[i]+1;
            for(int i=m*2+1;i<=bcnt;i++) add(bp[i],1);
            done=0;prints("Yes");solve();
        }
    }
    return flush(),0;
}