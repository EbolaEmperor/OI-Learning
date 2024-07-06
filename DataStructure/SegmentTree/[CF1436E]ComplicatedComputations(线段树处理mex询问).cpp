#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
vector<int> pos[N];
int n, a[N], pre[N];
struct Node{
    Node *ls, *rs;
    int cnt;
    Node(int x = 0): ls(nullptr), rs(nullptr), cnt(x) {}
};
Node *root[N];

// 树状数组套线段树，外层下表表示值域，内层下标表示位置
// 支持：在 <=v 的值域中查找有多少个 [l,r] 中的位置

inline int lowbit(const int &x){return x & -x;}

void insert(Node* &rt, int l, int r, int k){
    if(rt == nullptr) rt = new Node(0);
    ++rt->cnt;
    if(l == r) return;
    int mid = (l + r) / 2;
    if(k <= mid) insert(rt->ls, l, mid, k);
    else insert(rt->rs, mid+1, r, k);
}

void insert(int pos, int v){
    for(; v <= n + 1; v += lowbit(v))
        insert(root[v], 1, n + 1, pos);
}

int query(Node *rt, int l, int r, int nl, int nr){
    if(rt == nullptr) return 0;
    if(l >= nl && r <= nr) return rt->cnt;
    int mid = (l + r) / 2, ans = 0;
    if(nl <= mid) ans += query(rt->ls, l, mid, nl, nr);
    if(nr > mid) ans += query(rt->rs, mid+1, r, nl, nr);
    return ans;
}

int query(int l, int r, int v){
    int ans = 0;
    for(; v > 0; v -= lowbit(v))
        ans += query(root[v], 1, n + 1, l, r);
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n + 1; ++i) pos[i].push_back(1);
    for(int i = 2; i <= n + 1; ++i){
        scanf("%d", a + i);
        // pre[i]: 上一个值为 a[i] 的位置
        pre[i] = pos[a[i]].back();
        pos[a[i]].push_back(i);
    }
    for(int i = 1; i <= n + 1; ++i) pos[i].push_back(n+2);
    if(pos[1].size() == n + 2) return puts("1"), 0;
    for(int ans = 2; ans <= n+1; ++ans){
        for(int i = 1; i < pos[ans-1].size() - 1; ++i)
            insert(pos[ans-1][i], pre[pos[ans-1][i]]);
        bool ok = 0;
        for(int i = 0; i < pos[ans].size() - 1; ++i){
            int l = pos[ans][i] + 1;
            int r = pos[ans][i + 1] - 1;
            if(l > r) continue;
            // 询问 <ans 的数（即已插入的）中，pre 值 <l 且位置在 [l,r] 之间的有几个
            if(query(l, r, l - 1) == ans - 1) {ok = 1; break;}
        }
        if(!ok) return printf("%d\n", ans), 0;
    }
    printf("%d\n", n+2);
    return 0;
}