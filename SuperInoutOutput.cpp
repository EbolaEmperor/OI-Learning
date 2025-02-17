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
    inline char getc(){
        char c = Get();
        while(isspace(c)) c = Get();
        return c;
    }
    inline void reads(char *s){
        char c = Get(); int tot = 0;
        while(isspace(c)) c = Get();
        while(!isspace(c)) s[++tot] = c, c = Get();
        s[++tot] = '\0';
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
    inline void prints(const char *s){
        int len = strlen(s);
        for(int i = 0; i < len; i++) putc(s[i]);
        putc('\n');
    }
    inline void printd(int d, double x){
        long long t = (long long)floor(x);
        print(t); putc('.'); x -= t;
        while(d--){
            double y = x * 10; x *= 10;
            int c = (int)floor(y);
            putc(c + '0');
            x -= floor(y);
        }
    }
}
