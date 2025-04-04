#include <bits/stdc++.h>
using namespace std;

const int B = 1e5;
// cnt[x] 用于统计 %k=x 的有几个
unordered_map<long long, int> cnt;
long long m, k;
int digitsum[B + 5];

int main(){
    cin >> k >> m;
    for(int i = 0; i < B; i++){
        digitsum[i] = digitsum[i / 10] + i % 10;
        cnt[((digitsum[i] - i) % k + k) % k]++;
    }
    digitsum[B] = 1;
    long long ans = 0;
    for(int a = 0; a < m / B; a++){
        long long t = 1ll * a * B - digitsum[a];
        ans += cnt[((t % k) + k) % k];
    }
    long long a = m / B;
    for(int b = 0; b <= m % B; b++){
        if((1ll * a * B + b) % k == (digitsum[a] + digitsum[b]) % k)
            ans++;
    }
    cout << ans - 1 << endl;
    return 0;
}