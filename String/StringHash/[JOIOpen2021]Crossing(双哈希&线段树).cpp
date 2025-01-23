#include <bits/stdc++.h>
using namespace std;

namespace IO{
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
    inline char getc(){
        char c = Get();
        while(isspace(c)) c = Get();
        return c;
    }
}
using IO::read;
using IO::getc;

const int N = 200010;

class Hash{
private:
    int p, base;
    int pwb[N], allsame[N][3];
    unordered_map<int, int> save;
public:
    Hash(int p, int base): p(p), base(base) {
        pwb[0] = 1;
        allsame[0][0] = 1;
        allsame[0][1] = 2;
        allsame[0][2] = 3;
        for(int i = 1; i < N; i++){
            pwb[i] = 1ll * base * pwb[i - 1] % p;
            allsame[i][0] = (1ll * allsame[i - 1][0] * base + 1) % p;
            allsame[i][1] = (1ll * allsame[i - 1][1] * base + 2) % p;
            allsame[i][2] = (1ll * allsame[i - 1][2] * base + 3) % p;
        }
    }

    int merge(int a, int b, int blen) const{
        return (1ll * a * pwb[blen] + b) % p;
    }

    int getAllSame(int len, int c) const{
        return allsame[len - 1][c - 1];
    }

    int getHash(const vector<int> &a) const{
        int res = 0;
        for(int x : a)
            res = (1ll * res * base + (x + 1)) % p;
        return res;
    }

    void insert(const vector<int> &a){
        save[getHash(a)] = 1;
    }

    bool inPack(int val) const{
        return save.count(val);
    }
};

const int p1 = 1e9 + 7, base1 = 233;
const int p2 = 998244353, base2 = 113;
Hash h1(p1, base1);
Hash h2(p2, base2);
int val1[N << 2], val2[N << 2], cover[N << 2];
vector<int> a;

void pushup(int o, int rlen){
    val1[o] = h1.merge(val1[o << 1], val1[o << 1 | 1], rlen);
    val2[o] = h2.merge(val2[o << 1], val2[o << 1 | 1], rlen);
}

void down(int o, int l, int r, int x){
    val1[o] = h1.getAllSame(r - l + 1, x);
    val2[o] = h2.getAllSame(r - l + 1, x);
    cover[o] = x;
}

void pushdown(int o, int l, int r){
    if(!cover[o]) return;
    int mid = (l + r) / 2;
    down(o << 1, l, mid, cover[o]);
    down(o << 1 | 1, mid + 1, r, cover[o]);
    cover[o] = 0;
}

void build(int o, int l, int r){
    if(l == r){
        val1[o] = val2[o] = a[l] + 1;
        return;
    }
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    pushup(o, r - mid);
}

void update(int o, int l, int r, int nl, int nr, int x){
    if(l >= nl && r <= nr) return down(o, l, r, x + 1);
    int mid = (l + r) / 2;
    pushdown(o, l, r);
    if(nl <= mid) update(o << 1, l, mid, nl, nr, x);
    if(nr > mid) update(o << 1 | 1, mid + 1, r, nl, nr, x);
    pushup(o, r - mid);
}

int mapping(char c){
    if(c == 'J') return 0;
    if(c == 'O') return 1;
    return 2;
}

int croos(int x, int y){
    return (6 - x - y) % 3;
}

vector<int> croos(const vector<int> &a, const vector<int> &b){
    int n = a.size();
    vector<int> s(n);
    for(int i = 0; i < n; i++)
        s[i] = croos(a[i], b[i]);
    return s;
}

vector<int> readString(int n){
    vector<int> s(n);
    for(int j = 0; j < n; j++)
        s[j] = mapping(getc());
    return s;
}

void initPack(int n){
    vector<vector<int>> s(3);
    for(int i = 0; i < 3; i++){
        s[i] = readString(n);
        h1.insert(s[i]);
        h2.insert(s[i]);
    }
    vector<int> cs[6];
    cs[0] = croos(s[0], s[1]);
    cs[1] = croos(s[0], s[2]);
    cs[2] = croos(s[1], s[2]);
    cs[3] = croos(cs[0], s[2]);
    cs[4] = croos(cs[1], s[1]);
    cs[5] = croos(cs[2], s[0]);
    for(int i = 0; i < 6; i++){
        h1.insert(cs[i]);
        h2.insert(cs[i]);
    }
}

inline void check(){
    puts(h1.inPack(val1[1]) && h2.inPack(val2[1]) ? "Yes" : "No");
}

int main(){
    int n = read();
    initPack(n);
    int Q = read();
    a = readString(n);
    build(1, 0, n - 1);
    check();
    while(Q--){
        int l = read() - 1, r = read() - 1, x = mapping(getc());
        update(1, 0, n - 1, l, r, x);
        check();
    }
    return 0;
}