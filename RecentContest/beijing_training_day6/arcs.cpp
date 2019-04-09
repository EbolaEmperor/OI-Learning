#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=1e9+7,N=100010;
vector<int> pos[N];
int n,col[N],sz;
int ans=0;

void gao1(int a)  //find the number of 'baba', which a in big and b in all
{
    static LL s1[N];  //s1[b]: The number of color b at the left of now
    static LL s2[N];  //s2[b]: The pair of 'ab' at the left of now
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    LL num=0;  // The number of color a at the left of now
    int tot=pos[a].size();
    for(int i=1;i<=n;i++)
        if(col[i]==a) num++;
        else
        {
            int tmp=(num*s1[col[i]]-s2[col[i]])%ha;  //The pair of 'ba' at the left of now
            ans=(ans+1ll*tmp*(tot-num))%ha;
            s1[col[i]]++;
            s2[col[i]]+=num;
        }
}

void gao2(int a)  //find the number of 'abab', which a in big and b in small
{
    static LL s1[N];  //s1[b]: The number of color b at the right of now
    static LL s2[N];  //s2[b]: The pair of 'ba' at the right of now
    memset(s1,0,sizeof(s1));
    memset(s2,0,sizeof(s2));
    LL num=0;  // The number of color a at the right of now
    int tot=pos[a].size();
    for(int i=n;i>=1;i--)
        if(col[i]==a) num++;
        else if(pos[col[i]].size()<=sz)
        {
            int tmp=(num*s1[col[i]]-s2[col[i]])%ha;  //The pair of 'ab' at the right of now
            ans=(ans+1ll*tmp*(tot-num))%ha;
            s1[col[i]]++;
            s2[col[i]]+=num;
        }
}

int bit[N];
inline int lowbit(const int &x){return x&-x;}
void add(int p){for(;p<=n;p+=lowbit(p)) bit[p]++;}
int sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=bit[p];return res;}

inline int C3(__int128 n){return n*(n-1)*(n-2)/6%ha;}
inline int C4(__int128 n){return n*(n-1)*(n-2)*(n-3)/24%ha;}

void gao3()  //find the number of 'baba', which a in small and b in small
{
    static vector<int> qry[N],upd[N];
    for(int i=1;i<=n;i++)
        if(pos[i].size()<=sz)
        {
            ans=(ans-C4(pos[i].size())+ha)%ha;
            ans=(ans-2ll*C3(pos[i].size())+ha)%ha;
            for(int j=0;j<pos[i].size();j++)
                for(int k=j+1;k<pos[i].size();k++)
                {
                    qry[pos[i][k]].push_back(pos[i][j]);
                    qry[pos[i][j]].push_back(-pos[i][j]);
                    upd[pos[i][k]].push_back(pos[i][j]);
                }
        }
    for(int i=1;i<=n;i++)
    {
        for(int p : qry[i])
            if(p>0) ans=(ans+sum(p))%ha;
            else ans=(ans-sum(-p)+ha)%ha;
        for(int p : upd[i]) add(p);
    }
}

int main()
{
    scanf("%d",&n);
    sz=sqrt(n/log2(n));
    for(int i=1;i<=n;i++)
        scanf("%d",col+i),pos[col[i]].push_back(i);
    for(int i=1;i<=n;i++)
        if(pos[i].size()>sz) gao1(i),gao2(i);
    gao3();
    printf("%d\n",ans);
    return 0;
}
