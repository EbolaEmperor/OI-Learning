#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

const int N = 5e5 + 5;
long long dis[N];
int n, m, a[N];
long long l, r;

void twoCircleUpdate(int x) {
    int g = gcd(m, x), step = x % m;
    for(int i = 0; i < g; i++)
        for(int c = 0; c < 2; c++)
            for(int j = i, p = -1; p != i; j = p) {
                p = (j + step) >= m ? j + step - m : j + step;
                dis[p] = min(dis[p], dis[j] + x);
            }
}

long long getans(long long r) {
    long long ans = 0;
    for(int i = 0; i < m; i++) {
        if(dis[i] <= r) {
            ans += (r - dis[i]) / m + 1;
        }
    }
    return ans;
}

int main() {
    cin >> n >> l >> r;
    m = INT_MAX;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] != 0)
            m = min(m, a[i]);
    }
    dis[0] = 0;
    fill(dis + 1, dis + m, LLONG_MAX / 2);
    for(int i = 1; i <= n; i++)
        if(a[i] != m && a[i] != 0)
            twoCircleUpdate(a[i]);
    cout << getans(r) - getans(l - 1) << endl;
    return 0;
}