#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
int n, type, h[N], tag[N];
long long f[N], sum[N], minlast[N];

int main(){
    scanf("%d%d", &n, &type);
    for(int i = 1; i <= n; ++i)
        scanf("%d", h + i), sum[i] = sum[i-1] + h[i];
    memset(f, 0x3f, sizeof(f));
    memset(minlast, 0x3f, sizeof(minlast));
    f[0] = 0; minlast[0] = -0x3f3f3f3f;
    for(int i = 1; i <= n; ++i){
        int p = lower_bound(sum + 1, sum + 1 + n, minlast[i-1] + sum[i-1]) - sum;
        tag[p] = i - 1;
        tag[i] = max(tag[i], tag[i-1]);
        f[i] = f[tag[i]] + (sum[i] - sum[tag[i]]) * (sum[i] - sum[tag[i]]);
        minlast[i] = sum[i] - sum[tag[i]];
    }
    cout << f[n] << endl;
    return 0;
}
