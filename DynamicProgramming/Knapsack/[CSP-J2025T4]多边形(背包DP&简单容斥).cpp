#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 5010;
int f[N], a[N], n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    int ans = 0, full = 1;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        full = 2 * full % ha;
        for (int j = 0; j <= a[i]; j++)
            ans = (ans + f[j]) % ha;
        for (int j = 5000; j >= a[i]; j--)
            f[j] = (f[j] + f[j - a[i]]) % ha;
    }
    ans = (full - 1 - ans + ha) % ha;
    printf("%d\n", ans);
    return 0;
}