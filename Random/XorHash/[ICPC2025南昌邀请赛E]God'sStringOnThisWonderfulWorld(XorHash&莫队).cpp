// 常数太大，过不去
#include <bits/stdc++.h>
#include <random>
using namespace std;

using ll = long long;
const int B = 550;
const int M = 26;
random_device rd;
mt19937_64 gen(rd());
vector<ll> sum;
ll curans = 0;
unordered_map<ll, int> cur;

struct Query {
    int l, r, id;
    bool operator < (const Query &other) const {
        if (l / B != other.l / B) return l < other.l;
        if (l / B % 2 == 0) return r < other.r;
        return r > other.r;
    }
};

void add(int i) {curans += cur[sum[i]]; cur[sum[i]]++;}
void del(int i) {cur[sum[i]]--; curans -= cur[sum[i]];}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k, q;
    string s;
    cin >> n >> k >> q >> s;

    vector<ll> randval[M];
    for (int i = 0; i < M; i++) {
        ll sum = 0;
        randval[i].resize(k);
        for (int j = 0; j < k - 1; j++) {
            randval[i][j] = uniform_int_distribution<ll>(0, LLONG_MAX)(gen);
            sum ^= randval[i][j];
        }
        randval[i][k - 1] = sum;
    }

    static int cnt[M] = {0};
    sum.resize(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] ^ randval[s[i] - 'a'][cnt[s[i] - 'a']];
        (cnt[s[i] - 'a'] += 1) %= k;
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end());

    vector<ll> ans(q);
    int l = 0, r = -1;
    for (int i = 0; i < q; i++) {
        while (l > queries[i].l) add(--l);
        while (r < queries[i].r) add(++r);
        while (l < queries[i].l) del(l++);
        while (r > queries[i].r) del(r--);
        ans[queries[i].id] = curans;
    }

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}