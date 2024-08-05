// 复杂度 O(n * log n * log log n)
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
typedef pair<LL, pair<int,int>> Point;
vector<int> w, cnt, split, rec;
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
    const int B = n;
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
    rec.resize(2 * n + 5, -1); rec[0] = 0;
    priority_queue<Point, vector<Point>, greater<Point>> nodes;
    nodes.push(make_pair(w[0], make_pair(0, 0)));
    for(int i = 1; i <= 2 * n; i++){
        auto pos = nodes.top().second;
        nodes.pop();
        b[i] = b[pos.first] + w[pos.second];
        auto pos1 = make_pair(pos.first + 1, pos.second);
        if(rec[pos1.first] < pos1.second){
            nodes.push(make_pair(b[pos1.first] + w[pos1.second], pos1));
            rec[pos1.first] = pos1.second;
        }
        auto pos2 = make_pair(pos.first, pos.second + 1);
        if(pos2.second < w.size() && rec[pos2.first] < pos2.second){
            nodes.push(make_pair(b[pos2.first] + w[pos2.second], pos2));
            rec[pos2.first] = pos2.second;
        }
    }
}

// 计算展开 m 次的树中，前 n 小的叶节点权值之和，即表格前 m 列的第 m ~ m+n-1 小的数之和
LL compute(int m){
    LL ans = 0;
    priority_queue<Point, vector<Point>, greater<Point>> nodes;
    nodes.push(make_pair(w[0], make_pair(0, 0)));
    rec[0] = 0;
    for(int i = 1; i <= 2 * n; i++) rec[i] = -1;
    for(int i = 1; i < m + n; i++){
        if(nodes.empty()) return INT64_MAX;
        auto pos = nodes.top().second;
        nodes.pop();
        if(i >= m) ans += b[pos.first] + w[pos.second];
        auto pos1 = make_pair(pos.first + 1, pos.second);
        if(pos1.first < m && rec[pos1.first] < pos1.second){
            nodes.push(make_pair(b[pos1.first] + w[pos1.second], pos1));
            rec[pos1.first] = pos1.second;
        }
        auto pos2 = make_pair(pos.first, pos.second + 1);
        if(pos2.second < w.size() && rec[pos2.first] < pos2.second){
            nodes.push(make_pair(b[pos2.first] + w[pos2.second], pos2));
            rec[pos2.first] = pos2.second;
        }
    }
    return ans;
}

LL computeSplit(int m){
    if(splitans[m] != -1) return splitans[m];
    else return splitans[m] = compute(split[m]);
}

// 在展开 l 次的树到展开 r 次的树之间找答案
LL babyStep(int l, int r){
    set<Point> nodes;
    LL ans = INT64_MAX, sum = w[0];
    nodes.insert(make_pair(w[0], make_pair(0, 0)));
    rec[0] = 0;
    for(int i = 1; i <= 2 * n; i++) rec[i] = -1;
    auto it = nodes.begin();
    for(int i = 1; i < l + n; i++){
        if(i < l){
            it = nodes.begin();
            nodes.erase(it);
            auto pos = it->second;
            sum -= b[pos.first] + w[pos.second];
        } else if(i == l) {
            it = nodes.begin();
        } else {
            if(nodes.size() >= n) break;
            if(++it == nodes.end()) break;
        }
        auto pos = it->second;
        auto pos1 = make_pair(pos.first + 1, pos.second);
        if(pos1.first < l && rec[pos1.first] < pos1.second){
            nodes.insert(make_pair(b[pos1.first] + w[pos1.second], pos1));
            rec[pos1.first] = pos1.second;
            sum += b[pos1.first] + w[pos1.second];
        }
        auto pos2 = make_pair(pos.first, pos.second + 1);
        if(pos2.second < w.size() && rec[pos2.first] < pos2.second){
            nodes.insert(make_pair(b[pos2.first] + w[pos2.second], pos2));
            rec[pos2.first] = pos2.second;
            sum += b[pos2.first] + w[pos2.second];
        }
    }
    for(int i = l; i < r; i++){
        if(nodes.empty()) break;
        sum -= nodes.begin()->first;
        nodes.erase(nodes.begin());
        for(int j = 0; j < cnt[i]; j++){
            nodes.insert(make_pair(b[i] + w[j], make_pair(i, j)));
            sum += b[i] + w[j];
        }
        while(nodes.size() > n){
            auto it = nodes.end(); --it;
            sum -= it->first;
            nodes.erase(it);
        }
        if(nodes.size() == n){
            if(sum < ans) ans = sum;
            else break;
        }
    }
    return ans;
}

int main(){
    read_w();
    init_b();
    int l = 0, r = split.size()-1, mid;
    while(l < r){
        mid = (l + r) / 2;
        if(computeSplit(mid) >= computeSplit(mid+1)) l = mid + 1;
        else r = mid;
    }
    int lft = l ? split[l-1] : 1;
    cout << babyStep(lft, split[l+1]) << endl;
    return 0;
}