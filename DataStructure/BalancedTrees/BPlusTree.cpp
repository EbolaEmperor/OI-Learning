#include <bits/stdc++.h>
using namespace std;

namespace IO{
    // Input
    const int S = (1 << 18) + 5;
    char buf[S], *H, *T;
    inline char Get(){
        if(H == T) T = (H = buf) + fread(buf, 1, S, stdin);
        return (H == T) ? -1 : *H++;
    }
    inline int read(){
        int x = 0, fg = 1; char c = Get();
        while(!isdigit(c) && c != '-') c = Get();
        if(c == '-') fg = -1, c = Get();
        while(isdigit(c)) x = x * 10 + c - '0', c = Get();
        return x * fg;
    }
    // Output
    char obuf[S], *oS = obuf, *oT = oS + S - 1, c, qu[55]; int qr;
    inline void flush(){fwrite(obuf, 1, oS - obuf, stdout); oS = obuf;}
    inline void putc(char x){*oS++ = x; if(oS == oT) flush();}
    struct END{~END(){flush();} } EENNDD;
    template <class I>inline void print(I x) {
        if(!x) putc('0');
        if(x < 0) putc('-'), x = -x;
        while(x) qu[++qr] = x % 10 + '0', x /= 10;
        while(qr) putc(qu[qr--]);
    }
}


class BPlusTree {
private:
    static constexpr int MAX_LEAF_KEYS = 64;
    static constexpr int MIN_LEAF_KEYS = MAX_LEAF_KEYS / 2;
    static constexpr int MAX_CHILDREN = 64;
    static constexpr int MIN_CHILDREN = MAX_CHILDREN / 2;

    struct Node {
        bool leaf = true;
        vector<int> keys;      // leaf: real keys; internal: max key of each child
        vector<int> cnt;       // leaf only
        vector<Node*> child;   // internal only
        Node* parent = nullptr;
        Node* prev = nullptr;  // leaf chain
        Node* next = nullptr;  // leaf chain
        int sz = 0;            // total multiplicity in subtree

        explicit Node(bool is_leaf) : leaf(is_leaf) {}
    };

    Node* root = nullptr;

    static int max_key(Node* x) {
        if (x->keys.empty()) return INT_MIN;
        return x->keys.back();
    }

    static int locate_child(Node* p, Node* c) {
        for (int i = 0; i < (int)p->child.size(); ++i) {
            if (p->child[i] == c) return i;
        }
        return -1;
    }

    static void recalc(Node* x) {
        if (x->leaf) {
            x->sz = 0;
            for (int v : x->cnt) x->sz += v;
            return;
        }
        x->keys.resize(x->child.size());
        x->sz = 0;
        for (int i = 0; i < (int)x->child.size(); ++i) {
            x->child[i]->parent = x;
            x->keys[i] = max_key(x->child[i]);
            x->sz += x->child[i]->sz;
        }
    }

    void fix_up(Node* x) {
        while (x) {
            recalc(x);
            x = x->parent;
        }
    }

    Node* find_leaf(int key) const {
        Node* cur = root;
        if (!cur) return nullptr;
        while (!cur->leaf) {
            int i = 0;
            while (i < (int)cur->keys.size() && key > cur->keys[i]) ++i;
            if (i == (int)cur->child.size()) i = (int)cur->child.size() - 1;
            cur = cur->child[i];
        }
        return cur;
    }

    void insert_child_after(Node* parent, Node* left_child, Node* new_child) {
        int idx = locate_child(parent, left_child);
        parent->child.insert(parent->child.begin() + idx + 1, new_child);
        new_child->parent = parent;
        recalc(parent);
    }

    void split_leaf(Node* leaf) {
        int n = (int)leaf->keys.size();
        int mid = n / 2;

        Node* right = new Node(true);
        right->keys.assign(leaf->keys.begin() + mid, leaf->keys.end());
        right->cnt.assign(leaf->cnt.begin() + mid, leaf->cnt.end());
        leaf->keys.resize(mid);
        leaf->cnt.resize(mid);
        recalc(leaf);
        recalc(right);

        right->next = leaf->next;
        if (right->next) right->next->prev = right;
        leaf->next = right;
        right->prev = leaf;

        if (leaf == root) {
            Node* nr = new Node(false);
            nr->child = {leaf, right};
            leaf->parent = nr;
            right->parent = nr;
            recalc(nr);
            root = nr;
            return;
        }

        Node* p = leaf->parent;
        insert_child_after(p, leaf, right);
        if ((int)p->child.size() > MAX_CHILDREN) split_internal(p);
        else fix_up(p);
    }

    void split_internal(Node* node) {
        int n = (int)node->child.size();
        int mid = n / 2;

        Node* right = new Node(false);
        right->child.assign(node->child.begin() + mid, node->child.end());
        node->child.resize(mid);

        recalc(node);
        recalc(right);

        if (node == root) {
            Node* nr = new Node(false);
            nr->child = {node, right};
            node->parent = nr;
            right->parent = nr;
            recalc(nr);
            root = nr;
            return;
        }

        Node* p = node->parent;
        insert_child_after(p, node, right);
        if ((int)p->child.size() > MAX_CHILDREN) split_internal(p);
        else fix_up(p);
    }

    bool need_rebalance(Node* x) const {
        if (x == root) return false;
        if (x->leaf) return (int)x->keys.size() < MIN_LEAF_KEYS;
        return (int)x->child.size() < MIN_CHILDREN;
    }

    void shrink_root_if_needed() {
        if (!root) return;
        if (!root->leaf && root->child.size() == 1) {
            Node* old = root;
            root = root->child[0];
            root->parent = nullptr;
            delete old;
        }
        if (root) recalc(root);
    }

    void rebalance_leaf(Node* leaf) {
        if (leaf == root) return;
        Node* p = leaf->parent;
        int idx = locate_child(p, leaf);
        Node* left = (idx > 0) ? p->child[idx - 1] : nullptr;
        Node* right = (idx + 1 < (int)p->child.size()) ? p->child[idx + 1] : nullptr;

        if (left && (int)left->keys.size() > MIN_LEAF_KEYS) {
            leaf->keys.insert(leaf->keys.begin(), left->keys.back());
            leaf->cnt.insert(leaf->cnt.begin(), left->cnt.back());
            left->keys.pop_back();
            left->cnt.pop_back();
            recalc(left);
            recalc(leaf);
            fix_up(p);
            return;
        }

        if (right && (int)right->keys.size() > MIN_LEAF_KEYS) {
            leaf->keys.push_back(right->keys.front());
            leaf->cnt.push_back(right->cnt.front());
            right->keys.erase(right->keys.begin());
            right->cnt.erase(right->cnt.begin());
            recalc(right);
            recalc(leaf);
            fix_up(p);
            return;
        }

        if (left) {
            left->keys.insert(left->keys.end(), leaf->keys.begin(), leaf->keys.end());
            left->cnt.insert(left->cnt.end(), leaf->cnt.begin(), leaf->cnt.end());
            left->next = leaf->next;
            if (leaf->next) leaf->next->prev = left;
            recalc(left);

            p->child.erase(p->child.begin() + idx);
            delete leaf;
            recalc(p);
            fix_up(p);
            if (need_rebalance(p)) rebalance_internal(p);
        } else if (right) {
            leaf->keys.insert(leaf->keys.end(), right->keys.begin(), right->keys.end());
            leaf->cnt.insert(leaf->cnt.end(), right->cnt.begin(), right->cnt.end());
            leaf->next = right->next;
            if (right->next) right->next->prev = leaf;
            recalc(leaf);

            p->child.erase(p->child.begin() + idx + 1);
            delete right;
            recalc(p);
            fix_up(p);
            if (need_rebalance(p)) rebalance_internal(p);
        }

        shrink_root_if_needed();
    }

    void rebalance_internal(Node* node) {
        if (node == root) {
            shrink_root_if_needed();
            return;
        }
        Node* p = node->parent;
        int idx = locate_child(p, node);
        Node* left = (idx > 0) ? p->child[idx - 1] : nullptr;
        Node* right = (idx + 1 < (int)p->child.size()) ? p->child[idx + 1] : nullptr;

        if (left && (int)left->child.size() > MIN_CHILDREN) {
            Node* moved = left->child.back();
            left->child.pop_back();
            node->child.insert(node->child.begin(), moved);
            moved->parent = node;
            recalc(left);
            recalc(node);
            fix_up(p);
            return;
        }

        if (right && (int)right->child.size() > MIN_CHILDREN) {
            Node* moved = right->child.front();
            right->child.erase(right->child.begin());
            node->child.push_back(moved);
            moved->parent = node;
            recalc(right);
            recalc(node);
            fix_up(p);
            return;
        }

        if (left) {
            for (Node* c : node->child) {
                left->child.push_back(c);
                c->parent = left;
            }
            recalc(left);
            p->child.erase(p->child.begin() + idx);
            delete node;
            recalc(p);
            fix_up(p);
            if (need_rebalance(p)) rebalance_internal(p);
        } else if (right) {
            for (Node* c : right->child) {
                node->child.push_back(c);
                c->parent = node;
            }
            recalc(node);
            p->child.erase(p->child.begin() + idx + 1);
            delete right;
            recalc(p);
            fix_up(p);
            if (need_rebalance(p)) rebalance_internal(p);
        }

        shrink_root_if_needed();
    }

public:
    BPlusTree() { root = new Node(true); }

    void insert(int key) {
        Node* leaf = find_leaf(key);
        auto it = lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        int pos = (int)(it - leaf->keys.begin());
        if (it != leaf->keys.end() && *it == key) {
            leaf->cnt[pos]++;
            fix_up(leaf);
            return;
        }

        leaf->keys.insert(it, key);
        leaf->cnt.insert(leaf->cnt.begin() + pos, 1);
        recalc(leaf);
        if ((int)leaf->keys.size() > MAX_LEAF_KEYS) split_leaf(leaf);
        else fix_up(leaf->parent);
    }

    void erase_one(int key) {
        Node* leaf = find_leaf(key);
        auto it = lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        if (it == leaf->keys.end() || *it != key) return;

        int pos = (int)(it - leaf->keys.begin());
        if (leaf->cnt[pos] > 1) {
            leaf->cnt[pos]--;
            fix_up(leaf);
            return;
        }

        leaf->keys.erase(leaf->keys.begin() + pos);
        leaf->cnt.erase(leaf->cnt.begin() + pos);
        recalc(leaf);

        if (leaf == root) return;
        fix_up(leaf->parent);
        if (need_rebalance(leaf)) rebalance_leaf(leaf);
        shrink_root_if_needed();
    }

    int count_less(int key) const {
        Node* cur = root;
        int ans = 0;
        while (!cur->leaf) {
            bool down = false;
            for (int i = 0; i < (int)cur->child.size(); ++i) {
                if (key <= cur->keys[i]) {
                    cur = cur->child[i];
                    down = true;
                    break;
                }
                ans += cur->child[i]->sz;
            }
            if (!down) return ans;
        }
        for (int i = 0; i < (int)cur->keys.size(); ++i) {
            if (cur->keys[i] < key) ans += cur->cnt[i];
            else break;
        }
        return ans;
    }

    int kth(int k) const {
        Node* cur = root;
        while (!cur->leaf) {
            for (int i = 0; i < (int)cur->child.size(); ++i) {
                if (k <= cur->child[i]->sz) {
                    cur = cur->child[i];
                    break;
                }
                k -= cur->child[i]->sz;
            }
        }
        for (int i = 0; i < (int)cur->keys.size(); ++i) {
            if (k <= cur->cnt[i]) return cur->keys[i];
            k -= cur->cnt[i];
        }
        return 0;
    }

    int predecessor(int key) const {
        Node* leaf = find_leaf(key);
        int pos = (int)(lower_bound(leaf->keys.begin(), leaf->keys.end(), key) - leaf->keys.begin());
        if (pos > 0) return leaf->keys[pos - 1];
        Node* cur = leaf->prev;
        while (cur && cur->keys.empty()) cur = cur->prev;
        return cur->keys.back();
    }

    int successor(int key) const {
        Node* leaf = find_leaf(key);
        int pos = (int)(upper_bound(leaf->keys.begin(), leaf->keys.end(), key) - leaf->keys.begin());
        if (pos < (int)leaf->keys.size()) return leaf->keys[pos];
        Node* cur = leaf->next;
        while (cur && cur->keys.empty()) cur = cur->next;
        return cur->keys.front();
    }
};

int main() {
    int n = IO::read();
    BPlusTree tree;

    while (n--) {
        int opt = IO::read();
        int x = IO::read();
        if (opt == 1) {
            tree.insert(x);
        } else if (opt == 2) {
            tree.erase_one(x);
        } else if (opt == 3) {
            IO::print(tree.count_less(x) + 1);
            IO::putc('\n');
        } else if (opt == 4) {
            IO::print(tree.kth(x));
            IO::putc('\n');
        } else if (opt == 5) {
            IO::print(tree.predecessor(x));
            IO::putc('\n');
        } else if (opt == 6) {
            IO::print(tree.successor(x));
            IO::putc('\n');
        }
    }
    return 0;
}