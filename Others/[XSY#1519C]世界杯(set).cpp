#include<bits/stdc++.h>
using namespace std;

int n,k;
struct Type
{
    int mn[5],mx[5],sz;
    bool operator < (const Type &a) const{for(int i=0;i<k;i++)if(mn[i]<a.mx[i])return 1;return 0;}
    bool operator > (const Type &a) const{for(int i=0;i<k;i++)if(mx[i]>a.mn[i])return 1;return 0;}
};
set<Type> S;

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        Type x;x.sz=1;
        for(int j=0;j<k;j++)
        {
            scanf("%d",&x.mn[j]);
            x.mx[j]=x.mn[j];
        }
        for(auto it=S.lower_bound(x);it!=S.begin();it=S.lower_bound(x))
            if(*--it>x)
            {
                for(int j=0;j<k;j++)
                {
                    x.mn[j]=min(x.mn[j],it->mn[j]);
                    x.mx[j]=max(x.mx[j],it->mx[j]);
                }
                x.sz+=it->sz;
                S.erase(it);
            }
            else break;
        S.insert(x);
        printf("%d ",(--S.end())->sz);
    }
    return 0;
}