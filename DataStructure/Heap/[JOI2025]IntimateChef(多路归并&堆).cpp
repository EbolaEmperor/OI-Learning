#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

struct Chef {
    long long a, b;
    int ind;
    bool operator < (const Chef &o) const {
        return b > o.b || (b == o.b && ind < o.ind);
    }
} chef[N];
int idx[N]; // idx[i] 表示原第 i 个厨师排序后是 chef 里的第几个
int n, m, q;

/*
    我们将所有厨师按 b 从大到小排序，b 相同的按原编号从小到大排序
    假设一个厨师作为主厨，只与 a 值比他小（或 a 值相同但编号比他小）的厨师合作 (条件 P)
    如此一来，A 的美味值就一定是主厨的 a 值，考虑如下表格，其中 (ai,bi) 表示排序后的第 i 个厨师
        a1+max(b1,b1) a1+max(b1,b2) a1+max(b1,b3) ...
        a2+max(b2,b1) a2+max(b2,b2) a2+max(b2,b3) ...
        a3+max(b3,b1) a3+max(b3,b2) a3+max(b3,b3) ...
        ...
    行表示主厨，列表示搭档
    由于 bi 单调递减，所以上面的表格每一行都是单调递减的，所以可以多路归并
    对每个主厨，记一个 partner[i] 表示当前考虑到主厨 i 和搭档 partner[i] 的组合
    注意要把不能合作的情况在表格里挖掉，也就是直接跳过（包括不符合条件 P 的，以及主厨和搭档彼此不和的情况）
*/

// 四个变量描述一对厨师合作的结果，依次为：满意度、两人原编号的 min、两人原编号的 max、主厨的排序后编号
priority_queue<tuple<long long, int, int, int>> pq;
set<pair<int, int>> conflict;
int partner[N];
vector<int> queries;
vector<long long> ans;

// 检查主厨 i 和搭档 j 是否可以合作
bool can_partner(int i, int j) {
    if (i == j) return false;
    // 条件 P: 搭档的 a 值比主厨小，或 a 值相同但原编号小
    if (chef[j].a > chef[i].a || (chef[j].a == chef[i].a && chef[j].ind > chef[i].ind)) {
        return false;
    }
    int u = chef[i].ind, v = chef[j].ind;
    if (u > v) swap(u, v);
    // 检查是否不和
    return conflict.find({u, v}) == conflict.end();
}

// 为主厨 i 寻找从 start_j 开始的下一个合法搭档
int find_next_partner(int i, int start_j) {
    for (int j = start_j; j <= n; ++j) {
        if (can_partner(i, j)) {
            return j;
        }
    }
    return n + 1; // 找不到
}

// 尝试将主厨 main_chef_idx 与从 start_partner_idx 开始的下一个合法搭档的组合加入优先队列
void add_next_combination(int main_chef_idx, int start_partner_idx) {
    partner[main_chef_idx] = find_next_partner(main_chef_idx, start_partner_idx);
    if (partner[main_chef_idx] <= n) {
        int j = partner[main_chef_idx];
        long long satisfaction = chef[main_chef_idx].a + max(chef[main_chef_idx].b, chef[j].b);
        int u = chef[main_chef_idx].ind, v = chef[j].ind;
        if (u > v) swap(u, v);
        pq.emplace(satisfaction, -u, -v, main_chef_idx);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) cin >> chef[i].a;
    for (int i = 1; i <= n; ++i) cin >> chef[i].b;
    for (int i = 1; i <= n; ++i) chef[i].ind = i;

    sort(chef + 1, chef + n + 1);

    for (int i = 1; i <= n; ++i) {
        idx[chef[i].ind] = i;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        conflict.insert({u, v});
    }

    int max_x = 0;
    queries.resize(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
        max_x = max(max_x, queries[i]);
    }

    // 初始化多路归并，将每行的第一个元素放入优先队列
    for (int i = 1; i <= n; ++i) {
        add_next_combination(i, 1);
    }

    ans.push_back(0); // 1-indexed
    for (int k = 1; k <= max_x; ++k) {
        if (pq.empty()) break;
        auto [s, u_neg, v_neg, main_chef_idx] = pq.top();
        pq.pop();
        ans.push_back(s);

        // 将该主厨的下一个组合放入队列
        add_next_combination(main_chef_idx, partner[main_chef_idx] + 1);
    }

    for (int x : queries) {
        cout << ans[x] << "\n";
    }

    return 0;
}