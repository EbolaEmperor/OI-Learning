#include<bits/stdc++.h>
using namespace std;

const int N=1010;
bool col[N][N];
int cntc[N],cntr[N];
char ss[N];
int n;

int main()
{
    scanf("%d",&n);
    bool nosol=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss+1);
        for(int j=1;j<=n;j++)
        {
            col[i][j]=(ss[j]=='#');
            cntc[j]+=col[i][j];
            cntr[i]+=!col[i][j];
            if(col[i][j]) nosol=0;
        }
    }
    if(nosol) return puts("-1"),0;
    int ans=INT_MAX,nofull=0;
    for(int i=1;i<=n;i++) nofull+=(cntc[i]<n);
    for(int i=1;i<=n;i++) ans=min(ans,(!cntc[i])+cntr[i]+nofull);
    printf("%d\n",ans);
    return 0;
}