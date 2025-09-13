
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300005;

struct Item {
    ll len, s_time, f_time;
    bool operator<(const Item& other) const {
        return s_time < other.s_time;
    }
};

int n, q;
Item items[N];
ll suf_max_f[N]; // 后缀最大 f_time
ll suf_sum_len[N]; // 后缀长度和
map<ll, ll> result_map;
bitset<N> dp;

// result_map[len]: 晾衣杆长度 len 时的最小时间
void update_result(ll timee, ll len) {
    if (!result_map.count(len)) result_map[len] = timee;
    else result_map[len] = min(result_map[len], timee);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> items[i].len >> items[i].f_time >> items[i].s_time;
    }

    // 按 s_time 排序
    sort(items + 1, items + n + 1);

    for (int i = n; i >= 1; --i) {
        suf_max_f[i] = max(suf_max_f[i + 1], items[i].f_time);
        suf_sum_len[i] = suf_sum_len[i + 1] + items[i].len;
    }

    update_result(suf_max_f[1], suf_sum_len[1]);
    dp.set(0);
    ll total_len = 0;

    for (int i = 1; i <= n; ++i) {
        total_len += items[i].len;
        dp |= (dp << items[i].len);
        ll st = (total_len + 1) / 2;
        while (!dp.test(st)) ++st;
        update_result(max(suf_max_f[i + 1], items[i].s_time), 
                      st + suf_sum_len[i + 1]);
    }

    for (int i = 0; i < q; ++i) {
        ll x;
        cin >> x;
        auto it = result_map.upper_bound(x);
        cout << ((it == result_map.begin()) ? -1 : (--it)->second) << '\n';
    }
    return 0;
}