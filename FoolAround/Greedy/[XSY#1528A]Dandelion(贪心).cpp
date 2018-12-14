#include<bits/stdc++.h>
using namespace std;

const int N=1010;
struct Dan{int s,p,t;} dan[N];
int choice[N],pre[N];
int n,T,magic[N];
bool used[N][N];

int main()
{
    scanf("%d%d%d",&n,&T,magic);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&dan[i].s,&dan[i].p,&dan[i].t);
    int ans=magic[0],ansd=0;
    for(int i=0;i<=T;i++)
    {
        if(magic[i]>ans) ans=magic[i],ansd=i;
        memcpy(used[i],used[pre[i]],sizeof(used[i]));
        if(i>0) used[i][choice[i]]=1;
        for(int j=1;j<=n;j++)
        {
            if(used[i][j]||dan[j].s>magic[i]) continue;
            int x=i+dan[j].t,y=magic[i]+dan[j].p;
            if(x>T) continue;
            if(y>magic[x]) magic[x]=y,pre[x]=i,choice[x]=j;
        }
    }
    printf("%d\n",ans);
    stack<int> stk;
    for(int u=ansd;u;u=pre[u])
        stk.push(choice[u]);
    while(!stk.empty())
        printf("%d ",stk.top()),stk.pop();
    return 0;
}