#include <bits/stdc++.h>
using namespace std;

/* ------------------ 小工具：64 位字符串哈希（FNV-1a） ------------------ */
static inline uint64_t hash_str(const string &s){
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return h;
}
struct PairKey {
    uint64_t a, b;
    bool operator==(const PairKey& o) const { return a==o.a && b==o.b; }
};
struct PairKeyHash {
    size_t operator()(const PairKey& k) const {
        uint64_t x = k.a ^ (k.b + 0x9e3779b97f4a7c15ULL + (k.a<<6) + (k.a>>2));
        return (size_t)x;
    }
};

/* ------------------ 链式 Trie ------------------ */
struct Trie {
    struct E { int to, nxt; unsigned char ch; };
    vector<int> head;     // 每个节点的第一条边
    vector<E> edges;      // 所有边
    Trie(){ clear(); }
    void clear(){
        head.clear(); edges.clear();
        new_node(); // root = 0
    }
    int new_node(){ head.push_back(-1); return (int)head.size()-1; }
    // 找到 u 下字符 ch 的孩子；没有返回 -1
    int findChild(int u, unsigned char ch) const {
        for(int e=head[u]; e!=-1; e=edges[e].nxt)
            if(edges[e].ch==ch) return edges[e].to;
        return -1;
    }
    int addChild(int u, unsigned char ch){
        int v = new_node();
        edges.push_back({v, head[u], ch});
        head[u] = (int)edges.size()-1;
        return v;
    }
    // 插入字符串，返回终止节点
    int insert(const string& s){
        int u=0;
        for(unsigned char c: s){
            int v = findChild(u, c);
            if(v==-1) v = addChild(u, c);
            u=v;
        }
        return u;
    }
    // 沿着 s 尽可能向下走，返回能到达的“最深”节点
    int follow_deepest(const string& s) const {
        int u=0;
        for(unsigned char c: s){
            int v = findChild(u, c);
            if(v==-1) break;
            u=v;
        }
        return u;
    }
};

/* ------------------ Fenwick：区间加 / 单点查 ------------------ */
struct BIT {
    int n; vector<int> bit;
    void init(int n_){ n=n_; bit.assign(n+2, 0); }
    void add(int i,int v){ for(; i<=n; i+=i&-i) bit[i]+=v; }
    void range_add(int l,int r,int v){ if(l>r) return; add(l,v); add(r+1,-v); }
    int point_query(int i){ int s=0; for(; i>0; i-=i&-i) s+=bit[i]; return s; }
};

/* ------------------ 组内原始数据 ------------------ */
struct Group {
    // 规则 (left, right) ：left = s1 去掉“本质”的左段；right = s1 去掉“本质”的右段
    vector<pair<string,string>> dictLR;
    // 询问 (L, R, id)
    struct Q { string L, R; int id; };
    vector<Q> qs;
};

/* ------------------ 主程序 ------------------ */
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; 
    if(!(cin>>n>>q)) return 0;

    // 按“替换部分（本质）”分组（必须完全相等才可能有贡献）【题解原理】
    unordered_map<PairKey,int,PairKeyHash> gid; gid.reserve(n*2);
    vector<Group> groups;

    // 读规则，切出“本质”以及“左右段”，按本质分桶
    for(int i=0;i<n;i++){
        string s1,s2; cin>>s1>>s2;
        int L=(int)s1.size();
        int l=0; while(l<L && s1[l]==s2[l]) ++l;
        int r=L-1; while(r>=0 && s1[r]==s2[r]) --r;
        if(l>r){ // s1==s2，该规则不可能对任一询问贡献，直接忽略（题解里也提醒） 
            continue;
        }
        string mid1 = s1.substr(l, r-l+1);
        string mid2 = s2.substr(l, r-l+1);
        PairKey key{ hash_str(mid1), hash_str(mid2) };

        string left  = s1.substr(0, l);
        string right = s1.substr(r+1);

        int id;
        auto it = gid.find(key);
        if(it==gid.end()){
            id = (int)groups.size();
            gid.emplace(key,id);
            groups.push_back(Group{});
        }else id=it->second;
        groups[id].dictLR.emplace_back(std::move(left), std::move(right));
    }

    vector<long long> ans(q, 0);

    // 读询问，切出“本质”和“左右段”，分到同一类；若组不存在，答案为 0
    for(int j=0;j<q;j++){
        string t1,t2; cin>>t1>>t2;
        int L=(int)t1.size();
        int l=0; while(l<L && t1[l]==t2[l]) ++l;
        int r=L-1; while(r>=0 && t1[r]==t2[r]) --r;
        // 题面保证 t1!=t2，因此一定 l<=r
        string mid1 = t1.substr(l, r-l+1);
        string mid2 = t2.substr(l, r-l+1);
        PairKey key{ hash_str(mid1), hash_str(mid2) };

        string left  = t1.substr(0, l);
        string right = t1.substr(r+1);

        auto it = gid.find(key);
        if(it==gid.end()){
            ans[j]=0; // 该“本质”在规则中不存在
        }else{
            int id = it->second;
            groups[id].qs.push_back(Group::Q{ std::move(left), std::move(right), j });
        }
    }

    // 逐组处理
    Trie trieR, trieL;
    vector<int> tin, tout;
    BIT bit;

    for(auto &G : groups){
        if(G.qs.empty()) continue; // 无询问可跳过

        // 预估容量（优化常数）
        size_t sumR=1, sumL=1;
        for(auto &p: G.dictLR){ sumL += p.first.size(); sumR += p.second.size(); }

        /* ---------- 1) 构建右 trie 并做 Euler 序 ---------- */
        trieR.clear();
        trieR.head.reserve(sumR+1);
        trieR.edges.reserve(sumR+1);

        // 记录每条规则右端对应的“右 trie 终止节点”
        vector<int> vNode(G.dictLR.size());
        for(size_t i=0;i<G.dictLR.size();++i){
            int v = trieR.insert(G.dictLR[i].second);
            vNode[i] = v;
        }

        // Euler（非递归），得到每个右节点的 [tin, tout]
        int Nrt = (int)trieR.head.size();
        tin.assign(Nrt, 0); tout.assign(Nrt, 0);
        int T=0;

        // 为了遍历孩子，需要把每个节点的边链表“枚举指针”放到栈上
        struct F { int u; int e; int state; }; // state 0: 进点；1: 处理中/出点
        vector<F> st; st.reserve(Nrt*2);
        st.push_back({0, trieR.head[0], 0});
        while(!st.empty()){
            F cur = st.back(); st.pop_back();
            int u=cur.u, e=cur.e, state=cur.state;
            if(state==0){
                tin[u]=++T;
                st.push_back({u, trieR.head[u], 1}); // 准备处理孩子
            }else{
                // 依次走孩子
                int ee = e;
                if(ee!=-1){
                    // 把自己（剩余链）放回，再压一个孩子的“进点”
                    st.push_back({u, trieR.edges[ee].nxt, 1});
                    int v = trieR.edges[ee].to;
                    st.push_back({v, trieR.head[v], 0});
                }else{
                    tout[u]=T;
                }
            }
        }

        bit.init(T+2); // Fenwick 大小按时间戳

        /* ---------- 2) 构建左 trie（插入反转后的左段） ---------- */
        trieL.clear();
        trieL.head.reserve(sumL+1);
        trieL.edges.reserve(sumL+1);

        vector<int> uNode(G.dictLR.size());
        for(size_t i=0;i<G.dictLR.size();++i){
            string L = G.dictLR[i].first;
            reverse(L.begin(), L.end());
            uNode[i] = trieL.insert(L);
        }

        // 在左 trie 的每个节点挂“该节点对应的规则右端节点编号 v”
        vector<vector<int>> addAt(trieL.head.size());
        for(size_t i=0;i<G.dictLR.size();++i){
            addAt[uNode[i]].push_back(vNode[i]);
        }

        // 把询问挂到“L 反转后在左 trie 能走到的最深节点”上；
        // 每个询问还需要 R 在右 trie 的“最深可达节点”的 tin
        struct QOnNode { int tinR; int id; };
        vector<vector<QOnNode>> qAt(trieL.head.size());
        for(auto &qq : G.qs){
            string L = qq.L; reverse(L.begin(), L.end());
            int u = trieL.follow_deepest(L); // 左：尽量往下走，走不动就停祖先【题解描述】
            int w = trieR.follow_deepest(qq.R); // 右：尽量往下走
            qAt[u].push_back(QOnNode{ tin[w], qq.id });
        }

        /* ---------- 3) 离线 DFS 左 trie + BIT 区间加 / 点查 ---------- */
        struct S { int u, e, state; }; // state 0: 入点；1: 处理中/出点
        vector<S> st2; st2.reserve(trieL.head.size()*2);
        st2.push_back({0, trieL.head[0], 0});
        while(!st2.empty()){
            S cur = st2.back(); st2.pop_back();
            int u=cur.u, e=cur.e, state=cur.state;
            if(state==0){
                // 入点：把此节点挂的所有 v 做区间 +1
                for(int v : addAt[u]) bit.range_add(tin[v], tout[v], +1);
                // 回答挂在此节点的所有询问（点查）
                for(auto &qq : qAt[u]) ans[qq.id] += bit.point_query(qq.tinR);
                // 遍历孩子
                st2.push_back({u, trieL.head[u], 1});
            }else{
                int ee = e;
                if(ee!=-1){
                    st2.push_back({u, trieL.edges[ee].nxt, 1});
                    int v = trieL.edges[ee].to;
                    st2.push_back({v, trieL.head[v], 0});
                }else{
                    // 出点：撤销贡献
                    for(int v : addAt[u]) bit.range_add(tin[v], tout[v], -1);
                }
            }
        }

        // 释放组内大容器（交给下一组复用内存）
        vector<pair<string,string>>().swap(G.dictLR);
        vector<Group::Q>().swap(G.qs);
    }

    // 输出
    for(int i=0;i<q;i++) cout<<ans[i]<<"\n";
    return 0;
}
