#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=300010;
map<LL,int> cnt;
vector<int> col[N];
LL val[N];int qwq,n;

LL Rand(){return (LL)rand()<<30|rand();}

void _main_()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        scanf("%d",&x),col[x].push_back(i);
    for(int i=1;i<=n;i++)
        if(!col[i].empty())
        {
            LL sum=0;
            for(int j=0;j<col[i].size()-1;j++)
                sum^=(val[col[i][j]]=Rand());
            val[col[i].back()]=sum;
        }
    LL sum=0,ans=0;cnt[0]=1;
    for(int i=1;i<=n;i++)
    {
        sum^=val[i];
        ans+=cnt[sum];
        cnt[sum]++;
    }
    cout<<ans<<"\n";
    for(int i=1;i<=n;i++)
        col[i].clear(),val[i]=0;
    cnt.clear();
}

int main()
{
    srand(time(0));
    scanf("%d",&qwq);
    while(qwq--) _main_();
    return 0;
}