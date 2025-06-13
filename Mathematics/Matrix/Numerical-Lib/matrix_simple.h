/***************************************************************
 *
 * 这是一个简化版本的矩阵运算库，不含任何数值算法
 * 
 * copyright © 2023 Wenchong Huang, All rights reserved.
 *
 **************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#include <iomanip>

typedef std::complex<double> Complex;

const double mat_eps = 1e-12;

class Matrix;
class ColVector;
class RowVector;

class Matrix{
protected:
    double *a;
public:
    int n, m;
    int nRows() const { return n; }
    int nCols() const { return m; }
    
    Matrix();
    Matrix(const int &_n);
    Matrix(const int &_n, const int &_m);
    Matrix(const Matrix &A);
    Matrix(const double *p, const int &_n);
    Matrix(const int &_n, const int &_m, const double *p);
    Matrix(const ColVector &v);
    Matrix(const RowVector &v);
    ~Matrix();
    bool empty() const;

    Matrix & operator = (const Matrix & rhs);
    Matrix & operator = (Matrix && rhs);

    const double operator () (const int &r, const int &c) const;
    double & operator () (const int &r, const int &c);
    const double* operator [] (const int &r) const{ return a + (r * m); }
    double* operator [] (const int &r){ return a + (r * m); }
    const double element(const int &r, const int &c) const;
    double & element(const int &r, const int &c);

    friend Matrix diag(const Matrix &A);

    void setSubmatrix(const int &r, const int &c, const Matrix &rhs);
    Matrix getSubmatrix(const int &r1, const int &r2, const int &c1, const int &c2) const;
    Matrix reshape(const int &_n, const int &_m) const;

    RowVector getRow(const int &r) const;
    ColVector getCol(const int &c) const;

    Matrix operator + (const double &x) const;
    Matrix operator - (const double &x) const;
    Matrix operator * (const double &x) const;
    friend Matrix operator * (const double &k, const Matrix &A);

    Matrix operator + (const Matrix &B) const;
    Matrix operator - () const;
    Matrix operator - (const Matrix &B) const;
    Matrix operator * (const Matrix &B) const;
    Matrix operator / (const double &p) const;
    Matrix T() const;

    double vecnorm(const double &p) const;
    double maxnorm() const;
    void swaprow(const int &r1, const int &r2);
    void swapcol(const int &r1, const int &r2);
};

class RowVector: public Matrix{
public:
    RowVector(): Matrix() {};
    RowVector(const int &n): Matrix(1,n) {};
    RowVector(const int &n, const double *p): Matrix(1,n,p) {};
    RowVector(const Matrix &rhs);
    int size() const;
    const double operator ()(const int &x) const;
    double & operator () (const int &x);
    RowVector operator + (const RowVector &rhs) const;
    RowVector operator - (const RowVector &rhs) const;
    RowVector operator - () const;
    ColVector T() const;
    const double operator [] (const int &r) const{ return a[r]; }
    double& operator [] (const int &r){ return a[r]; }
};

class ColVector: public Matrix{
public:
    ColVector(): Matrix() {};
    ColVector(const int &n): Matrix(n,1) {};
    ColVector(const int &n, const double *p): Matrix(n,1,p) {};
    ColVector(const Matrix &rhs);
    ColVector(const std::vector<double> &rhs);
    int size() const;
    void sort();
    const double operator ()(const int &x) const;
    double & operator () (const int &x);
    ColVector& operator += (const ColVector &rhs);
    ColVector& operator -= (const ColVector &rhs);
    ColVector& operator *= (const double k);
    ColVector operator + (const ColVector &rhs) const;
    ColVector operator - (const ColVector &rhs) const;
    ColVector operator - () const;
    RowVector T() const;
    const double operator [] (const int &r) const{ return a[r]; }
    double& operator [] (const int &r){ return a[r]; }
};

Matrix hilbert(const int &n);
Matrix zeros(const int &n, const int &m);
Matrix ones(const int &n, const int &m);
Matrix eye(const int &n);
double value(const Matrix &A);
ColVector zeroCol(const int &n);
RowVector zeroRow(const int &n);
int sgn(const double &x);

//----------------------Matrix相关函数---------------------------
Matrix operator * (const double &k, const Matrix &x);
Matrix abs(const Matrix &A);
Matrix log2(const Matrix &A);
double max(const Matrix &A);
double sum(const Matrix &A);
std::istream& operator >> (std::istream& in, Matrix &A);
std::ostream& operator << (std::ostream& out, const Matrix &A);
Matrix dotdiv(const Matrix &a, const Matrix &b);
Matrix mergeCol(const Matrix &A, const Matrix &B);
Matrix mergeRow(const Matrix &A, const Matrix &B);
Matrix min(const Matrix &A, const Matrix &B);
Matrix max(const Matrix &A, const Matrix &B);
double vecnorm(const Matrix &A, const double &p);
double vecnorm(const Matrix &A);
double maxnorm(const Matrix &A);
double relativeError(const Matrix &A, const Matrix &B);
Matrix randMatrix(const int &n, const int &m);
Matrix randInvertibleMatrix(const int &n);

//----------------------Row/ColVector相关函数----------------------
RowVector operator * (const double &k, const RowVector &x);
ColVector operator * (const double &k, const ColVector &x);
ColVector operator * (const Matrix &A, const ColVector &x);
RowVector operator * (const RowVector &x, const Matrix &A);
double operator * (const RowVector &r, const ColVector &c);

//----------------------基本算术扩展----------------------------
double fact(const int &n);
double sqr(const double &x);
double binom(const int &n, const int &k);







//---------------------- 实现 --------------------------

Matrix::Matrix(){
    n = m = 0;
    a = nullptr;
}
Matrix::Matrix(const int &_n){
    n = m = _n;
    a = new double[n*m];
    memset(a, 0, sizeof(double)*(n*m));
}
Matrix::Matrix(const int &_n, const int &_m){
    n = _n;
    m = _m;
    a = new double[n*m];
    memset(a, 0, sizeof(double)*(n*m));
}
Matrix::Matrix(const Matrix &A){
    n = A.n;
    m = A.m;
    a = new double[n*m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            element(i,j) = A(i,j);
}
Matrix::Matrix(const double *p, const int &_n){
    n = _n; m = 1;
    a = new double[n];
    for(int i = 0; i < n; i++)
        a[i] = p[i];
}
Matrix::Matrix(const int &_n, const int &_m, const double *p){
    n = _n; m = _m;
    a = new double[n*m];
    for(int i = 0; i < n*m; i++)
        a[i] = p[i];
}
Matrix::Matrix(const ColVector &v){
    n = v.size();
    m = 1;
    a = new double[n];
    for(int i = 0; i < n; i++)
        a[i] = v(i);
}
Matrix::Matrix(const RowVector &v){
    n = 1;
    m = v.size();
    a = new double[m];
    for(int i = 0; i < m; i++)
        a[i] = v(i);
}
Matrix::~Matrix(){
    delete [] a;
}
bool Matrix::empty() const{
    return n==0 || m==0;
}

ColVector::ColVector(const std::vector<double> &rhs){
    n = rhs.size();
    m = 1;
    a = new double[n];
    for(int i = 0; i < n; i++)
        a[i] = rhs[i];
}

Matrix & Matrix::operator = (const Matrix & rhs){
    if(n == rhs.n && m == rhs.m){
        std::memcpy(a, rhs.a, sizeof(double) * (n*m));
    } else {
        Matrix copy(rhs);
        std::swap(*this, copy);
    }
    return *this;
}
Matrix & Matrix::operator = (Matrix && rhs){
    std::swap(a, rhs.a);
    n = rhs.n;
    m = rhs.m;
    return *this;
}

const double Matrix::element(const int &r, const int &c) const{
    if(r<0 || r>=n || c<0 || c>=m){
        std::cerr << "[Error] Matrix:: out of range" << std::endl;
        exit(-1);
    }
    return a[r*m+c];
}
double & Matrix::element(const int &r, const int &c){
    if(r<0 || r>=n || c<0 || c>=m){
        std::cerr << "[Error] Matrix:: out of range" << std::endl;
        exit(-1);
    }
    return a[r*m+c];
}
const double Matrix::operator () (const int &r, const int &c) const{
    return element(r, c);
}
double & Matrix::operator () (const int &r, const int &c){
    return element(r, c);
}

Matrix diag(const Matrix &A){
    if(A.n==1 && A.m>0){
        Matrix D(A.m, A.m);
        for(int i = 0; i < A.m; i++)
            D(i, i) = A(0, i);
        return D;
    } else if(A.m==1 && A.n>0){
        Matrix D(A.n, A.n);
        for(int i = 0; i < A.n; i++)
            D(i, i) = A(i, 0);
        return D;
    } else {
        int n = std::min(A.n,A.m);
        Matrix D(n,1);
        for(int i = 0; i < n; i++)
            D(i, 0) = A(i, i);
        return D;
    }
}

// 将矩阵以第r行第c列为左上角的子矩阵设为rhs
void Matrix::setSubmatrix(const int &r, const int &c, const Matrix &rhs){
    if(r<0 || c<0 || r+rhs.n>n || c+rhs.m>m){
        std::cerr << "Matrix Error! setSubmatrix::: out of range!" << std::endl;
        exit(-1);
    }
    for(int i = 0; i < rhs.n; i++)
        for(int j = 0; j < rhs.m; j++)
            element(r+i, j+c) = rhs(i, j);
}

Matrix Matrix::getSubmatrix(const int &r1, const int &r2, const int &c1, const int &c2) const{
    if(r1<0 || c1<0 || r2>=n || c2>=m || r2<r1 || c2<c1){
        std::cerr << "Matrix Error! getSubmatrix::: out of range!" << std::endl;
        exit(-1);
    }
    Matrix sub(r2-r1+1, c2-c1+1);
    for(int i = 0; i < r2-r1+1; i++)
        for(int j = 0; j < c2-c1+1; j++)
            sub(i, j) = element(r1+i, c1+j);
    return sub;
}

Matrix Matrix::reshape(const int &_n, const int &_m) const{
    if(_n*_m != n*m){
        std::cerr << "Matrix Error! Reshape should keep the size!" << std::endl;
        exit(-1);
    }
    Matrix rhs = *this;
    rhs.n = _n;
    rhs.m = _m;
    return rhs;
}

RowVector Matrix::getRow(const int &r) const{
    RowVector res(m);
    for(int i = 0; i < m; i++)
        res(i) = element(r,i);
    return res;
}

ColVector Matrix::getCol(const int &c) const{
    ColVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = element(i,c);
    return res;
}

Matrix Matrix::operator + (const double &x) const {
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i,j) + x;
    return C;
}

Matrix Matrix::operator * (const double &x) const {
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i,j) * x;
    return C;
}

Matrix operator * (const double &k, const Matrix &A) {
    return A * k;
}

Matrix Matrix::operator - (const double &x) const {
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i,j) - x;
    return C;
}

Matrix Matrix::operator + (const Matrix &B) const {
    if(n!=B.n || m!=B.m){
        std::cerr << "Matrix Error! Undefined Addition!" << std::endl;
        exit(-1);
    }
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i,j) + B(i, j);
    return C;
}

Matrix Matrix::operator - () const {
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = -element(i,j);
    return C;
}

Matrix Matrix::operator - (const Matrix &B) const {
    if(n!=B.n || m!=B.m){
        std::cerr << "Matrix Error! Undefined Subtraction!" << std::endl;
        exit(-1);
    }
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i,j) - B(i, j);
    return C;
}

Matrix Matrix::operator / (const double &k) const {
    Matrix C(n, m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = element(i, j) / k;
    return C;
}

Matrix Matrix::operator * (const Matrix &B) const{
    if(m!=B.n){
        std::cerr << "Matrix Error! Undefined multiplication! (" << n << "*" << m << ") * (" << B.n << "*" << B.m << ")" << std::endl;
        exit(-1);
    }
    Matrix C(n, B.m);
    for(int i = 0; i < C.n; i++)
        for(int k = 0; k < m; k++){
            double tmp = a[i * m + k];
            if(!tmp) continue;
            for(int j = 0; j < C.m; j++)
                C(i, j) += tmp * B(k, j);
        }
    return C;
}

Matrix Matrix::T() const{
    Matrix C(m, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            C(j, i) = element(i,j);
    return C;
}

double Matrix::maxnorm() const{
    double norm = 0;
    for(int i = 0; i < n*m; i++)
        norm = std::max(norm, fabs(a[i]));
    return norm;
}

double maxnorm(const Matrix &A){
    return A.maxnorm();
}

double Matrix::vecnorm(const double &p) const{
    double norm = 0;
    for(int i = 0; i < n*m; i++)
        norm += pow(a[i], p);
    return pow(norm, 1.0/p);
}

double vecnorm(const Matrix &A, const double &p){
    return A.vecnorm(p);
}

double vecnorm(const Matrix &A){
    return A.vecnorm(2);
}

// 将矩阵中所有元素取绝对值后返回，用法：B=abs(A)
Matrix abs(const Matrix &A){
    Matrix C = A;
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++)
            C(i, j) = std::fabs(A(i, j));
    return C;
}

// 矩阵求最大值函数，返回矩阵中的最大元素，用法：x=max(A)
double max(const Matrix &A){
    if(A.m==0 || A.n==0) return 0;
    double res = A(0, 0);
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++)
            res = std::max(res, A(i, j));
    return res;
}

// 矩阵求最小值函数，返回矩阵中的最大元素，用法：x=min(A)
double min(const Matrix &A){
    if(A.m==0 || A.n==0) return 0;
    double res = A(0, 0);
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++)
            res = std::min(res, A(i, j));
    return res;
}

// 矩阵求和函数，返回所有元素的和，用法：s=sum(A)
double sum(const Matrix &A){
    double res = 0;
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++)
            res += A(i, j);
    return res;
}

std::istream& operator >> (std::istream& in, Matrix &A){
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++)
            in >> A(i, j);
    return in;
}

std::ostream& operator << (std::ostream& out, const Matrix &A){
    out << std::setprecision(14);
    for(int i = 0; i < A.n; i++)
    {
        out << "[ " << A(i, 0);
        for(int j = 1; j < A.m; j++)
            out << ", " << A(i, j);
        out << " ]";
        if(i < A.n - 1) out << "\n";
    }
    return out;
}

void Matrix::swaprow(const int &r1, const int &r2){
    if(r1<0 || r1>=n || r2<0 || r2>=n){
        std::cerr << "Matrix Error! Swaprow out of range!" << std::endl;
        exit(-1);
    }
    for(int j = 0; j < m; j++)
        std::swap(a[r1*m+j], a[r2*m+j]);
}

void Matrix::swapcol(const int &r1, const int &r2){
    if(r1<0 || r1>=m || r2<0 || r2>=m){
        std::cerr << "Matrix Error! Swapcol out of range!" << std::endl;
        exit(-1);
    }
    for(int i = 0; i < n; i++)
        std::swap(a[i*m+r1], a[i*m+r2]);
}

// 向量对应元素相除除，用法：x = dotdiv(a,b)
Matrix dotdiv(const Matrix &a, const Matrix &b){
    Matrix x = a;
    for(int i = 0; i < a.n; i++)
        for(int j = 0; j < a.m; j++)
            x(i, j) /= b(i, j);
    return x;
}

Matrix mergeCol(const Matrix &A, const Matrix &B){
    if(A.m == 0) return B;
    if(B.m == 0) return A;
    if(A.n != B.n){
        std::cerr << "Cannot merge Matrices in column with different row size!" << std::endl;
        return Matrix();
    }
    Matrix C(A.n, A.m+B.m);
    C.setSubmatrix(0,0,A);
    C.setSubmatrix(0,A.m,B);
    return C;
}

Matrix mergeRow(const Matrix &A, const Matrix &B){
    if(A.n == 0) return B;
    if(B.n == 0) return A;
    if(A.m != B.m){
        std::cerr << "Cannot merge Matrices in row with different column size!" << std::endl;
        return Matrix();
    }
    Matrix C(A.n+B.n, A.m);
    C.setSubmatrix(0,0,A);
    C.setSubmatrix(A.n,0,B);
    return C;
}

Matrix log2(const Matrix &A) {
    Matrix res(A.n,A.m);
    for(int i = 0; i < res.n; i++)
        for(int j = 0; j < res.m; j++)
            res(i,j) = log2(A(i,j));
    return res;
}

// 返回一个矩阵C，使得C(i,j)=min(A(i,j),B(i,j))
Matrix min(const Matrix &A, const Matrix &B){
    if(A.n!=B.n || A.m!=B.m){
        std::cerr << "Cannot use min in two matrices of different size." << std::endl;
        return Matrix();
    }
    Matrix C(A.n,A.m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = std::min(A(i, j),B(i, j));
    return C;
}

// 返回一个矩阵C，使得C(i,j)=max(A(i,j),B(i,j))
Matrix max(const Matrix &A, const Matrix &B){
    if(A.n!=B.n || A.m!=B.m){
        std::cerr << "Cannot use max in two matrices of different size." << std::endl;
        return Matrix();
    }
    Matrix C(A.n,A.m);
    for(int i = 0; i < C.n; i++)
        for(int j = 0; j < C.m; j++)
            C(i, j) = std::max(A(i, j),B(i, j));
    return C;
}

//----------------------ColVector相关函数---------------------------

ColVector::ColVector(const Matrix &rhs){
    if(rhs.m != 1){
        std::cerr << "Error! Cannot convert a non sigle-column matrix into ColVector!" << std::endl;
        (*this) = ColVector();
    } else {
        (*this) = ColVector(rhs.n);
        for(int i = 0; i < n; i++)
            (*this)(i) = rhs(i, 0);
    }
}

const double ColVector::operator ()(const int &x) const{
    return element(x,0);
}
    
double & ColVector::operator () (const int &x){
    return element(x,0);
}

int ColVector::size() const{
    return n;
}

ColVector& ColVector::operator += (const ColVector &rhs){
    if(n != rhs.n){
        std::cerr << "ColVector Addition Error!" << std::endl;
    }
    for(int i = 0; i < n; i++)
        a[i] += rhs.a[i];
    return *this;
}

ColVector& ColVector::operator -= (const ColVector &rhs){
    if(n != rhs.n){
        std::cerr << "ColVector Addition Error!" << std::endl;
    }
    for(int i = 0; i < n; i++)
        a[i] -= rhs.a[i];
    return *this;
}

ColVector& ColVector::operator *= (const double k){
    for(int i = 0; i < n; i++)
        a[i] *= k;
    return *this;
}

ColVector ColVector::operator + (const ColVector &rhs) const{
    if(n!=rhs.n){
        std::cerr << "ColVector Addition Error!" << std::endl;
        return ColVector();
    }
    ColVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = (*this)(i) + rhs(i);
    return res;
}

ColVector ColVector::operator - (const ColVector &rhs) const{
    if(n!=rhs.n){
        std::cerr << "ColVector Addition Error!" << std::endl;
        return ColVector();
    }
    ColVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = (*this)(i) - rhs(i);
    return res;
}

ColVector ColVector::operator - () const{
    ColVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = -(*this)(i);
    return res;
}

ColVector operator * (const Matrix &A, const ColVector &x){
    if(A.m!=x.n){
        std::cerr << "ColVector Multiplication Error!" << std::endl;
        return ColVector();
    }
    ColVector res(A.n);
    for(int i = 0; i < res.n; i++)
        for(int j = 0; j < A.m; j++)
            res(i) += A(i, j) * x(j);
    return res;
}

void ColVector::sort(){
    std::sort(a, a+n);
}

ColVector operator * (const double &k, const ColVector &x){
    ColVector res(x.n);
    for(int i = 0; i < res.n; i++)
        res(i) = k * x(i);
    return res;
}

RowVector ColVector::T() const{
    RowVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = (*this)(i);
    return res;
}


//----------------------RowVector相关函数---------------------------

RowVector::RowVector(const Matrix &rhs){
    if(rhs.n != 1){
        std::cerr << "Error! Cannot convert a non sigle-row matrix into RowVector!" << std::endl;
        (*this) = RowVector();
    } else {
        (*this) = RowVector(rhs.m);
        for(int i = 0; i < m; i++)
            (*this)(i) = rhs(0, i);
    }
}

const double RowVector::operator ()(const int &x) const{
    return element(0,x);
}

double & RowVector::operator () (const int &x){
    return element(0,x);
}

int RowVector::size() const{
    return m;
}

RowVector operator * (const RowVector &x, const Matrix &A){
    if(A.n!=x.m){
        std::cerr << "RowVector Multiplication Error!" << std::endl;
        return RowVector();
    }
    RowVector res(A.m);
    for(int i = 0; i < res.m; i++)
        for(int j = 0; j < A.n; j++)
            res(i) += A(j, i) * x(j);
    return res;
}

double operator * (const RowVector &r, const ColVector &c){
    if(r.m!=c.n){
        std::cerr << "RowVector and ColVector Multiplication Error!" << std::endl;
        return 0;
    }
    return value((Matrix)r*c);
}

RowVector RowVector::operator + (const RowVector &rhs) const{
    if(m!=rhs.m){
        std::cerr << "RowVector Addition Error!" << std::endl;
        return RowVector();
    }
    RowVector res(m);
    for(int i = 0; i < m; i++)
        res(i) = (*this)(i) + rhs(i);
    return res;
}

RowVector RowVector::operator - (const RowVector &rhs) const{
    if(m!=rhs.m){
        std::cerr << "RowVector Addition Error!" << std::endl;
        return RowVector();
    }
    RowVector res(m);
    for(int i = 0; i < m; i++)
        res(i) = (*this)(i) - rhs(i);
    return res;
}

RowVector RowVector::operator - () const{
    RowVector res(m);
    for(int i = 0; i < m; i++)
        res(i) = -(*this)(i);
    return res;
}

RowVector operator * (const double &k, const RowVector &x){
    RowVector res(x.m);
    for(int i = 0; i < res.m; i++)
        res(i) = k * x(i);
    return res;
}

ColVector RowVector::T() const{
    ColVector res(n);
    for(int i = 0; i < n; i++)
        res(i) = (*this)(i);
    return res;
}

Matrix hilbert(const int &n){
    Matrix H(n, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            H(i, j) = 1.0/(i+j+1);
    return H;
}

Matrix zeros(const int &n, const int &m){
    return Matrix(n, m);
}

Matrix ones(const int &n, const int &m){
    Matrix H(n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            H(i, j) = 1.0;
    return H;
}

Matrix eye(const int &n){
    Matrix H(n, n);
    for(int i = 0; i < n; i++)
        H(i, i) = 1.0;
    return H;
}

double value(const Matrix &A){
    return A(0, 0);
}

ColVector zeroCol(const int &n){
    return ColVector(n);
}

RowVector zeroRow(const int &n){
    return RowVector(n);
}

int sgn(const double &x){
    if(x>0) return 1;
    else if(x<0) return -1;
    else return 0;
}

double sqr(const double &x){
    return x*x;
}

double fact(const int &n){
    double ans = 1;
    for(int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}

double binom(const int &n, const int &k){
    return fact(n)/(fact(k)*fact(n-k));
}

double relativeError(const Matrix &A, const Matrix &B){
    double err = 0;
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m; j++){
            err = std::max(err, fabs(A(i,j)-B(i,j)) / std::max(std::max( fabs(A(i,j)), fabs(B(i,j)) ), 1.0) );
        }
    return err;
}

double dot(const ColVector &a, const ColVector &b){
    if(a.size() != b.size()){
        std::cerr << "ColVector dot product Error! Size mismatch." << std::endl;
        return 0;
    }
    double res = 0;
    for(int i = 0; i < a.size(); i++)
        res += a(i) * b(i);
    return res;
}

#endif