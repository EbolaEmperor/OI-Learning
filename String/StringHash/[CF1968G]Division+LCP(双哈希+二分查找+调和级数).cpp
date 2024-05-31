#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
const ull base = 233;
const ll base2 = 311;
const ll mod = 1e9+7;
const int N = 200010;
char s[N];
int n;
ull hashsum[N], pw[N];
ll hashsum2[N], pw2[N];
 
ull gethash(int l, int r){
    return hashsum[r] - hashsum[l-1] * pw[r-l+1];
}
 
ll gethash2(int l, int r){
    return (hashsum2[r] - hashsum2[l-1] * pw2[r-l+1] % mod + mod) % mod;
}
 
bool equal(int l1, int r1, int l2, int r2){
    return gethash(l1,r1) == gethash(l2,r2) && gethash2(l1,r1) == gethash2(l2,r2);
}
 
int f[N];
// f[i] = LCP(S[1,i-1], S[i,n])
int getf(int i){
    int len = min(i - 1, n - i + 1);
    int l = 1, r = len, mid, ans = 0;
    while(l <= r){
        mid = (l + r) / 2;
        if(equal(1,mid,i,i+mid-1))
            l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans;
}
 
vector<int> pos[N];
// pos[x] = { i : f[i]==x }
int mx[N];
// mx[k]: The maximum i such that 
//          exists k disjoint substrings that equal to S[1,i]
// Note that mx[k] >= mx[k+1]
 
int main(){
    int t, ql, qr;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d%s", &n, &ql, &qr, s + 1);
        pw[0] = pw2[0] = 1;
        for(int i = 1; i <= n; ++i){
            pw[i] = pw[i-1] * base;
            pw2[i] = pw2[i-1] * base2 % mod;
        }
        for(int i = 1; i <= n; ++i){
            hashsum[i] = hashsum[i-1] * base + s[i];
            hashsum2[i] = (hashsum2[i-1] * base2 + s[i]) % mod;
        }
        set<int> S;
        for(int i = 1; i <= n; ++i){
            f[i] = getf(i);
            if(f[i]){
                pos[f[i]].push_back(i);
                S.insert(i);
            }
        }
        // For each i, find the maximum k such that 
        //   exists k disjoint substrings that equal to S[1,i], write as k[i].
        // Note that k[i] is decreasing and mx[k[i+1]+1 ... k[i]] = i
        for(int i = 1; i <= n; ++i){
            int now = i + 1, k = 1;
            while(true){
                auto it = S.lower_bound(now);
                if(it == S.end()) break;
                now = *it + i, ++k;
            }
            mx[k] = i;
            for(int j : pos[i]) S.erase(j);
        }
        for(int i = n-1; i >= 1; --i) mx[i] = max(mx[i], mx[i+1]);
        for(int i = ql; i <= qr; ++i) printf("%d ", mx[i]); puts("");
        for(int i = 1; i <= n; ++i) pos[i].clear(), mx[i] = 0;
    }
    return 0;
}