#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

const int N = 1e5 + 5, M = 55;
long long dis[N];
int n, q, m, v[M], c[M], maxid = -1;

void twoCircleUpdate(int vol, int cost) {
    int g = gcd(m, vol), step = vol % m, d0 = vol / m;
    for(int i = 0; i < g; i++)
        for(int cycle = 0; cycle < 2; cycle++)
            for(int j = i, p = -1; p != i; j = p) {
                p = j + step;
                long long d = p >= m ? d0 + 1 : d0;
                if(p >= m) p -= m;
                dis[p] = max(dis[p], dis[j] + cost - d * c[maxid]);
            }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &v[i], &c[i]);
        if(maxid == -1 || (long long) c[i] * v[maxid] > (long long) c[maxid]  * v[i])
            maxid = i;
    }
    m = v[maxid];
    dis[0] = 0;
    fill(dis + 1, dis + m, -1e18);
    for(int i = 1; i <= n; i++)
        if(i != maxid) twoCircleUpdate(v[i], c[i]);
    for(int i = 1; i <= q; i++) {
        long long V;
        scanf("%lld", &V);
        int p = V % m;
        if(dis[p] < -1e17) puts("-1");
        else printf("%lld\n", dis[p] + V / m * c[maxid]);
    }
    return 0;
}