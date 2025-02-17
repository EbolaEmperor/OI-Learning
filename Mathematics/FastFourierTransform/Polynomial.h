#pragma once

#include <bits/stdc++.h>
using namespace std;

const int Mod = 998244353;
const int unitImage = 86583718;
const int inv2 = (Mod + 1) / 2;

random_device seed;
mt19937 rnd(seed());

int Pow(int a, int b);
void NTT(int *a, int len, bool INTT);
int sqrtMod(int n);

class Polynomial{
private:
    int n;
    int *a;
    Polynomial& resize(int _n);
    Polynomial& leftmove(int k);

public:
    Polynomial(): n(-1), a(nullptr){}
    Polynomial(const int &_n);
    Polynomial(const int &_n, const int *p);
    Polynomial(const Polynomial &rhs);
    ~Polynomial();

    int operator () (int x) const;
    int operator [] (int i) const;
    int& operator [] (int i);

    Polynomial& operator = (const Polynomial &rhs);
    Polynomial operator + (const Polynomial &rhs) const;
    Polynomial operator - (const Polynomial &rhs) const;
    Polynomial operator - () const;
    Polynomial operator * (int k) const;
    Polynomial operator * (const Polynomial &rhs) const;
    friend Polynomial pow(Polynomial lhs, int kk, int b);
    Polynomial derivative() const;
    Polynomial integral() const;

    friend Polynomial inv(const Polynomial &p, int n);
    friend Polynomial log(const Polynomial &p);
    friend Polynomial exp(const Polynomial &p, int n);
    friend Polynomial sqrt(const Polynomial &p, int n);

    friend Polynomial sin(const Polynomial &p);
    friend Polynomial cos(const Polynomial &p);
    friend Polynomial tan(const Polynomial &p);

    friend Polynomial asin(const Polynomial &p);
    friend Polynomial acos(const Polynomial &p);
    friend Polynomial atan(const Polynomial &p);
};





//---------------------------------- Implemention ----------------------------------

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % Mod)
        if(b & 1) ans = 1ll * ans * a % Mod;
    return ans;
}

void NTT(int *a, int len, bool INTT){
    int *r = new int[len];
    r[0] = 0;
    int l = -1;
    for(int x = len; x; x >>= 1) ++l;
    for(int i = 1; i < len; i++) r[i] = (r[i / 2] / 2) | ((i & 1) << (l - 1));
    for(int i = 0; i < len; i++) if(i < r[i]) swap(a[i], a[r[i]]);
    delete[] r;
    for(int i = 1; i < len; i <<= 1){
        int p = (i << 1);
        int wn = Pow(3, (Mod - 1) / p);
        if(INTT) wn = Pow(wn, Mod - 2);
        for(int j = 0; j < len; j += p){
            int w = 1;
            for(int k = 0; k < i; k++){
                int x = a[j + k], y = 1ll * w * a[i + j + k] % Mod;
                a[j + k] = (x + y) % Mod;
                a[i + j + k] = (x - y + Mod) % Mod;
                w = 1ll * w * wn % Mod;
            }
        }
    }
    if(INTT){
        int inv = Pow(len, Mod - 2);
        for(int i = 0; i < len; i++) a[i] = 1ll * a[i] * inv % Mod;
    }
}

int CompW;
struct CompMod{
    int r, i;
    CompMod(int _r=0, int _i=0): r(_r), i(_i){}
    friend CompMod operator * (const CompMod &a, const CompMod &b){
        return CompMod((1ll * a.r * b.r + 1ll * a.i * b.i % Mod * CompW) % Mod,
                       (1ll * a.r * b.i + 1ll * a.i * b.r) % Mod);
    }
    friend CompMod operator ^ (CompMod a, int b){
        CompMod ans(1, 0);
        for(; b; b >>= 1, a = a * a)
            if(b & 1) ans = ans * a;
        return ans;
    }
};

int sqrtMod(int n){
    if(n == 1) return 1;
    const int p = Mod; int a;
    if(Pow(n, (p - 1) / 2) == p-1) return -1;
    do{
        a = rnd() % p;
        CompW = (1ll * a * a - n + p) % p;
    } while(Pow(CompW, (p - 1) / 2) != p - 1);
    CompMod t = CompMod(a, 1) ^ ((p + 1) / 2);
    int x1 = t.r, x2 = p - x1;
    return min(x1, x2);
}

Polynomial::Polynomial(const int &_n){
    n = _n;
    a = new int[n + 1];
    memset(a, 0, sizeof(int) * (n + 1));
}

Polynomial::Polynomial(const int &_n, const int *p){
    n = _n;
    a = new int[n + 1];
    memcpy(a, p, sizeof(int) * (n + 1));
}

Polynomial::Polynomial(const Polynomial & rhs){
    n = rhs.n;
    a = new int[n + 1];
    memcpy(a, rhs.a, sizeof(int) * (n + 1));
}

Polynomial::~Polynomial(){
    delete[] a;
    n = 0;
}

Polynomial& Polynomial::resize(int _n){
    if(_n == n) return *this;
    else if(_n < n) n = _n;
    else {
        int *p = a;
        a = new int[_n + 1];
        memcpy(a, p, sizeof(int) * (n + 1));
        memset(a + n + 1, 0, sizeof(int) * (_n - n));
        n = _n;
        delete[] p;
    }
    return *this;
}

Polynomial& Polynomial::leftmove(int k){
    int *p = a;
    a = new int[n + k + 1];
    memset(a, 0, sizeof(int) * k);
    memcpy(a + k, p, sizeof(int) * (n + 1));
    delete[] p;
    n = n + k;
    return *this;
}

Polynomial& Polynomial::operator= (const Polynomial &rhs){
    n = rhs.n;
    a = new int[n + 1];
    memcpy(a, rhs.a, sizeof(int) * (n + 1));
    return *this;
}

Polynomial Polynomial::operator + (const Polynomial &rhs) const{
    Polynomial res(std::max(n, rhs.n));
    for(int i = 0; i <= n; i++)
        res[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++)
        res[i] = (res[i] + rhs[i]) % Mod;
    return res;
}

Polynomial Polynomial::operator - (const Polynomial &rhs) const{
    Polynomial res(std::max(n, rhs.n));
    for(int i = 0; i <= n; i++)
        res[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++)
        res[i] = (res[i] - rhs[i] + Mod) % Mod;
    return res;
}

Polynomial Polynomial::operator - () const{
    Polynomial res(n);
    for(int i = 0; i <= n; i++)
        res[i] = ((*this)[i] ? Mod - (*this)[i] : 0);
    return res;
}

Polynomial Polynomial::operator * (int k) const{
    Polynomial res = *this;
    for(int i = 0; i <= n; i++)
        res[i] = 1ll * k * res[i] % Mod;
    return res;
}

Polynomial Polynomial::operator * (const Polynomial &rhs) const{
    Polynomial res(n + rhs.n);
    if(res.n <= 5){
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= rhs.n; j++)
                res[i + j] = (res[i + j] + 1ll * a[i] * rhs[j]) % Mod;
        return res;
    }
    int len = 1;
    while(len <= n + rhs.n) len <<= 1;
    int *f = new int[len];
    int *g = new int[len];
    memset(f, 0, sizeof(int) * len);
    memset(g, 0, sizeof(int) * len);
    for(int i = 0; i <= n; i++) f[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++) g[i] = rhs[i];
    NTT(f, len, 0); NTT(g, len, 0);
    for(int i = 0; i < len; i++)
        f[i] = 1ll * f[i] * g[i] % Mod;
    NTT(f, len, 1);
    for(int i = 0; i <= n + rhs.n; i++)
        res[i] = f[i];
    delete[] f;
    delete[] g;
    return res;
}

int Polynomial::operator() (int x) const{
    int rx = 1, res = 0;
    for(int i = 0; i <= n; i++){
        res = (res + 1ll * a[i] * rx) % Mod;
        rx = 1ll * rx * x % Mod;
    }
    return res;
}

int& Polynomial::operator[] (int i){
    return a[i];
}

int Polynomial::operator[] (int i) const{
    return a[i];
}

Polynomial Polynomial::derivative() const{
    Polynomial res(n - 1);
    for(int i = 0; i < n; i++)
        res.a[i] = 1ll * a[i + 1] * (i + 1) % Mod;
    return res;
}

Polynomial Polynomial::integral() const{
    Polynomial res(n + 1);
    int *inv = new int[n + 1];
    inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (Mod - 1ll * (Mod / i) * inv[Mod % i] % Mod) % Mod;
    for(int i = 0; i <= n; i++)
        res.a[i + 1] = 1ll * a[i] * inv[i + 1] % Mod;
    return res;
}

Polynomial constPoly(int x = 0){
    Polynomial res(0);
    res[0] = x;
    return res;
}

Polynomial inv(const Polynomial &p, int n = -1){
    if(n == -1) n = p.n + 1;
    if(n == 1) return constPoly(Pow(p[0], Mod - 2));
    auto g0 = inv(p, (n + 1) >> 1);
    Polynomial f(n - 1, p.a);
    return (g0 * 2 - g0 * g0 * f).resize(n - 1);
}

Polynomial log(const Polynomial &p){
    assert(p[0] == 1);
    return (p.derivative() * inv(p)).integral().resize(p.n);
}

Polynomial exp(const Polynomial &p, int n = -1){
    assert(p[0] == 0);
    if(n == -1) n = p.n + 1;
    if(n == 1) return constPoly(1);
    auto g0 = exp(p, (n + 1) >> 1).resize(n - 1);
    Polynomial f(n - 1, p.a);
    return (g0 * (constPoly(1) - log(g0) + f)).resize(n - 1);
}

Polynomial sqrt(const Polynomial &p, int n = -1){
    if(n == -1) n = p.n + 1;
    if(n == 1) return constPoly(sqrtMod(p[0]));
    auto g0 = sqrt(p, (n + 1) >> 1).resize(n - 1);
    Polynomial f(n - 1, p.a);
    return (g0 + inv(g0) * f).resize(n - 1) * inv2;
}

Polynomial pow(Polynomial a, int kk, int b){
    if(a[0] == 1){
        return exp(log(a) * kk);
    } else if(a[0]){
        int a0 = a[0];
        a = a * Pow(a0, Mod - 2);
        a = pow(a, kk, b);
        return a * Pow(a0, b);
    } else {
        int t = 0;
        while(t <= a.n && a[t] == 0) t++;
        if(t > a.n) return a;
        Polynomial f(a.n - t, a.a + t);
        long long lmv = min(1ll * t * b, 1ll * a.n + 1);
        return pow(f, kk, b).leftmove(lmv).resize(a.n);
    }
}

Polynomial sin(const Polynomial &p){
    return (exp(p * unitImage) - exp(p * (Mod - unitImage)))
             * Pow(2 * unitImage % Mod, Mod - 2);
}

Polynomial cos(const Polynomial &p){
    return (exp(p * unitImage) + exp(p * (Mod - unitImage))) * inv2;
}

Polynomial tan(const Polynomial &p){
    return (sin(p) * inv(cos(p))).resize(p.n);
}

Polynomial asin(const Polynomial &p){
    return (p.derivative() * inv(sqrt(constPoly(1) - (p * p).resize(p.n))))
            .resize(p.n).integral().resize(p.n);
}

Polynomial acos(const Polynomial &p){
    return -asin(p);
}

Polynomial atan(const Polynomial &p){
    return (p.derivative() * inv(constPoly(1) + (p * p).resize(p.n)))
            .resize(p.n).integral().resize(p.n);
}