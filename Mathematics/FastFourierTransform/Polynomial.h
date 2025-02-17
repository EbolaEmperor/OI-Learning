#pragma once

#include <bits/stdc++.h>
using namespace std;

const int Mod = 998244353;

int Pow(int a, int b);
void NTT(int *a, int len, bool INTT);

class Polynomial{
private:
    int n;
    int *a;
    void resize(int _n);

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
    Polynomial operator * (const Polynomial &rhs) const;
    friend Polynomial pow(Polynomial lhs, int b);
    Polynomial derivative() const;
    Polynomial integral() const;

    friend Polynomial inv(const Polynomial &p, int deg);
    friend Polynomial log(const Polynomial &p);
    friend Polynomial exp(const Polynomial &p);
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

void Polynomial::resize(int _n){
    if(_n == n) return;
    else if(_n < n) n = _n;
    else {
        int *p = a;
        a = new int[_n + 1];
        memcpy(a, p, sizeof(int) * (n + 1));
        memset(a + n + 1, 0, sizeof(int) * (_n - n));
        delete[] p;
    }
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

Polynomial Polynomial::operator * (const Polynomial &rhs) const{
    Polynomial res(n + rhs.n);
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

Polynomial pow(Polynomial a, int b){
    Polynomial res(1);
    res[0] = 1;
    for(;b; b >>= 1, a = a * a)
        if(b & 1) res = res * a;
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

Polynomial inv(const Polynomial &p, int n = -1){
    if(n == -1) n = p.n + 1;
    if(n == 1){
        Polynomial res(0);
        res[0] = Pow(p[0], Mod - 2);
        return res;
    }
    auto b = inv(p, (n + 1) >> 1);
    int len = 1;
    while(len < n * 2) len <<= 1;
    int *c = new int[len];
    int *d = new int[len];
    memcpy(c, p.a, sizeof(int) * n);
    memset(c + n, 0, sizeof(int) * (len - n));
    memcpy(d, b.a, sizeof(int) * (b.n + 1));
    memset(d + b.n + 1, 0, sizeof(int) * (len - b.n - 1));
    NTT(c, len, 0); NTT(d, len, 0);
    for(int i = 0; i < len; i++)
        d[i] = 1ll * (2ll - 1ll * c[i] * d[i] % Mod + Mod) % Mod * d[i] % Mod;
    NTT(d, len, 1);
    Polynomial res(n - 1, d);
    delete[] c;
    delete[] d;
    return res;
}

Polynomial log(const Polynomial &p){
    auto h = (p.derivative() * inv(p)).integral();
    h.resize(p.n);
    return h;
}