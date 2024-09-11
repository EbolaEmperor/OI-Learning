#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 5010;
int n, a[N], pre[N], f[N][N], sum[N][N];

inline void add(int &x, const int &y){
    x = (x + y >= ha) ? (x + y - ha) : (x + y);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; i++){
        pre[i] = pre[i - 1];
        while(a[pre[i] + 1] * 2 <= a[i]) pre[i]++;
        f[1][i] = 1;
        sum[1][i] = i;
    }
    for(int x = 2; x <= n; x++)
        for(int i = 1; i <= n; i++){
            add(f[x][i], sum[x-1][pre[i]]);
            if(pre[i] - x + 2 > 0)
                add(f[x][i], (long long) (pre[i] - x + 2) * f[x-1][i] % ha);
            sum[x][i] = sum[x][i - 1];
            add(sum[x][i], f[x][i]);
        }
    cout << f[n][n] << endl;
    return 0;
}