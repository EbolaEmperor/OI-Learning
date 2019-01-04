#include<bits/stdc++.h>
using namespace std;

const int N=2010,M=1000010;
struct Card{int a,b,c;} card[N];
int f[2][N<<2][2][2];
int A,B,n,mxa=0,cnt[N<<1];
int ans1=0,ans2=0;
bool can[M];

inline void upmax(int &x,const int &y){if(y>x) x=y;}

int gao1()
{
    memset(f[0],-0x3f,sizeof(f[0]));
    int sum=0;f[0][0][0][0]=0;
    for(int i=1,now=1;i<=n;i++,now^=1)
    {
        memset(f[now],-0x3f,sizeof(f[now]));
        int m=card[i].a<<1,b=card[i].b,c=card[i].c;
        int lim=min(b,b%m+m);
        cnt[m]+=(b-lim)/m;
        ans2+=(b-lim)/m*c;
        for(int j=0;j<=sum;j++)
            for(int k1=0;k1<2;k1++)
                for(int k2=0;k2<2;k2++)
                {
                    if(f[now^1][j][k1][k2]<0) continue;
                    for(int k=0;k<=lim;k++)
                    {
                        int s1=k1,s2=k2,res=f[now^1][j][k1][k2];
                        if(k+1==m||k+1==2*m) s1^=1,res+=k1?0:c;
                        if(lim-k+1==m||lim-k+1==2*m) s2^=1,res+=k2?c:0;
                        res+=c*(k>=m)+c*(lim-k>=m);
                        upmax(f[now][j+k][s1][s2],res);
                    }
                }
        sum+=lim;
    }
    return sum;
}

void gao2()
{
    static bool done[M];can[0]=1;
    for(int i=0;i<=mxa;i++)
    {
        if(!cnt[i]) continue;
        memset(done,0,sizeof(done));
        for(int j=B;j>=0;j--)
        {
            if(!can[j]) continue;
            for(int k=0;k<=cnt[i];k++)
            {
                if(j+k*i>B) break;
                if(done[j+k*i]) continue;
                done[j+k*i]=can[j+k*i]=1;
            }
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&card[i].a,&card[i].b,&card[i].c);
        A+=card[i].a;B+=card[i].b;
        upmax(mxa,card[i].a<<1);
    }
    sort(card+1,card+1+n,[](Card a,Card b){return a.c>b.c;});
    int sum=gao1();gao2();
    for(int i=0;i<=min(sum,B/2);i++)
    {
        if(!can[B/2-i]) continue;
        for(int k1=0;k1<2;k1++)
            for(int k2=0;k2<2;k2++)
                upmax(ans1,f[n&1][i][k1][k2]);
    }
    printf("%d\n",ans1+ans2);
    return 0;
}