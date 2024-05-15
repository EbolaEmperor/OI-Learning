#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
struct V{int p,h,v;};
const int ha=1e9+7,N=1010;
int n,a[N][N],h[N][N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<ha)?(x-y+ha):(x-y);}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",a[i]+j);
    int all=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            all=(all+1ll*(n-i+1)*(n-j+1))%ha;
    int ans1=0,ans2=0;
    for(int k=0;k<32;k++)
    {
        memset(h,0,sizeof(h));
        for(int i=0;i<=n;i++) a[i][0]=a[0][i]=0;
        for(int j=1;j<=n;j++)
            for(int i=1;i<=n;i++)
                if(a[i][j]>>k&1) h[i][j]=(a[i-1][j]>>k&1)?h[i-1][j]+1:1;
        int cnt1=0;
        for(int i=1;i<=n;i++)
        {
            static V s[N];
            int cur=0,top=1;s[1].p=0;
            for(int j=1;j<=n;j++)
                if(a[i][j]>>k&1)
                {
                    while(top>1&&s[top].h>=h[i][j]) cur=mns(cur,s[top--].v);
                    top++;s[top]={j,h[i][j],1ll*(j-s[top-1].p)*h[i][j]%ha};
                    cur=add(cur,s[top].v);
                    cnt1=add(cnt1,cur);
                }
                else cur=0,s[top=1].p=j;
        }
        ans1=(ans1+(1ll<<k)*cnt1)%ha;
        
        memset(h,0,sizeof(h));
        for(int i=0;i<=n;i++) a[i][0]=a[0][i]=1<<k;
        for(int j=1;j<=n;j++)
            for(int i=1;i<=n;i++)
                if(!(a[i][j]>>k&1)) h[i][j]=(!(a[i-1][j]>>k&1))?h[i-1][j]+1:1;
        int cnt2=0;
        for(int i=1;i<=n;i++)
        {
            static V s[N];
            int cur=0,top=1;s[1].p=0;
            for(int j=1;j<=n;j++)
                if(!(a[i][j]>>k&1))
                {
                    while(top>1&&s[top].h>=h[i][j]) cur=mns(cur,s[top--].v);
                    top++;s[top]={j,h[i][j],1ll*(j-s[top-1].p)*h[i][j]%ha};
                    cur=add(cur,s[top].v);
                    cnt2=add(cnt2,cur);
                }
                else cur=0,s[top=1].p=j;
        }
        ans2=(ans2+(1ll<<k)*(all-cnt2+ha))%ha;
    }
    printf("%d %d\n",ans1,ans2);
    return 0;
}
