#include<bits/stdc++.h>
using namespace std;

typedef __int128 LLL;

LLL read(){
	LLL x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + (c - '0'), c = getchar();
	return x;
}
void write(LLL x){
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}


class ExCRT {
private:
    struct Equ { LLL b, m; };
    Equ last;

    LLL ExGcd(LLL a, LLL b, LLL &x, LLL &y) const {
        if (b == 0) { x = 1; y = 0; return a; }
        LLL g = ExGcd(b, a % b, x, y);
        LLL t = x; x = y;
        y = t - (a / b) * y;
        return g;
    }

    /* 合并两个同余方程 */
    Equ CRTmerge(Equ a1, Equ a2) const {
        LLL k1, k2;
        LLL g = ExGcd(a1.m, a2.m, k1, k2);
        LLL c = a2.b - a1.b;
        if (c % g != 0)
            throw invalid_argument("No solution.");
        k1 = k1 * (c / g) % (a2.m / g);
        LLL x = k1 * a1.m + a1.b;
        LLL lcm = a1.m / g * a2.m;
        x = (x % lcm + lcm) % lcm;
        return Equ{ x, lcm };
    }

    /* 将 ax ≡ b (mod m) 规约成 x ≡ b2 (mod m2)；若无解抛异常 */
    Equ reduce(LLL a, LLL b, LLL m) const {
        LLL x, y;
        LLL g = ExGcd(a, m, x, y);
        if (b % g != 0)
            throw invalid_argument("No solution.");
        a /= g;  b /= g;  m /= g;
        LLL inv = (x % m + m) % m;
        LLL new_b = inv * b % m;
        return Equ{ new_b, m };
    }

public:
    ExCRT() { last.m = last.b = -1; }

    /* 插入 x ≡ b (mod m) */
    void insert(LLL m, LLL b) {
        b = (b % m + m) % m;
        if (last.m == -1) last = Equ{ b, m };
        else last = CRTmerge(last, Equ{ b, m });
    }

    /* 插入 ax ≡ b (mod m) */
    void insert(LLL a, LLL b, LLL m) {
        a = (a % m + m) % m;
        b = (b % m + m) % m;
        Equ e = reduce(a, b, m);
        insert(e.m, e.b);
    }

    LLL answer() const { return last.b; }
};

int main(){
	int n;
	scanf("%d",&n);
	ExCRT excrt;
	LLL m = read(), b = read();
	excrt.insert(m, b);
	for(int i = 2; i <= n; i++){
		m = read(); b = read();
		try {
			excrt.insert(m, b);
		} catch (const invalid_argument &e) {
			puts("No solution.");
			return 0;
		}
		excrt.insert(m, b);
	}
	write(excrt.answer());
	return 0;
}
