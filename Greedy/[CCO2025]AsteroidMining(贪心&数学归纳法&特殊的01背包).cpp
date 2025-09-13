#include <bits/stdc++.h>
#define int long long
using namespace std;

// obj = [value, weight]
const int N = 500010;
pair<int,int> obj[N], tmp[N];
int n, m;

bool cmp(pair<int,int> a, pair<int,int> b) {
    return a.second < b.second || (a.second == b.second && a.first > b.first);
}

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> obj[i].first >> obj[i].second;
    }
    sort(obj + 1, obj + n + 1, cmp);

    int ans = 0;
    while(m) {
        int unit = obj[1].second, ones = 0, submin = -1;
        m /= unit;
        for (int i = 1; i <= n; i++) {
            obj[i].second /= unit;
            if (obj[i].second == 1) ones++;
            else if (submin == -1) submin = obj[i].second;
        }

        if (submin == -1) {
            for (int i = 1; i <= n && i <= m; i++) {
                ans += obj[i].first;
            }
            break;
        }

        int need = min(m % submin, ones);
        for (int i = 1; i <= n && i <= need; i++) {
            ans += obj[i].first;
        }
        m -= m % submin;

        int idx = 0;
        int cache = 0;
        for (int i = need+1; i <= n && obj[i].second == 1; i++) {
            if ((i - need) % submin == 0) {
                tmp[++idx] = {obj[i].first + cache, submin};
                cache = 0;
            } else {
                cache += obj[i].first;
            }
        }
        if (cache) tmp[++idx] = {cache, submin};

        for (int i = need+1; i <= n; i++)
            if (obj[i].second > 1) tmp[++idx] = obj[i];
        n = idx;
        for (int i = 1; i <= n; i++)
            obj[i] = tmp[i];
        sort(obj + 1, obj + n + 1, cmp);
    }

    cout << ans << endl;

    return 0;
}