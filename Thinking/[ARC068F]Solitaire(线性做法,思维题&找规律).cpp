#include <bits/stdc++.h>
using namespace std;
#define ha 1000000007

int Pow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = 1ll * a * a % ha)
        if (b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int main(){
    int n, k;
    cin >> n >> k;
    if(k == 1){
        cout << Pow(2, max(n - 2, 0)) << endl;
        return 0;
    }
    if(k == n) k--;
    n = n - k + 1;
    int ans = n;
    for(int j = k; j < 2 * k - 2; j++)
        ans = 1ll * ans * (n + j) % ha;
    int fac = 1;
    for(int j = 2; j < k; j++)
        fac = 1ll * fac * j % ha;
    fac = Pow(fac, ha - 2);
    ans = 1ll * ans * fac % ha;
    ans = 1ll * ans * Pow(2, n - 2) % ha;
    cout << ans << endl;
    return 0;
}