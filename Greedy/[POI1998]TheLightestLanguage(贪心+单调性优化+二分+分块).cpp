#include <bits/stdc++.h>
using namespace std;

namespace IO{
    const int S = (1<<20)+5;
    char buf[S], *H, *T;
    inline char Get(){
        if(H == T) T = (H = buf) + fread(buf, 1, S, stdin);
        if(H == T) return -1; return *H++;
    }
    int read(){
        int x = 0, fg = 1; char c = Get();
        while(!isdigit(c) && c != '-') c = Get();
        if(c == '-') fg = -1, c = Get();
        while(isdigit(c)) x = x * 10 + c - '0', c = Get();
        return x * fg;
    }
}
using IO::read;

const int N = 2000010;
typedef long long LL;
typedef pair<LL, pair<int, int>> Point; // (权值, (行号, 列号))
typedef pair<LL, int> PLI;
vector<int> w, cnt, split, rec;
vector<int> save;
vector<LL> splitans;
vector<LL> b;
int n, k;

void read_w(){
    n = read();
    k = read();
    w.resize(k);
    for(int i = 0; i < k; ++i)
        w[i] = read();
    sort(w.begin(), w.end());
    cnt.resize(2 * n + 5);
    const int B = 1.5 * n;
    int scnt = 0;
    for(int i = 0; i <= 2 * n; i++){
        cnt[i] = min(2 * n / (i + 1), k);
        scnt += cnt[i];
        if(scnt >= B)
            scnt = 0, split.push_back(i);
    }
    if(scnt) split.push_back(2 * n);
    splitans.resize(split.size(), -1);
}

// 初始化 1 到 2n 号节点的权值 b[i]，则表格第 i 列第 j 行的数是 b[i] + w[j]
void init_b(){
    b.resize(2 * n + 5, 0);
    rec.resize(2 * n + 5, 0);
    priority_queue<PLI, vector<PLI>, greater<PLI>> nodes;
    nodes.push(make_pair(w[0], 0));
    for(int i = 1; i <= 2 * n; i++){
        auto col = nodes.top().second;
        b[i] = b[col] + w[rec[col]];
        save.push_back(col);
        nodes.pop();
        nodes.push(make_pair(b[i] + w[0], i));
        if(++rec[col] < k)
            nodes.push(make_pair(b[col] + w[rec[col]], col));
    }
}

// 计算展开 m 次的树中，前 n 小的叶节点权值之和，即表格前 m 列的第 m ~ m+n-1 小的数之和
LL compute(int m){
    LL ans = 0;
    priority_queue<PLI, vector<PLI>, greater<PLI>> nodes;
    static int pos[N];
    for(int i = 0; i < m - 1; i++) pos[save[i]]++;
    for(int i = 0; i < m; i++)
        if(pos[i] < k) nodes.push(make_pair(b[i] + w[pos[i]], i));
    for(int i = 0; i < n; i++){
        ans += nodes.top().first;
        int col = nodes.top().second;
        nodes.pop();
        if (++pos[col] < k)
            nodes.push(make_pair(b[col] + w[pos[col]], col));
    }
    memset(pos, 0, sizeof(int) * (m + 1));
    return ans;
}

LL computeSplit(int m){
    if(splitans[m] != -1) return splitans[m];
    else return splitans[m] = compute(split[m]);
}

// 在展开 l 次的树到展开 r 次的树之间找答案
LL babyStep(int l, int r){
    multiset<LL> leafs;
    LL ans = INT64_MAX, sum = 0;
    priority_queue<PLI, vector<PLI>, greater<PLI>> nodes;
    for(int i = 0; i <= 2 * n; i++) rec[i] = 0;
    for(int i = 0; i < l - 1; i++) rec[save[i]]++;
    for(int i = 0; i < l; i++)
        if(rec[i] < k) nodes.push(make_pair(b[i] + w[rec[i]], i));
    for(int i = 0; i < n; i++){
        if(nodes.empty()) break;
        auto [val, col] = nodes.top();
        leafs.insert(val);
        sum += val;
        nodes.pop();
        if(++rec[col] < k)
            nodes.push(make_pair(b[col] + w[rec[col]], col));
    }
    if(leafs.size() == n) ans = sum;
    for(int i = l; i < r; i++){
        if(leafs.empty()) break;
        sum -= *leafs.begin();
        leafs.erase(leafs.begin());
        for(int j = 0; j < cnt[i]; j++){
            if(leafs.size() >= n && b[i] + w[j] >= *leafs.rbegin()) break;
            leafs.insert(b[i] + w[j]);
            sum += b[i] + w[j];
        }
        while(leafs.size() > n){
            auto it = leafs.end(); --it;
            sum -= *it;
            leafs.erase(it);
        }
        if(leafs.size() == n){
            if(sum < ans) ans = sum;
            else break;
        }
    }
    return ans;
}

int main(){
    read_w();
    init_b();
    int l = 1, r = split.size()-1, mid;
    while(l < r){
        mid = (l + r) / 2;
        if(computeSplit(mid) == INT64_MAX
           || computeSplit(mid) > computeSplit(mid+1)) l = mid + 1;
        else r = mid;
    }
    int lft = l ? split[l-1] : 1;
    int rgt = l+1 < split.size() ? split[l+1] : 2*n;
    cout << babyStep(lft, rgt) << endl;
    return 0;
}