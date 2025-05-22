#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
using ll = long long;

ll qp(ll a, ll e = MOD - 2) {
    ll r = 1;
    for(; e; e >>= 1, a = a * a % MOD)
        if (e & 1) r = r * a % MOD;
    return r;
}

struct Comb {
    vector<ll> fac, ifac;
    Comb(int n = 0) { init(n); }
    void init(int n) {
        fac.resize(n + 1);
        ifac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
        ifac[n] = qp(fac[n]);
        for (int i = n; i; --i) ifac[i - 1] = ifac[i] * i % MOD;
    }
    ll C(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    vector<pair<int,string>> cases;
    vector<int> ks;
    int maxn = 0;
    while (T--) {
        int n, k; string s;
        cin >> n >> k >> s;
        cases.emplace_back(k, s);
        ks.push_back(k);
        maxn = max(maxn, n);
    }
    Comb cb(maxn);
    for (size_t idx = 0; idx < cases.size(); ++idx) {
        int k = cases[idx].first;
        const string &s = cases[idx].second;
        int n = (int)s.size();

        int tot1 = count(s.begin(), s.end(), '1');
        if (tot1 < k) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> pos(n + 1, 1);
        vector<int> ones;
        ones.push_back(0);
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == '1') ones.push_back(i);
            if (ones.size() > k)
                pos[i] = ones[ones.size() - k - 1] + 1;
        }

        ll ans = 1;
        for (int i = 1, v = 0; i <= n; ++i){
            if(s[i - 1] == '1' && v < k) ++v;
            ans = (ans + cb.C(i - pos[i], v - (s[i - 1] == '0'))) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}