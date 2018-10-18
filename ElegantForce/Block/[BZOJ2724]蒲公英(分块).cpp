#include<bits/stdc++.h>
using namespace std;

const int N=40010,B=50,T=810;
int n,m,a[N],mode[T][T];
int Hash[N],hs,cnt[N];
vector<int> pos[N];

void prework(int x)
{
    int bo=x/B,val,mx=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=x;i<=n;i++)
    {
        cnt[a[i]]++;
        if(cnt[a[i]]>mx||cnt[a[i]]==mx&&a[i]<val)
            val=a[i],mx=cnt[a[i]];
        mode[bo][i/B]=val;
    }
}

int getcnt(int x,int l,int r)
{
    auto rp=upper_bound(pos[x].begin(),pos[x].end(),r);
    auto lp=lower_bound(pos[x].begin(),pos[x].end(),l);
    return rp-lp;
}

int query(int l,int r)
{
    int ans=mode[l/B+1][r/B-1];
    int mx=getcnt(ans,l,r);
    for(int i=l;i<=min(r,(l/B+1)*B-1);i++)
    {
        int cnt=getcnt(a[i],l,r);
        if(cnt>mx||cnt==mx&&a[i]<ans)
            ans=a[i],mx=cnt;
    }
    if(l/B==r/B) return Hash[ans];
    for(int i=r/B*B;i<=r;i++)
    {
        int cnt=getcnt(a[i],l,r);
        if(cnt>mx||cnt==mx&&a[i]<ans)
            ans=a[i],mx=cnt;
    }
    return Hash[ans];
}

int main()
{
    int l,r,ans=0;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",a+i),Hash[i]=a[i];
    sort(Hash,Hash+n);
    hs=unique(Hash,Hash+n)-Hash;
    for(int i=0;i<n;i++)
    {
        a[i]=lower_bound(Hash,Hash+hs,a[i])-Hash;
        pos[a[i]].push_back(i);
    }
    for(int i=0;i<n;i+=B) prework(i);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&l,&r);
        l=(l+ans-1)%n;r=(r+ans-1)%n;
        if(l>r) swap(l,r);
        ans=query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}