/***************************************************************
 *
 * 这是一个利用高精度分数运算实现的精确矩阵运算库
 * 运算效率较低，但能保证绝对精确的运算，可用于理论研究
 * 依赖于：fraction.h, bigint.h
 * 
 * copyright © 2022 Wenchong Huang, All rights reserved.
 *
 **************************************************************/

#ifndef _MATRIX_FRACTION_H_
#define _MATRIX_FRACTION_H_

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <tuple>
#include "fraction.h"

class fracMatrix{
private:
    std::vector<fraction> a;
public:
    int n, m;
    fracMatrix(){
        n = m = 0;
        a.clear();
    }
    fracMatrix(const int &_n, const int &_m){
        n = _n;
        m = _m;
        a.resize(n*m);
        for(int i = 0; i < n*m; i++)
            a[i] = fraction(0,1);
    }
    fracMatrix(const int &_n, const int &_m, const std::vector<fraction> &val){
        n = _n;
        m = _m;
        a = val;
    }
    fracMatrix(const fracMatrix &A){
        n = A.n;
        m = A.m;
        a.resize(n*m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                a[i*m+j] = A.element(i,j);
    }
    ~fracMatrix(){
        a.clear();
    }

    bool iszero() const{
        for(int i = 0; i < n*m; i++)
            if(a[i]!=fraction(0,1)) return false;
        return true; 
    }
    fracMatrix & operator = (const fracMatrix & rhs){
        fracMatrix copy(rhs);
        std::swap(*this, copy);
        return *this;
    }
    fracMatrix & operator = (fracMatrix && rhs){
        std::swap(a, rhs.a);
        n = rhs.n;
        m = rhs.m;
        return *this;
    }

    // 矩阵基本运算
    fraction & element(const int &i, const int &j){
        return a[i*m+j];
    }
    const fraction & element(const int &i, const int &j) const{
        return a[i*m+j];
    }

    fraction & operator() (const int &i, const int &j){
        return a[i*m+j];
    }

    const fraction & operator() (const int &i, const int &j) const{
        return a[i*m+j];
    }

    fracMatrix operator + (const fracMatrix &B) {
        if(n!=B.n || m!=B.m){
            std::cerr << "fracMatrix Error! Undefined Addition!" << std::endl;
            exit(-1);
        }
        fracMatrix C(n, m);
        for(int i = 0; i < C.n; i++)
            for(int j = 0; j < C.m; j++)
                C.element(i,j) = a[i*m+j] + B.element(i,j);
        return C;
    }

    fracMatrix operator - () {
        fracMatrix C(n, m);
        for(int i = 0; i < C.n; i++)
            for(int j = 0; j < C.m; j++)
                C.element(i,j) = -a[i*m+j];
        return C;
    }

    fracMatrix operator - (const fracMatrix &B) {
        if(n!=B.n || m!=B.m){
            std::cerr << "fracMatrix Error! Undefined Subtraction!" << std::endl;
            exit(-1);
        }
        fracMatrix C(n, m);
        for(int i = 0; i < C.n; i++)
            for(int j = 0; j < C.m; j++)
                C.element(i,j) = a[i*m+j] - B.element(i,j);
        return C;
    }

    friend fracMatrix operator * (const fraction &k, const fracMatrix &A) {
        fracMatrix C(A.n, A.m);
        for(int i = 0; i < C.n; i++)
            for(int j = 0; j < C.m; j++)
                C.element(i,j) = k * A.element(i,j);
        return C;
    }

    fracMatrix operator * (const fracMatrix &B) const{
        if(m!=B.n){
            std::cerr << "fracMatrix Error! Undefined multiplication!" << std::endl;
            exit(-1);
        }
        fracMatrix C(n, B.m);
        for(int i = 0; i < C.n; i++)
            for(int j = 0; j < C.m; j++)
                for(int k = 0; k < m; k++)
                    C.element(i,j) += a[i*m+k] * B.element(k,j);
        return C;
    }

    fracMatrix T(){
        fracMatrix C(m, n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                C.element(j,i) = a[i*m+j];
        return C;
    }

    double vecnorm(const double &p){
        double norm = 0;
        for(int i = 0; i < n*m; i++)
            norm += pow(a[i].to_double(), p);
        return pow(norm, 1.0/p);
    }

    friend std::ostream& operator << (std::ostream& out, const fracMatrix &A){
        for(int i = 0; i < A.n; i++)
        {
            out << "[ " << A.element(i,0);
            for(int j = 1; j < A.m; j++)
                out << ", " << A.element(i,j);
            out << " ]" << std::endl;
        }
        return out;
    }

    void swaprow(const int &r1, const int &r2){
        if(r1<0 || r1>=n || r2<0 || r2>=n){
            std::cerr << "fracMatrix Error! Swaprow ouof range!" << std::endl;
            exit(-1);
        }
        for(int j = 0; j < m; j++)
            std::swap(a[r1*m+j], a[r2*m+j]);
    }

    void swapcol(const int &r1, const int &r2){
        if(r1<0 || r1>=m || r2<0 || r2>=m){
            std::cerr << "fracMatrix Error! Swapcol ouof range!" << std::endl;
            exit(-1);
        }
        for(int i = 0; i < n; i++)
            std::swap(a[i*m+r1], a[i*m+r2]);
    }

    fraction sum() const{
        fraction s = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                s += element(i,j);
        return s;
    }

    // 矩阵常用算法
    friend fracMatrix solve(fracMatrix A, fracMatrix b){
        if(A.m!=A.n || A.n!=b.n || A.m==0){
            std::cerr << "fracMatrix Error! The method solve() cannot solve an ill-posed equation!" << std::endl;
            return fracMatrix();
        }
        int n = A.n;
        fracMatrix x(n,1);
        for(int i = 0; i < n; i++){
            int p = i;
            while(p<n && A.element(p,i)==0) p++;
            if(p==n){
                std::cerr << "fracMatrix Error! The method solve() cannot solve an singular equation!" << std::endl;
                return fracMatrix();
            }
            if(p!=i) A.swaprow(i,p);
            for(int j = 0; j < n; j++){
                if(i==j) continue;
                fraction coef = A.element(j,i)/A.element(i,i);
                for(int k = i; k < n; k++)
                    A.element(j,k) -= A.element(i,k)*coef;
                b.element(j,0) -= b.element(i,0)*coef;
            }
        }
        for(int i = 0; i < n; i++)
            x.element(i,0) = b.element(i,0)/A.element(i,i);
        return x;
    }

    fracMatrix inverse(){
        if(m!=n || m==0){
            std::cerr << "fracMatrix Error! There's no inverse of a non-square or empty matrix!" << std::endl;
            return fracMatrix();
        }
        fracMatrix A(n,2*n);
        for(int i = 0; i < n; i++)
        {
            A.element(i,i+n) = 1;
            for(int j = 0; j < n; j++)
                A.element(i,j) = element(i,j);
        }
        for(int i = 0; i < n; i++){
            int p = i;
            while(p<n && A.element(p,i)==0) p++;
            if(p==n){
                std::cerr << "fracMatrix Error! There's no inverse of a singular matrix!" << std::endl;
                return fracMatrix();
            }
            if(p!=i) A.swaprow(i,p);
            for(int k = i+1; k < 2*n; k++)
                A.element(i,k) /= A.element(i,i);
            A.element(i,i) = 1;
            for(int j = 0; j < n; j++){
                if(i==j) continue;
                fraction coef = A.element(j,i);
                for(int k = i; k < 2*n; k++)
                    A.element(j,k) -= A.element(i,k)*coef;
            }
        }
        fracMatrix ans(n,n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                ans.element(i,j) = A.element(i,j+n);
        return ans;
    }

    fraction det(){
        if(m!=n || m==0){
            std::cerr << "fracMatrix Error! Cannot calculate the determinate of a non-square or empty matrix!" << std::endl;
            return 0;
        }
        fracMatrix A(*this);
        fraction ans = 1;
        for(int i = 0; i < n; i++){
            int p = i;
            while(p<n && A.element(p,i)==0) p++;
            if(p==n) return 0;
            if(p!=i) A.swaprow(i,p);
            ans *= A.element(i,i);
            for(int j = i+1; j < n; j++){
                fraction coef = A.element(j,i)/A.element(i,i);
                for(int k = i; k < n; k++)
                    A.element(j,k) -= A.element(i,k)*coef;
            }
        }
        return ans;
    }
};

fracMatrix hilbert(const int &n){
    fracMatrix H(n, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            H.element(i,j) = fraction(1, i+j+1);
    return H;
}

fracMatrix zeros(const int &n, const int &m){
    return fracMatrix(n, m);
}

fracMatrix ones(const int &n, const int &m){
    fracMatrix H(n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            H.element(i,j) = 1;
    return H;
}

fracMatrix eye(const int &n){
    fracMatrix H(n, n);
    for(int i = 0; i < n; i++)
        H.element(i,i) = 1;
    return H;
}

fraction value(const fracMatrix &A){
    return A.element(0,0);
}

std::tuple<fracMatrix, fracMatrix, fracMatrix> LU(fracMatrix A) {
    int n = A.n, m = A.m;
    std::vector<int> P(n);
    for (int i = 0; i < n; ++i) P[i] = i;
    fracMatrix L = (n >= m) ? zeros(n, m) : zeros(n, n);
    fracMatrix U = (n >= m) ? zeros(m, m) : zeros(n, m);
    int mm = std::min(n, m);
    for (int i = 0; i < mm; ++i) L(i, i) = 1.0;
    for (int k = 0; k < mm; ++k) {
        if (A(k,k) == 0) {
            int pivot = k;
            while(pivot < n && A(pivot, k) == 0) pivot++;
            if (pivot == n) {
                std::cerr << "[fracMatrix] LU:: cannot decompose a singular matrix as LU." << std::endl;
                return std::make_tuple(fracMatrix(), fracMatrix(), fracMatrix());
            }
            std::swap(P[k], P[pivot]);
            for (int j = 0; j < m; ++j) std::swap(A(k, j), A(pivot, j));
            for (int j = 0; j < k; ++j) std::swap(L(k, j), L(pivot, j));
        }
        for (int j = k; j < m; ++j) U(k, j) = A(k, j);
        for (int i = k + 1; i < n; ++i) {
            L(i, k) = A(i, k) / U(k, k);
            for (int j = k + 1; j < m; ++j) {
                A(i, j) -= L(i, k) * U(k, j);
            }
            A(i, k) = 0;
        }
    }
    fracMatrix Pmat(n, n);
    for (int i = 0; i < n; ++i) Pmat(P[i], i) = 1;
    return std::make_tuple(Pmat, L, U);
}

#endif