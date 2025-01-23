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
    inline void printd(double x){
        if(x < 0) putc('-'), x = -x;
        long long y = round(x * 100);
        print(y / 100);
        putc('.');
        putc(y / 10 % 10 + '0');
        putc(y % 10 + '0');
    }
}
using IO::read;
using IO::printd;
using IO::putc;

const int N = 210;
bool known[N];
double G[N][N], x[N];
int n, m, k, q;

bool Gauss(){
    for(int i = 1; i <= n; i++){
        int pos = i;
        for(int j = i + 1; j <= n; j++)
            if(fabs(G[j][i]) > fabs(G[pos][i])) pos = j;
        if(fabs(G[pos][i]) < 1e-15) return false;
        if(pos != i)
            for(int j = 1; j <= n + 1; j++)
                swap(G[i][j], G[pos][j]);
        vector<int> col;
        for(int k = i; k <= n + 1; k++)
            if(fabs(G[i][k]) > 1e-15) col.push_back(k);
        for(int j = i + 1; j <= n; j++){
            double t = G[j][i] / G[i][i];
            if(fabs(G[j][i]) < 1e-15) continue;
            for(int k : col)
                G[j][k] -= G[i][k] * t;
        }
    }
    return true;
}

void solve(){
    assert(Gauss());
    for(int i = n; i >= 1; i--){
        x[i] = G[i][n + 1] / G[i][i];
        for(int j = 1; j < i; j++)
            G[j][n + 1] -= G[j][i] * x[i];
    }
}

int main(){
    n = read(); m = read(); k = read(); q = read();
    while(k--){
        int u = read(), v = read();
        G[u][u] = 1;
        G[u][n + 1] = v;
        known[u] = 1;
    }
    known[0] = 1;
    while(m--){
        int u = read(), v = read(), R = read();
        if(!known[u]) G[u][u] += 1.0 / R, G[u][v] -= 1.0 / R;
        if(!known[v]) G[v][v] += 1.0 / R, G[v][u] -= 1.0 / R;
    }
    solve();
    while(q--){
        int a = read(), b = read();
        printd(x[a] - x[b]);
        putc('\n');
    }
    return 0;
}