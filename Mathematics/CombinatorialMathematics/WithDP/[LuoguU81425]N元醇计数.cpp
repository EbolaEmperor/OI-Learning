// Number of n-carbon alkyl radicals.
#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int inv6 = 166374059;
const int N = 1010;
long long f[N], n;

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int main(){
    cin >> n;
    f[0] = f[1] = 1;
    for(int m = 2; m <= n; m++){
        // A < B < C
        for(int i = 0; i < m; i++)
            for(int j = i + 1; j < m; j++){
                if(j >= m - 1 - i - j) break;
                f[m] = (f[m] + f[i] * f[j] % ha * f[m - 1 - i - j]) % ha;
            }
        // A = B != C
        for(int i = 0; 2 * i < m; i++){
            if(i == m - 1 - 2 * i) continue;
            f[m] = (f[m] + f[i] * (f[i] + 1) / 2 % ha * f[m - 1 - 2 * i]) % ha;
        }
        // A = B = C
        if(m % 3 == 1){
            int k = (m - 1) / 3;
            f[m] = (f[m] + f[k] * (f[k] - 1) % ha * (f[k] - 2) % ha * inv6 % ha
                         + f[k] * f[k] % ha ) % ha;
        }
    }
    cout << f[n] << endl;
    return 0;
}