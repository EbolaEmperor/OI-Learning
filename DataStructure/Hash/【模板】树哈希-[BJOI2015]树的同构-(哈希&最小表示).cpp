#include <bits/stdc++.h>
using namespace std;

class Tree {
private:
    int n, mnS;
    vector<vector<int>> adj;
    vector<int> maxSubtr, siz;

    void getSize(int u, int fa) {
        siz[u] = 1;
        maxSubtr[u] = n + 1;
        for (int v : adj[u]) {
            if (v == fa) continue;
            getSize(v, u);
            siz[u] += siz[v];
            maxSubtr[u] = max(maxSubtr[u], siz[v]);
        }
        maxSubtr[u] = max(maxSubtr[u], n - siz[u]);
        mnS = min(mnS, maxSubtr[u]);
    }

    string getHash(int u, int fa = -1) const {
        string trHash = "0";
        vector<string> subHash;
        for (int v : adj[u]) {
            if (v == fa) continue;
            subHash.push_back(getHash(v, u));
        }
        sort(subHash.begin(), subHash.end());
        for (auto &s : subHash)
            trHash += s;
        trHash += "1";
        return trHash;
    }

public:
    Tree(const vector<int> &fa) {
        n = fa.size();
        adj.resize(n);
        siz.resize(n);
        maxSubtr.resize(n);
        for (int i = 0; i < fa.size(); ++i) {
            int f = fa[i];
            if (f >= 0) {
                adj[i].push_back(f);
                adj[f].push_back(i);
            }
        }
        mnS = n + 1;
        getSize(0, -1);
    }

    vector<int> getBaryCenter() const {
        vector<int> res;
        for (int i = 0; i < n; i++)
            if (maxSubtr[i] == mnS)
                res.push_back(i);
        return res;
    }

    string getHash() const {
        auto bary = getBaryCenter();
        string trHash = "2";
        for (int rt : bary)
            trHash = min(trHash, getHash(rt));
        return trHash;
    }
};

int main() {
    map<string, int> treeInd;
    int M;
    cin >> M;
    for (int ind = 1; ind <= M; ++ind) {
        int n;
        cin >> n;
        vector<int> fa(n);
        for (int i = 0; i < n; i++) {
            cin >> fa[i];
            --fa[i];
        }
        Tree tree(fa);
        auto hashVal = tree.getHash();
        if (!treeInd.count(hashVal))
            treeInd[hashVal] = ind;
        cout << treeInd[hashVal] << "\n";
    }
    return 0;
}