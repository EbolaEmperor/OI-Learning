#include<bits/stdc++.h>
using namespace std;

const int N=100010,D=10010;
int a[N],n;
vector<int> pos[D];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        pos[a[i]].push_back(i);
    }
    int cnt=1,pre=0;
    long long ans=0ll;
    for(int i=0;i<=10000;i++)
    {
        if(pos[i].empty()) continue;
        ans+=1ll*cnt*(i-pre);
        for(int j=0;j<pos[i].size();j++)
        {
            int p=pos[i][j];
            if(a[p-1]>a[p]) cnt++;
            if(j==0||p!=pos[i][j-1]+1) cnt--;
            if(a[p+1]>a[p]) cnt++;
        }
        pre=i;
    }
    cout<<ans<<endl;
    return 0;
}
