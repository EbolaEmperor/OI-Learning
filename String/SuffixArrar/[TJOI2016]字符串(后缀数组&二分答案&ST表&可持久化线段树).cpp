#include<bits/stdc++.h>
using namespace std;

const int N=200010;
char s[N];

namespace SA {
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
}

namespace RMQ {
    int st[N][20], lo2[N];
    void init(int n) {
        for (int i = 2; i <= n; i++) lo2[i] = lo2[i >> 1] + 1;
        for (int i = 1; i <= n; i++) st[i][0] = SA::height[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) {
        int j = lo2[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
}

namespace SGT {
    int tot = 1;
    int ls[N * 25], rs[N * 25], val[N * 25], rt[N];

    void insert(int &x, int pre, int l, int r, int pos, int v) {
        x = ++tot;
        ls[x] = ls[pre];
        rs[x] = rs[pre];
        val[x] = val[pre] + v;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos <= mid) {
            insert(ls[x], ls[pre], l, mid, pos, v);
        } else {
            insert(rs[x], rs[pre], mid + 1, r, pos, v);
        }
    }

    int query(int x, int pre, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return val[x] - val[pre];
        int mid = (l + r) / 2;
        return query(ls[x], ls[pre], l, mid, ql, qr) 
             + query(rs[x], rs[pre], mid + 1, r, ql, qr);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    scanf("%s", s+1);
    SA::getSA(n, 131);
    SA::getHeight(n);
    RMQ::init(n);
    SGT::rt[0] = 1;
    for(int i = 1; i <= n; i++) {
        SGT::insert(SGT::rt[i], SGT::rt[i - 1], 1, n, SA::sa[i], 1);
    }
    while(m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        auto check = [&](int k) {
            int x = SA::rk[c];
            for(int i = 20; i >= 0; i--) {
                if (x - (1 << i) >= 2 && RMQ::query(x - (1 << i), SA::rk[c]) >= k) {
                    x -= (1 << i);
                }
            }
            if(SA::height[x] >= k) x--;

            int y = SA::rk[c] + 1;
            for(int i = 20; i >= 0; i--) {
                if (y + (1 << i) <= n && RMQ::query(SA::rk[c] + 1, y + (1 << i)) >= k) {
                    y += (1 << i);
                }
            }
            if(SA::height[y] < k) y--;

            return SGT::query(SGT::rt[y], SGT::rt[x - 1], 1, n, a, b - k + 1) >= 1;
        };

        int l = 0, r = min(b - a + 1, d - c + 1), mid;
        while(l < r) {
            mid = (l + r + 1) / 2;
            if(check(mid)) l = mid;
            else r = mid - 1;
        }
        cout << l << "\n";
    }
    return 0;
}
