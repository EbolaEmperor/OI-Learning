#include <vector>
#include <climits>
#include <set>
#include <iostream>
#include <tuple>

class SegmentTree1 {
private:
    struct Node {
        int min_val;
        int lazy;
        Node() : min_val(0), lazy(0) {}
    };
    std::vector<Node> tree;
    int n;
    void push_down(int node, int start, int end) {
        if (tree[node].lazy != 0) {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;
            tree[left_child].lazy += tree[node].lazy;
            tree[right_child].lazy += tree[node].lazy;
            tree[left_child].min_val += tree[node].lazy;
            tree[right_child].min_val += tree[node].lazy;
            tree[node].lazy = 0;
        }
    }
    void update(int node, int start, int end, int l, int r, int val) {
        if (start > r || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            tree[node].min_val += val;
            tree[node].lazy += val;
            return;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        update(left_child, start, mid, l, r, val);
        update(right_child, mid + 1, end, l, r, val);
        tree[node].min_val = std::min(tree[left_child].min_val, tree[right_child].min_val);
    }
    int query_min(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MAX;
        }
        if (l <= start && end <= r) {
            return tree[node].min_val;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        int left_min = query_min(left_child, start, mid, l, r);
        int right_min = query_min(right_child, mid + 1, end, l, r);
        return std::min(left_min, right_min);
    }
    int find_first_zero(int node, int start, int end, int l, int r) {
        if (start > r || end < l || tree[node].min_val > 0) {
            return -1;
        }
        if (start == end) {
            return (tree[node].min_val == 0) ? start : -1;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        int pos = find_first_zero(left_child, start, mid, l, r);
        if (pos != -1) {
            return pos;
        }
        return find_first_zero(right_child, mid + 1, end, l, r);
    }
    int find_last_zero(int node, int start, int end, int l, int r) {
        if (start > r || end < l || tree[node].min_val > 0) {
            return -1;
        }
        if (start == end) {
            return (tree[node].min_val == 0) ? start : -1;
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        int pos = find_last_zero(right_child, mid + 1, end, l, r);
        if (pos != -1) {
            return pos;
        }
        return find_last_zero(left_child, start, mid, l, r);
    }
public:
    SegmentTree1(int size) {
        n = size;
        tree.resize(4 * n);
    }
    void add(int l, int r, int val) {
        update(0, 0, n - 1, l, r, val);
    }
    void subtract(int l, int r, int val) {
        update(0, 0, n - 1, l, r, -val);
    }
    int min(int l, int r) {
        return query_min(0, 0, n - 1, l, r);
    }
    int first_zero(int l, int r) {
        if (r < l) return n;
        int tmp = find_first_zero(0, 0, n - 1, l, r);
        return (tmp == -1) ? n : tmp;
    }
    int last_zero(int l, int r) {
        if (r < l) return -1;
        return find_last_zero(0, 0, n - 1, l, r);
    }
};

class SegmentTree2 {
private:
    struct Node {
        int max_val;
        std::multiset<int> values;
        Node() : max_val(INT_MIN) {}
    };
    std::vector<Node> tree;
    int n;
    void update(int node, int start, int end, int idx, int val, bool is_insert) {
        if (start == end) {
            if (is_insert) {
                tree[node].values.insert(val);
            } else {
                auto it = tree[node].values.find(val);
                if (it != tree[node].values.end()) {
                    tree[node].values.erase(it);
                }
            }
            tree[node].max_val = tree[node].values.empty() ? INT_MIN : *tree[node].values.rbegin();
            return;
        }
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        if (idx <= mid) {
            update(left_child, start, mid, idx, val, is_insert);
        } else {
            update(right_child, mid + 1, end, idx, val, is_insert);
        }
        tree[node].max_val = std::max(tree[left_child].max_val, tree[right_child].max_val);
    }
    int query_max(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node].max_val;
        }
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        int left_max = query_max(left_child, start, mid, l, r);
        int right_max = query_max(right_child, mid + 1, end, l, r);
        return std::max(left_max, right_max);
    }
public:
    SegmentTree2(int size) {
        n = size;
        tree.resize(4 * n);
    }
    void insert(int idx, int val) {
        if (idx < 0 || idx >= n) return;
        update(0, 0, n - 1, idx, val, true);
    }
    void remove(int idx, int val) {
        if (idx < 0 || idx >= n) return;
        update(0, 0, n - 1, idx, val, false);
    }
    int max(int l, int r) {
        if (l < 0) l = 0;
        if (r >= n) r = n - 1;
        if (l > r) return INT_MIN;
        return query_max(0, 0, n - 1, l, r);
    }
};

using namespace std;

void fuck() {
    int n, m;
    cin >> n >> m;
    SegmentTree1 seg1(n);
    SegmentTree2 seg2(n);
    vector<int> ans(m);

    vector<tuple<int, int, int>> opes(m);
    int p = 0; // 双指针
    for(int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        --l; --r;
        opes[i] = make_tuple(t, l, r);

        if(t == 0) seg1.add(l, r, 1);
        else seg2.insert(r, l);

        while(p <= i) {
            if(t == 0) {
                int x = seg1.last_zero(0, l - 1) + 1;
                int y = seg1.first_zero(r + 1, n - 1) - 1;
                int mx = seg2.max(x, y);
                if(mx < x) break;
            } else {
                if(seg1.min(l, r) == 0) break;
            }
            auto [tp, lp, rp] = opes[p];
            if(tp == 0) seg1.add(lp, rp, -1);
            else seg2.remove(rp, lp);
            p++;
        }
        ans[i] = p;
    }

    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        puts(l >= ans[r] ? "YES" : "NO");
    }
}

int main() {
    int T;
    cin >> T;
    while(T--) fuck();
    return 0;
}