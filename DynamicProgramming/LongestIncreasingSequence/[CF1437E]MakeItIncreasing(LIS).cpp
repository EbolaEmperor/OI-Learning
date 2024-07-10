#include <bits/stdc++.h>
using namespace std;

int LIS(const vector<int> &a)
{
    int ans = 0;
    int *g = new int[a.size()];
    memset(g, 0x7f, sizeof(int) * a.size());
    for(int i = 0; i < a.size(); i++)
    {
        int p = upper_bound(g, g + ans, a[i]) - g;
        ans = max(ans, p + 1);
        g[p] = a[i];
    }
    delete[] g;
    return ans;
}

const int N = 500000;
int a[N+5], b[N+5];
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    a[0] = -2e9; a[n+1] = 2e9;
    for(int i = 1; i <= m; ++i)
        scanf("%d", b + i);
    for(int i = 1; i <= m - 1; ++i){
        if(a[b[i+1]] < a[b[i]] + b[i+1] - b[i]){
            puts("-1");
            return 0;
        }
    }
    for(int i = 1; i <= n; ++i) a[i] -= i;
    b[0] = 0; b[m+1] = n + 1;
    int ans = 0;
    for(int i = 0; i <= m; ++i){
        if(b[i+1] <= b[i] + 1) continue;
        vector<int> h;
        int l = b[i], r = b[i+1];
        for(int j = l + 1; j < r; ++j)
            if(a[j] >= a[l] && a[j] <= a[r])
                h.push_back(a[j]);
        ans += (r - l - 1) - LIS(h);
    }
    cout << ans << endl;
    return 0;
}