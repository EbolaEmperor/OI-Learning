// 原题是 O(n^2) 的，这份代码是加强版 O(n log n) 的
// 加强版来源：楼教主男人八题，2009 国家集训队论文题
#include<bits/stdc++.h>
using namespace std;

const int N = 200010;
int s[N];
int sa[N],rk[N],c[N];
int x[N],y[N],tmp[N];
int height[N];

void getSA(int n,int m)
{
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<m;i++) c[i+1]+=c[i];
    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
        for(int i=1;i<=n;i++) c[tmp[i]]++;
        for(int i=1;i<m;i++) c[i+1]+=c[i];
        for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
        num=1;swap(x,y);x[sa[1]]=1;
        for(int i=2;i<=n;i++)
            x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
        if(num==n) break;
        m=num;
    }
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
}

void getHeight(int n)
{
    int k=0;
    for(int i=1;i<=n;i++)
    {
        if(rk[i]==1) continue;   //height[1]=0
        if(k) k--;   //h[i]>=h[i-1]-1
        int j=sa[rk[i]-1];
        while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;   //h[i]=height[rk[i]]
    }
}

bool check(int n, int k) {
    int min_sa = sa[1], max_sa = sa[1];
    for(int i = 2; i <= n; i++) {
        if(height[i] < k) {
            if(max_sa - min_sa > k) return true;
            min_sa = max_sa = sa[i];
        } else {
            min_sa = min(min_sa, sa[i]);
            max_sa = max(max_sa, sa[i]);
        }
    }
    return max_sa - min_sa > k;
}

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = 1; i <= n; i++) s[i] = s[i + 1] - s[i];
    --n;
    for(int i = 1; i <= n; i++) s[i] += 90;
    getSA(n, 180);
    getHeight(n);

    if(!check(n, 4)) {
        cout << 0 << endl;
        return 0;
    }

    int l = 4, r = n / 2, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if (check(n, mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << r + 1 << endl;
    return 0;
}
