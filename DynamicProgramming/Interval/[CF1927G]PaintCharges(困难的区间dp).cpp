#include <bits/stdc++.h>
using namespace std;

const int inf = 0x7f7f7f7f;
const int N = 105;
int a[N], n, t;
int f[N][N][N];
// f[i][j][k]: The minimum operation times when
//             only using first i filters,
//             the left-most uncolored position is j,
//             the right-most colored position is k. 

inline void ckmin(int &x, const int &y){
    x = (y < x) ? y : x;
}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", a+i);
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n + 1; ++j)
                for(int k = 0; k <= n + 1; ++k)
                    f[i][j][k] = inf;
        f[0][1][0] = 0;
        for(int i = 1; i <= n; ++i){
            // Donot use the i-th filter.
            for(int j = 0; j <= n + 1; ++j)
                for(int k = 0; k <= n + 1; ++k)
                    f[i][j][k] = f[i-1][j][k];
            // Use the i-th filter as a left-filter.
            int L = max(i - a[i] + 1, 1);
            for(int j = 0; j <= n + 1; ++j)
                for(int k = 0; k <= n + 1; ++k)
                    // Here, you should note that if k>i is colored, then [i,k] are all colored.
                    // So after using the i-th filter as a left-filter, 
                    //    if the left-filter covers j, 
                    //    then the right-most uncolored position is max(i+1,k+1).
                    ckmin(f[i][j < L ? j : max(i + 1, k + 1)][max(i, k)], f[i-1][j][k] + 1);
            // Use the i-th filter as a right-filter.
            int R = min(i + a[i] - 1, n);
            for(int j = 0; j <= n + 1; ++j)
                for(int k = 0; k <= n + 1; ++k)
                    ckmin(f[i][j < i ? j : max(j, R + 1)][max(R, k)], f[i-1][j][k] + 1);
        }
        printf("%d\n", f[n][n+1][n]);
    }
    return 0;
}