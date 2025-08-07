#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int minv[N<<2];
int n, a[N], pre[N];
bool can[N];

void update(int o, int l, int r, int k, int v) {
    if (l == r) {
        minv[o] = v;
        return;
    }
    int mid = (l + r) / 2;
    if(k <= mid) update(o<<1, l, mid, k, v);
    else update(o<<1|1, mid+1, r, k, v);
    minv[o] = min(minv[o<<1], minv[o<<1|1]);
}

int qmin(int o, int l, int r, int nl, int nr) {
    if (l >= nl && r <= nr) return minv[o];
    int mid = (l + r) / 2, ans = n+3;
    if(nl <= mid) ans = min(ans, qmin(o<<1, l, mid, nl, nr));
    if(nr > mid) ans = min(ans, qmin(o<<1|1, mid+1, r, nl, nr));
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        pre[i] = 0;
        can[1] |= (a[i] != 1);
    }
    if (!can[1])
        return puts("1"), 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > 1 && !can[a[i]])
            can[a[i]] = (qmin(1, 1, n, 1, a[i]-1) > pre[a[i]]);
        update(1, 1, n, a[i], i);
        pre[a[i]] = i;
    }
    for(int i = 2; i <= n+1; i++)
        if (!can[i] && qmin(1, 1, n, 1, i-1) <= pre[i])
            return printf("%d\n", i), 0;
    printf("%d\n", n+2);
    return 0;
}