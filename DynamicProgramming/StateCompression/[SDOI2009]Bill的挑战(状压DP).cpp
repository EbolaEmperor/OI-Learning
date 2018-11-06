#include<bits/stdc++.h>
using namespace std;

const int N=17,M=55;
const int ha=1000003;
int match[M][27],n,m,k;
int f[M][1<<N];
char s[N][M];

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int Main()
{
    memset(f,0,sizeof(f));
    memset(match,0,sizeof(match));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    m=strlen(s[1]+1);
    for(int j=1;j<=m;j++)
        for(int c=0;c<26;c++)
            for(int i=1;i<=n;i++)
                if(s[i][j]==c+'a'||s[i][j]=='?')
                    match[j][c]|=1<<i-1;
    f[0][(1<<n)-1]=1;
    for(int i=0;i<m;i++)
        for(int s=0;s<(1<<n);s++)
            for(int c=0;c<26;c++)
                add(f[i+1][s&match[i+1][c]],f[i][s]);
    int ans=0;
    for(int s=0;s<(1<<n);s++)
    {
        int cnt=0;
        for(int i=0;i<n;i++)
            if(s&(1<<i)) cnt++;
        if(cnt==k) add(ans,f[m][s]);
    }
    return ans;
}

int main()
{
    int T;scanf("%d",&T);
    while(T--) printf("%d\n",Main());
    return 0;
}