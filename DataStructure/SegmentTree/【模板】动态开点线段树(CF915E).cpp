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


const int N = 300010, M = N * 50;
int lson[M], rson[M], sum[M], lazy[M], rt, tot = 0;

void pushdown(int o, int l, int r) {
    if(lazy[o] != -1) {
        int mid = (l + r) / 2;
        if (!lson[o]) lson[o] = ++tot;
        if (!rson[o]) rson[o] = ++tot;
        lazy[lson[o]] = lazy[rson[o]] = lazy[o];
        sum[lson[o]] = lazy[o] * (mid - l +1);
        sum[rson[o]] = lazy[o] * (r - mid);
        lazy[o] = -1;
    }
}

void modify(int &o, int l, int r, int nl, int nr, int v) {
    if (!o) o = ++tot;
    if (l >= nl && r <= nr) {
        sum[o] = v * (r - l + 1);
        lazy[o] = v;
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) / 2;
    if (nl <= mid) modify(lson[o], l, mid, nl, nr, v);
    if (nr > mid) modify(rson[o], mid+1, r, nl, nr, v);
    sum[o] = sum[lson[o]] + sum[rson[o]];
}

int main() {
    int n, q, l, r, v;
    n = IO::read(); q = IO::read();
    memset(lazy, -1, sizeof(lazy));
    while (q--) {
        l = IO::read(); r = IO::read(); v = IO::read();
        modify(rt, 1, n, l, r, (v==1)?1:0);
        IO::print(n - sum[rt]);
        IO::putc('\n');
    }
    return 0;
}