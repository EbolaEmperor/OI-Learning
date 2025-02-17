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

class ExCRT{
private:
	struct Equ{LLL b, m;};
	Equ last;
	LLL ExGcd(LLL a, LLL b, LLL &x, LLL &y) const{
		if(b == 0){x = 1; y = 0; return a;}
		LLL g = ExGcd(b, a % b, x, y);
		LLL t = x; x = y;
		y = t - (a / b) * y;
		return g;
	}
	Equ CRTmerge(Equ a1, Equ a2) const{
		LLL k1, k2;
		LLL g = ExGcd(a1.m, a2.m, k1, k2);
		LLL c = a2.b - a1.b;
		if(c % g != 0) puts("No!"), exit(0);
		k1 = k1 * (c / g) % (a2.m / g);
		LLL x = k1 * a1.m + a1.b;
		LLL lcm = a1.m / g * a2.m;
		x = (x % lcm + lcm) % lcm;
		return Equ{x, lcm};
	}
public:
	ExCRT() { last.m = last.b = -1; }
	void insert(LLL module, LLL residule){
		if(last.m == -1) last = Equ{residule, module};
		else last = CRTmerge(last, Equ{residule, module});
	}
	LLL answer() const{ return last.b; }
};

int main(){
	int n;
	scanf("%d",&n);
	ExCRT excrt;
	LLL m = read(), b = read();
	excrt.insert(m, b);
	for(int i = 2; i <= n; i++){
		m = read(); b = read();
		excrt.insert(m, b);
	}
	write(excrt.answer());
	return 0;
}
