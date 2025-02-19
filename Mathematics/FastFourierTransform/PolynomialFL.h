#pragma once

#include <bits/stdc++.h>
#define Comp complex<double>
using namespace std;

void FFT(Comp *a, int len, int v);

class Polynomial{
private:
    int n;
    double *a;

public:
    Polynomial(): n(-1), a(nullptr){}
    Polynomial(const int &_n);
    Polynomial(const int &_n, const double *p);
    Polynomial(const Polynomial &rhs);
    ~Polynomial();

    Polynomial& resize(int _n);
    Polynomial& leftmove(int k);
    Polynomial& reverse();

    double operator () (double x) const;
    double operator [] (int i) const;
    double& operator [] (int i);

    Polynomial& operator = (const Polynomial &rhs);
    Polynomial operator + (const Polynomial &rhs) const;
    Polynomial operator - (const Polynomial &rhs) const;
    Polynomial operator - () const;
    Polynomial operator * (double k) const;
    Polynomial operator * (const Polynomial &rhs) const;
    Polynomial derivative() const;
    Polynomial integral() const;
};





//---------------------------------- Implemention ----------------------------------

void FFT(Comp *a, int len, int v){
    int *r = new int[len];
    r[0] = 0;
    int l = -1;
    for(int x = len; x; x >>= 1) ++l;
    for(int i = 1; i < len; i++) r[i] = (r[i / 2] / 2) | ((i & 1) << (l - 1));
    for(int i = 0; i < len; i++) if(i < r[i]) swap(a[i], a[r[i]]);
    delete[] r;
    for(int i = 1; i < len; i <<= 1){
        int p = (i << 1);
        Comp wn(cos(M_PI / i), v * sin(M_PI / i));
        for(int j = 0; j < len; j += p){
            Comp w = 1;
            for(int k = 0; k < i; k++){
                Comp x = a[j + k], y = w * a[i + j + k];
                a[j + k] = x + y;
                a[i + j + k] = x - y;
                w *= wn;
            }
        }
    }
    if(v == -1)
        for(int i = 0; i < len; i++) a[i] = a[i] / (double)len;
}

Polynomial::Polynomial(const int &_n){
    n = _n;
    a = new double[n + 1];
    memset(a, 0, sizeof(double) * (n + 1));
}

Polynomial::Polynomial(const int &_n, const double *p){
    n = _n;
    a = new double[n + 1];
    memcpy(a, p, sizeof(double) * (n + 1));
}

Polynomial::Polynomial(const Polynomial & rhs){
    n = rhs.n;
    a = new double[n + 1];
    memcpy(a, rhs.a, sizeof(double) * (n + 1));
}

Polynomial::~Polynomial(){
    delete[] a;
    n = 0;
}

Polynomial& Polynomial::resize(int _n){
    if(_n == n) return *this;
    else if(_n < n) n = _n;
    else {
        double *p = a;
        a = new double[_n + 1];
        memcpy(a, p, sizeof(double) * (n + 1));
        memset(a + n + 1, 0, sizeof(double) * (_n - n));
        n = _n;
        delete[] p;
    }
    return *this;
}

Polynomial& Polynomial::leftmove(int k){
    double *p = a;
    a = new double[n + k + 1];
    memset(a, 0, sizeof(double) * k);
    memcpy(a + k, p, sizeof(double) * (n + 1));
    delete[] p;
    n = n + k;
    return *this;
}

Polynomial& Polynomial::operator= (const Polynomial &rhs){
    n = rhs.n;
    a = new double[n + 1];
    memcpy(a, rhs.a, sizeof(double) * (n + 1));
    return *this;
}

Polynomial Polynomial::operator + (const Polynomial &rhs) const{
    Polynomial res(std::max(n, rhs.n));
    for(int i = 0; i <= n; i++)
        res[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++)
        res[i] += rhs[i];
    return res;
}

Polynomial Polynomial::operator - (const Polynomial &rhs) const{
    Polynomial res(std::max(n, rhs.n));
    for(int i = 0; i <= n; i++)
        res[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++)
        res[i] -= rhs[i];
    return res;
}

Polynomial Polynomial::operator - () const{
    Polynomial res(n);
    for(int i = 0; i <= n; i++)
        res[i] = -(*this)[i];
    return res;
}

Polynomial Polynomial::operator * (double k) const{
    Polynomial res = *this;
    for(int i = 0; i <= n; i++)
        res[i] = k * res[i];
    return res;
}

Polynomial Polynomial::operator * (const Polynomial &rhs) const{
    Polynomial res(n + rhs.n);
    if(res.n <= 5){
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= rhs.n; j++)
                res[i + j] += a[i] * rhs[j];
        return res;
    }
    int len = 1;
    while(len <= n + rhs.n) len <<= 1;
    auto f = new Comp[len];
    auto g = new Comp[len];
    memset(f, 0, sizeof(Comp) * len);
    memset(g, 0, sizeof(Comp) * len);
    for(int i = 0; i <= n; i++) f[i] = (*this)[i];
    for(int i = 0; i <= rhs.n; i++) g[i] = rhs[i];
    FFT(f, len, 1); FFT(g, len, 1);
    for(int i = 0; i < len; i++) f[i] *= g[i];
    FFT(f, len, -1);
    for(int i = 0; i <= n + rhs.n; i++)
        res[i] = f[i].real();
    delete[] f;
    delete[] g;
    return res;
}

double Polynomial::operator() (double x) const{
    double rx = 1, res = 0;
    for(int i = 0; i <= n; i++){
        res += a[i] * rx;
        rx *= x;
    }
    return res;
}

double& Polynomial::operator[] (int i){
    return a[i];
}

double Polynomial::operator[] (int i) const{
    return a[i];
}

Polynomial Polynomial::derivative() const{
    Polynomial res(n - 1);
    for(int i = 0; i < n; i++)
        res.a[i] = a[i + 1] * (i + 1);
    return res;
}

Polynomial Polynomial::integral() const{
    Polynomial res(n + 1);
    for(int i = 0; i <= n; i++)
        res.a[i + 1] = a[i] / (i + 1);
    return res;
}

Polynomial constPoly(double x = 0){
    Polynomial res(0);
    res[0] = x;
    return res;
}

Polynomial& Polynomial::reverse(){
    std::reverse(a, a + n + 1);
    return *this;
}