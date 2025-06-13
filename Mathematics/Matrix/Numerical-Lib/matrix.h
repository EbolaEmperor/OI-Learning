/***************************************************************
 *
 * 这是一个矩阵运算库，为了方便以后设计算法更加简洁，特编写以用
 * 版本号：v1.5.1
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

    friend Matrix solve(Matrix A, Matrix b);
    ColVector solve(const ColVector &b) const;
    double det() const;
    Matrix inv() const;
    Matrix rref() const;
    void FGdecompose(Matrix &F, Matrix &G) const;
    Matrix pinv() const;
    double sqrsum() const;
    void setdiag(const ColVector &d);
    std::tuple<Matrix, Matrix, Matrix> PLU() const;

public:
    std::tuple<Matrix, Matrix, Matrix> svd() const;
    std::vector<Complex> eigen() const;
    std::pair<Matrix,Matrix> getQR() const;
private:
    ColVector getEigenVector(double lambda) const;
    Matrix realSchur() const;
    std::pair<Matrix,Matrix> hessenberg() const;
    std::pair<ColVector,double> householder() const;
    std::pair<Matrix,Matrix> doubleQR() const;
    bool isComplexEigen() const;
    std::pair<Complex,Complex> getComplexEigen() const;
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
Matrix solveLowerTriangular(const Matrix &A, const Matrix &b, int bandwidth = -1);
Matrix solveUpperTriangular(const Matrix &A, const Matrix &b, int bandwidth = -1);
ColVector CG_solve(const Matrix &A, const ColVector &b);
ColVector CG_solve(const Matrix &A, const ColVector &b, const double err);
ColVector CG_solve(const Matrix &A, const ColVector &b, const double err, ColVector x);
double det(const Matrix &A);
Matrix inv(const Matrix &A);
Matrix choleskyImproved(const Matrix &A);
Matrix solveByLDL(const Matrix &A, const Matrix &b);
Matrix gillMurray(Matrix A);
Matrix solveByLDL_GM(const Matrix &A, const Matrix &b);
Matrix pinv(const Matrix &A);
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

// 解下三角方程，用法：x = solveLowerTriangular(A,b)
Matrix solveLowerTriangular(const Matrix &A, const Matrix &b, int bandwidth){
    Matrix x = b;
    int n = A.n;
    for(int i = 0; i < n; i++){
        x(i, 0) /= A(i, i);
        if(bandwidth == -1){
            for(int j = i + 1; j < n; j++)
                x(j, 0) -= x(i, 0) * A(j, i);
        } else {
            for(int j = i + 1; j < n && j <= i + bandwidth; j++)
                x(j, 0) -= x(i, 0) * A(j, i);
        }
    }
    return x;
}

// 解上三角方程，用法：x = solveUpperTriangular(A,b)
Matrix solveUpperTriangular(const Matrix &A, const Matrix &b, int bandwidth){
    Matrix x = b;
    int n = A.n;
    for(int i = n-1; i >= 0; i--){
        x(i, 0) /= A(i, i);
        if(bandwidth == -1){
            for(int j = 0; j < i; j++)
                x(j, 0) -= x(i, 0) * A(j, i);
        } else {
            for(int j = std::max(i - bandwidth, 0); j < i; j++)
                x(j, 0) -= x(i, 0) * A(j, i);
        }
    }
    return x;
}

// 解方程Ax=b，算法为列主元法Gauss消元，用法：x = solve(A,b)
Matrix solve(Matrix A, Matrix b){
    if(A.n<A.m || A.n!=b.n || A.m==0){
        std::cerr << "Matrix Error! The method solve() cannot solve an ill-posed equation!" << std::endl;
        return Matrix();
    }
    int n = A.n, m = A.m;
    Matrix x(m,1);
    int* columns = new int[m];
    int col_cnt;
    for(int i = 0; i < m; i++){
        int p = i;
        for(int j = i; j < n; j++)
            if(fabs(A(j, i))>fabs(A(p, i))) p=j;
        if(p!=i) A.swaprow(i,p), b.swaprow(i,p);
        if( !A(i, i) ){
            std::cerr << "Matrix Error! The method solve() cannot solve an singular equation!" << std::endl;
            std::cerr << "Error occurs at i=" << i << std::endl;
            return Matrix();
        }
        col_cnt = 0;
        for(int j = i; j < m; j++)
            if( A(i,j) ) columns[col_cnt++] = j;
        // 冗余列优化，显著提升稀疏矩阵运算速度
        for(int j = i+1; j < n; j++){
            if( !A(j, i) ) continue; // 冗余行优化，显著提升稀疏矩阵运算速度
            double coef = A(j, i) / A(i, i);
            for(int k = 0; k < col_cnt; k++)
                A(j, columns[k]) -= A(i, columns[k]) * coef;
            b(j, 0) -= b(i, 0) * coef;
        }
    }
    for(int i = m-1; i >= 0; i--){
        x(i, 0) = b(i, 0)/A(i, i);
        for(int j = 0; j < i; j++)
            b(j, 0) -= A(j, i) * x(i, 0);
    }
    delete [] columns;
    return x;
}
ColVector Matrix::solve(const ColVector & b) const{
    return ::solve(*this, b);
}

// 共轭梯度法求解方程 Ax=b，要求A是方阵
ColVector CG_solve(const Matrix &A, const ColVector &b){
    return CG_solve(A, b, 1e-6);
}
ColVector CG_solve(const Matrix &A, const ColVector &b, const double err){
    return CG_solve(A, b, err, ColVector());
}
ColVector CG_solve(const Matrix &A, const ColVector &b, const double err, ColVector x){
    if(x.empty()) x = ColVector(b.size());
    ColVector r = A*x-b;
    ColVector p = -r;
    long long step = 0;
    while(r.vecnorm(2) >= err){
        step++;
        double alpha = - value(r.T()*p) / (p.T()*A*p);
        x = x + alpha*p;
        double tmp = value(r.T()*r);
        r = r + alpha*A*p;
        double beta = value(r.T()*r) / tmp;
        p = -r + beta*p;
    }
    std::cout << "Steps: " << step << std::endl;
    return x;
}

// 返回矩阵的行列式，用高斯消元法计算。用法：d=A.det()
double Matrix::det() const{
    if(m!=n || m==0){
        std::cerr << "fracMatrix Error! Cannot calculate the determinate of a non-square or empty matrix!" << std::endl;
        return 0;
    }
    Matrix A(*this);
    double ans = 1;
    for(int i = 0; i < n; i++){
        int p = i;
        while(p<n && A(p, i)==0) p++;
        if(p==n) return 0;
        if(p!=i) A.swaprow(i,p), ans = -ans;
        ans *= A(i, i);
        for(int j = i+1; j < n; j++){
            double coef = A(j, i)/A(i, i);
            for(int k = i; k < n; k++)
                A(j, k) -= A(i, k)*coef;
        }
    }
    return ans;
}

// 返回矩阵的行列式，只是提供A.det()方法的另一种调用方式。用法：d=det(A)
double det(const Matrix &A){
    return A.det();
}

// 返回矩阵的逆矩阵，用列主元高斯消元法计算。用法：B=A.inv()
Matrix Matrix::inv() const{
    if(m!=n || m==0){
        std::cerr << "Matrix Error! There's no inverse of a non-square or empty matrix!" << std::endl;
        return Matrix();
    }
    Matrix A(n,2*n);
    for(int i = 0; i < n; i++)
    {
        A(i, i+n) = 1;
        for(int j = 0; j < n; j++)
            A(i, j) = element(i,j);
    }
    for(int i = 0; i < n; i++){
        int p = i;
        for(int j = i+1; j < n; j++)
            if(fabs(A(j, i))>fabs(A(p, i))) p=j;
        if(A(p, i)==0){
            std::cerr << "Matrix Error! There's no inverse of a singular matrix!" << std::endl;
            return Matrix();
        }
        if(p!=i) A.swaprow(i,p);
        for(int k = i+1; k < 2*n; k++)
            A(i, k) /= A(i, i);
        A(i, i) = 1;
        for(int j = 0; j < n; j++){
            if(i==j) continue;
            double coef = A(j, i);
            for(int k = i; k < 2*n; k++)
                A(j, k) -= A(i, k)*coef;
        }
    }
    Matrix ans(n,n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            ans(i, j) = A(i, j+n);
    return ans;
}

// 返回矩阵的逆矩阵，只是提供A.inv()方法的另一种调用方式。用法：B=inv(A)
Matrix inv(const Matrix &A){
    return A.inv();
}

// 改进Cholesky分解（LDL分解），用法：L=choleskyImproved(A)，D的元素存储在L的对角线上
Matrix choleskyImproved(const Matrix &A){
    if(A.m!=A.n || A.m==0){
        std::cerr << "Matrix Error! The method cholesky() cannot apply on a non-square or empty matrix!" << std::endl;
        return Matrix();
    }
    int n = A.n;
    Matrix L(n, n);
    for(int j = 0; j < n; j++)
    {
        L(j, j) = A(j, j);
        for(int k = 0; k < j; k++)
            L(j, j) -= L(j, k)*L(k, k)*L(j, k);
        for(int i = j+1; i < n; i++)
        {
            L(i, j) = A(i, j);
            for(int k = 0; k < j; k++)
                L(i, j) -= L(i, k)*L(k, k)*L(j, k);
            L(i, j) /= L(j, j);
        }
    }
    return L;
}

// 用改进Cholesky方法求解正定对称方程，用法：x = solveByLDL(A,b)
Matrix solveByLDL(const Matrix &A, const Matrix &b){
    Matrix L = choleskyImproved(A);
    Matrix D = diag(L);
    L = L - diag(D) + eye(L.n);
    Matrix y = solveLowerTriangular(L, b);
    y = dotdiv(y,D);
    return solveUpperTriangular(L.T(), y);
}

// Gill-Murray修正Cholesky分解
Matrix gillMurray(Matrix A){
    if(A.m!=A.n || A.n==0){
        std::cerr << "Matrix Error! The method gillMurray() cannot apply on a non-square or empty matrix!" << std::endl;
        exit(-1);
    }
    using std::max;
    int n = A.n;
    double gamma=0, xi=0;
    for(int i = 0; i < n; i++)
    {
        gamma = max(gamma, fabs(A(i, i)));
        for(int j = 0; j < i; j++)
            xi = max(xi, fabs(A(i, j)));
    }
    double nu = max(1.0, sqrt(n*n-1));
    double beta2 = max(max(gamma,xi/nu),1e-6);
    Matrix c(n,n);
    for(int i = 0; i < n; i++)
        c(i, i) = A(i, i);
    Matrix L(n,n);
    for(int j = 0; j < n; j++)
    {
        int q = j;
        for(int k = j+1; k < n; k++)
            if(fabs(c(k, k))>fabs(c(q, q))) q = k;
        if(j!=q) A.swapcol(j,q), A.swaprow(j,q);
        for(int k = 0; k < j; k++)
            L(j, k) = c(j, k)/L(k, k);
        for(int i = j+1; i < n; i++)
        {
            c(i, j) = A(i, j);
            for(int k = 0; k < j; k++)
                c(i, j) -= c(i, k)*L(j, k);
        }
        double theta = 0;
        for(int k = j+1; k < n; k++)
            theta = max(theta, fabs(c(k, j)));
        L(j, j) = max(max(fabs(c(j, j)),theta*theta/beta2),1e-3);
        for(int i = j+1; i < n; i++)
            c(i, i) -= c(i, j)*c(i, j)/L(j, j);
    }
    return L;
}

// 用Gill-Murray修正Cholesky方法求解正定对称方程，用法：x = solveByLDL_GM(A,b)
Matrix solveByLDL_GM(const Matrix &A, const Matrix &b){
    Matrix L = gillMurray(A);
    Matrix D = diag(L);
    L = L - diag(D) + eye(L.n);
    Matrix y = solveLowerTriangular(L, b);
    y = dotdiv(y,D);
    return solveUpperTriangular(L.T(), y);
}

// 返回矩阵的行最简形式，调用方式：H=A.rref()
Matrix Matrix::rref() const{
    Matrix A(*this);
    int row = 0;
    for(int i = 0; i < std::min(n,m); i++){
        int p = row;
        for(int j = row+1; j < n; j++)
            if(fabs(A(j, i))>fabs(A(p, i))) p=j;
        if(A(p, i)==0) continue;
        if(p!=row) A.swaprow(row,p);
        for(int k = i+1; k < m; k++)
            A(row, k) /= A(row, i);
        A(row, i) = 1;
        for(int j = 0; j < n; j++){
            if(j==row) continue;
            double coef = A(j, i)/A(row, i);
            for(int k = i; k < m; k++)
                A(j, k) -= A(row, k)*coef;
        }
        row++;
    }
    int r = 0;
    while(r<n && A.getSubmatrix(r,r,0,m-1).vecnorm(2)>1e-10) r++;
    return r ? A.getSubmatrix(0,r-1, 0, m-1) : Matrix();
}

// 求解满秩分解A=FG，用法：A.FGdecompose(F,G)
void Matrix::FGdecompose(Matrix &F, Matrix &G) const{
    G = rref();
    F = Matrix(n, G.n);
    int num = 0;
    for(int i = 0; i < G.n; i++)
        for(int j = i; j < G.m; j++)
            if(G(i, j)==1){
                F.setSubmatrix(0,num,getSubmatrix(0,n-1,j,j));
                num++;
                break;
            }
}

// 求解矩阵的M-P广义逆，调用方法：B=A.pinv()
Matrix Matrix::pinv() const{
    Matrix F,G;
    FGdecompose(F,G);
    return G.T()*(G*G.T()).inv()*(F.T()*F).inv()*F.T();
}

// 求解矩阵M-P的广义逆，调用方法：B=pinv(A)，与B=A.pinv()等价
Matrix pinv(const Matrix &A){
    return A.pinv();
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

// 返回矩阵中所有元素的平方和
double Matrix::sqrsum() const{
    double res = 0;
    for(int i = 0; i < n*m; i++)
        res += a[i]*a[i];
    return res;
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

//---------------------------1.1.0版本新增函数----------------------------------

std::vector<Complex> Matrix::eigen() const{
    Matrix X = randInvertibleMatrix(n);
    Matrix A = X * (*this) * X.inv();
    std::vector<Complex> res;
    Matrix H = A.realSchur();
    int i = 0;
    while(i < n){
        if(i==n-1 || H(i+1,i)==0){
            res.push_back(H(i,i));
            i++;
        } else {
            auto p = H.getSubmatrix(i,i+1,i,i+1).getComplexEigen();
            res.push_back(p.first);
            res.push_back(p.second);
            i += 2;
        }
    }
    return res;
}

Matrix Matrix::realSchur() const{
    auto [H, Q] = hessenberg();
    static const double u = 1e-14;
    while(true){
        for(int i = 1; i < n; i++){
            if( fabs(H(i,i-1)) <= (fabs(H(i,i))+fabs(H(i-1,i-1)))*u )
                H(i,i-1) = 0;
        }
        int m = 1;
        while(m <= n){
            if(m == n || fabs(H(n-m,n-m-1)) < u){
                m++;
            } else {
                if( (m == n-1 || fabs(H(n-m-1,n-m-2)) < u) && H.getSubmatrix(n-m-1,n-m,n-m-1,n-m).isComplexEigen()){
                    m += 2;
                } else {
                    break;
                }
            }
        }
        if(m == n+1) break;
        int l = n - m;
        while( l > 0 && fabs(H(l,l-1)) >= u ){
            l--;
        }
        l--;
        auto p = H.getSubmatrix(l+1,n-m, l+1,n-m).doubleQR();
        H.setSubmatrix(l+1,l+1, std::move(p.first));
        Matrix P = std::move(p.second);
        if(l>=0) H.setSubmatrix(0,l+1, H.getSubmatrix(0,l,l+1,n-m)*P);
        if(m>1) H.setSubmatrix(l+1,n-m+1, P.T()*H.getSubmatrix(l+1,n-m,n-m+1,n-1));
    }
    for(int k = 2; k < n; k++)
        for(int j = 0; j < k-1; j++)
            H(k,j) = 0;
    return H;
}

std::pair<Matrix, Matrix> Matrix::doubleQR() const {
    if (n <= 2) {
        // 对于 2×2 的矩阵，使用位移QR迭代
        double mu = element(n - 1, n - 1);
        Matrix H = (*this) - mu * eye(n);
        auto [Q, R] = H.getQR();
        return std::make_pair(R * Q + mu * eye(n), Q);
    }
    Matrix P = eye(n), H = (*this);
    double mm = n - 1;
    double s = H(mm - 1, mm - 1) + H(n - 1, n - 1);
    double t = H(mm - 1, mm - 1) * H(n - 1, n - 1) - H(mm - 1, n - 1) * H(n - 1, mm - 1);
    double x = H(0, 0) * H(0, 0) + H(0, 1) * H(1, 0) - s * H(0, 0) + t;
    double y = H(1, 0) * (H(0, 0) + H(1, 1) - s);
    double z = H(1, 0) * H(2, 1);
    for (int k = 0; k < n - 2; k++) {
        ColVector tmpc(3);
        tmpc(0) = x; tmpc(1) = y; tmpc(2) = z;
        auto hh = tmpc.householder();  // hh.first 为 v, hh.second 为 beta

        // 左更新：更新 H 的行 k 至 k+2，列 q 至 n-1，其中 q = max(0, k-1)
        int q = (k - 1 >= 0) ? (k - 1) : 0;
        Matrix subL = H.getSubmatrix(k, k + 2, q, n - 1);
        Matrix vtSubL = (hh.first.T()) * subL;
        Matrix updateL = hh.second * (hh.first * vtSubL);
        subL = subL - updateL;
        H.setSubmatrix(k, q, subL);

        // 右更新：更新 H 的行 0 至 r，列 k 至 k+2，其中 r = min(k+3, n-1)
        int r = std::min(k + 3, n - 1);
        Matrix subR = H.getSubmatrix(0, r, k, k + 2);
        Matrix subR_v = subR * hh.first;
        Matrix updateR = hh.second * (subR_v * (hh.first.T()));
        subR = subR - updateR;
        H.setSubmatrix(0, k, subR);

        // 更新 bulge
        x = H(k + 1, k);
        y = H(k + 2, k);
        if (k < n - 3)
            z = H(k + 3, k);

        // 更新累计正交矩阵 P：仅更新 P 的列 k 至 k+2 (共 3 列)
        Matrix P_block = P.getSubmatrix(0, n - 1, k, k + 2);
        Matrix P_block_v = P_block * hh.first;
        Matrix updateP = hh.second * (P_block_v * (hh.first.T()));
        P_block = P_block - updateP;
        P.setSubmatrix(0, k, P_block);
    }
    // 对最后 2×2 区块应用 Householder 反射
    ColVector tmpc(2);
    tmpc(0) = x; tmpc(1) = y;
    auto hh = tmpc.householder();
    // 左更新：更新 H 的行 n-2 至 n-1，列 n-3 至 n-1
    Matrix subL = H.getSubmatrix(n - 2, n - 1, n - 3, n - 1);
    Matrix vtSubL = (hh.first.T()) * subL;
    Matrix updateL = hh.second * (hh.first * vtSubL);
    subL = subL - updateL;
    H.setSubmatrix(n - 2, n - 3, subL);
    // 右更新：更新 H 的行 0 至 n-1，列 n-2 至 n-1
    Matrix subR = H.getSubmatrix(0, n - 1, n - 2, n - 1);
    Matrix subR_v = subR * hh.first;
    Matrix updateR = hh.second * (subR_v * (hh.first.T()));
    subR = subR - updateR;
    H.setSubmatrix(0, n - 2, subR);
    // 更新累计正交矩阵 P 的最后 2 列
    Matrix P_block = P.getSubmatrix(0, n - 1, n - 2, n - 1);
    Matrix P_block_v = P_block * hh.first;
    Matrix updateP = hh.second * (P_block_v * (hh.first.T()));
    P_block = P_block - updateP;
    P.setSubmatrix(0, n - 2, P_block);

    // 将 H 中主对角线以下超过一条次对角线的部分置零
    for (int i = 2; i < n; i++) {
        for (int j = 0; j < i - 1; j++) {
            H(i, j) = 0;
        }
    }
    return std::make_pair(H, P);
}

std::pair<Matrix, Matrix> Matrix::getQR() const {
    int r = n, c = m;
    Matrix Q = eye(n);
    Matrix R = (*this);
    // 只对 j=0,...,min(n-1, m-1) 进行反射
    int lim = std::min(n, m);
    for (int j = 0; j < lim; j++) {
        // 取 R 的子向量：第 j 列，从行 j 到 n-1
        ColVector x = R.getSubmatrix(j, n - 1, j, j);  // 尺寸为 (n-j)×1
        auto [v, beta] = x.householder();
        
        // 更新 R: R(j:n-1, j:m-1) = R(j:n-1, j:m-1) - beta * v * (v^T * R(j:n-1, j:m-1))
        Matrix subR = R.getSubmatrix(j, n - 1, j, m - 1);
        Matrix temp = (v.T()) * subR; // 1×(m-j) 行向量
        subR = subR - beta * (v * temp);
        R.setSubmatrix(j, j, subR);
        
        // 更新 Q: Q(:, j:n-1) = Q(:, j:n-1) - beta * (Q(:, j:n-1) * v) * v^T
        Matrix subQ = Q.getSubmatrix(0, n - 1, j, n - 1);
        Matrix tempQ = subQ * v;  // (n×1) 列向量
        subQ = subQ - beta * (tempQ * (v.T()));
        Q.setSubmatrix(0, j, subQ);
    }
    return std::make_pair(Q, R);
}

std::pair<Matrix, Matrix> Matrix::hessenberg() const {
    Matrix H = (*this);
    Matrix Q = eye(n);
    // 对于 k = 0,..., n-3 进行 Householder 消去
    for (int k = 0; k < n - 2; k++) {
        // 提取子向量：从第 k+1 行至 n-1 行，第 k 列
        ColVector x = H.getSubmatrix(k + 1, n - 1, k, k);  // 尺寸为 (n-k-1)×1
        auto [v, beta] = x.householder();
        
        // 左乘更新: H(k+1:n-1, k:n-1)  = H(k+1:n-1, k:n-1) - beta*v*(v^T * H(k+1:n-1, k:n-1))
        Matrix subH_left = H.getSubmatrix(k + 1, n - 1, k, n - 1);
        Matrix temp_left = (v.T()) * subH_left; // 1×(n-k)
        subH_left = subH_left - beta * (v * temp_left);
        H.setSubmatrix(k + 1, k, subH_left);
        
        // 右乘更新: H(0:n-1, k+1:n-1) = H(0:n-1, k+1:n-1) - beta*(H(0:n-1, k+1:n-1) * v)*v^T
        Matrix subH_right = H.getSubmatrix(0, n - 1, k + 1, n - 1);
        Matrix temp_right = subH_right * v;  // (n×1) 列向量
        subH_right = subH_right - beta * (temp_right * (v.T()));
        H.setSubmatrix(0, k + 1, subH_right);
        
        // 更新累计正交矩阵 Q: Q(:, k+1:n-1) = Q(:, k+1:n-1) - beta*(Q(:, k+1:n-1) * v)*v^T
        Matrix subQ = Q.getSubmatrix(0, n - 1, k + 1, n - 1);
        Matrix tempQ = subQ * v;
        subQ = subQ - beta * (tempQ * (v.T()));
        Q.setSubmatrix(0, k + 1, subQ);
    }
    // 将 H 中除主对角线和次对角线外的下三角部分清零
    for (int i = 2; i < n; i++) {
        for (int j = 0; j < i - 1; j++) {
            H(i, j) = 0;
        }
    }
    return std::make_pair(H, Q);
}

std::pair<ColVector,double> Matrix::householder() const{
    ColVector v = zeros(n,1);
    if(maxnorm()==0){
        return std::make_pair(v, 0.0);
    }
    double ita = maxnorm(), beta;
    ColVector x = (*this)/ita;
    double sigma = 0.0;
    for(int i = 1; i < n; i++){
        sigma += x(i) * x(i);
        v(i) = x(i);
    }
    if(sigma == 0){
        beta = 0;
    } else {
        double alpha = sqrt(x(0)*x(0)+sigma);
        if(x(0) <= 0)
            v(0) = x(0) - alpha;
        else
            v(0) = -sigma/(x(0)+alpha);
        beta = 2*v(0)*v(0) / (sigma+v(0)*v(0));
        v = v/v(0);
    }
    return std::make_pair(v,beta);
}

std::pair<Complex,Complex> Matrix::getComplexEigen() const{
    double trace = element(0,0)+element(1,1);
    Complex delta = sqr(trace) - 4*det();
    return std::make_pair( 0.5*(trace+sqrt(delta)), 0.5*(trace-sqrt(delta)) );
}

bool Matrix::isComplexEigen() const{
    double trace = element(0,0)+element(1,1);
    double delta = sqr(trace) - 4*det();
    return delta < -1e-13;
}

double norm(const ColVector &x, int p = 2){
    if(p == 0) return max(abs(x));
    else if(p == 1) return sum(abs(x));
    else if(p == 2) return sqrt(x.sqrsum());
    else return -1;
}

ColVector Matrix::getEigenVector(double lambda) const{
    const Matrix &A = (*this);
    Matrix B = A - lambda * eye(n);
    ColVector v(n); v(0) = 1;
    int step = 0;
    while(norm(A * v - lambda * v) >= 1e-15){
        ColVector y = B.solve(v);
        v = y / norm(y);
        if(++step == 2) break;
    }
    return v;
}

std::tuple<Matrix, Matrix, Matrix> Matrix::svd() const{
    Matrix Atil(n*2, n*2);
    // A 的奇异值就是 Atil 的正特征值
    Atil.setSubmatrix(n, 0, (*this));
    Atil.setSubmatrix(0, n, (*this).T());
    auto eig = Atil.eigen();
    std::vector<double> realEigen;
    for(auto x : eig)
        if(x.real() > 0)
            realEigen.push_back(x.real());
    sort(realEigen.begin(), realEigen.end(), std::greater<double>());

    Matrix U(n, n), V(n, n);
    int idx = 0;
    for(auto x : realEigen){
        // 反幂法求特征向量
        ColVector v = Atil.getEigenVector(x);
        v = v * sqrt(2.0);
        V.setSubmatrix(0, idx, v.getSubmatrix(0, n-1, 0, 0));
        U.setSubmatrix(0, idx, v.getSubmatrix(n, n*2-1, 0, 0));
        idx++;
    }
    return std::make_tuple(U, diag(ColVector(realEigen)), V);
}

Matrix randMatrix(const int &n, const int &m){
    Matrix A(n,m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            A(i,j) = (double)rand()/RAND_MAX;
    return A;
}

Matrix randInvertibleMatrix(const int &n){
    Matrix A = randMatrix(n, n);
    while(fabs(det(A))<1e-8){
        A = randMatrix(n, n);
    }
    return A;
}

Matrix tril(const Matrix &A, int d = 0){
    Matrix B = zeros(A.n, A.m);
    for(int i = 0; i < A.n; i++)
        for(int j = 0; j < A.m && j <= i + d; j++)
            B(i,j) = A(i,j);
    return B;
}

Matrix triu(const Matrix &A, int d = 0){
    Matrix B = zeros(A.n, A.m);
    for(int i = 0; i < A.n; i++)
        for(int j = i + d; j < A.m; j++)
            B(i,j) = A(i,j);
    return B;
}

void Matrix::setdiag(const ColVector &x){
    if(n != m || n != x.size()){
        std::cerr << "Matrix Error! The method setdiag() cannot apply on a non-square matrix or a vector of different size!" << std::endl;
        return;
    }
    for(int i = 0; i < n; i++)
        a[i * m + i] = x(i);
}

double dot(const ColVector &x, const ColVector &y){
    if(x.size() != y.size()){
        std::cerr << "Vector Error! The method dot() cannot apply on two vectors of different size!" << std::endl;
        return 0;
    }
    double res = 0;
    for(int i = 0; i < x.size(); i++)
        res += x(i) * y(i);
    return res;
}

std::tuple<Matrix, Matrix, Matrix> PLU(Matrix A) {
    int n = A.n, m = A.m;
    Matrix L = (n >= m) ? zeros(n, m) : zeros(n, n);
    Matrix U = (n >= m) ? zeros(m, m) : zeros(n, m);
    std::vector<int> P(n);
    for (int i = 0; i < n; ++i) P[i] = i;
    int mm = std::min(n, m);
    for (int i = 0; i < mm; ++i) L(i, i) = 1.0;
    for (int k = 0; k < mm; ++k) {
        int pivot = k;
        double maxv = std::fabs(A(k, k));
        for (int i = k + 1; i < n; ++i) {
            if (std::fabs(A(i, k)) > maxv) {
                maxv = std::fabs(A(i, k));
                pivot = i;
            }
        }
        if (maxv == 0.0) {
            std::cerr << "[Matrix] PLU:: cannot decompose matrix" << std::endl;
            return std::make_tuple(Matrix(), Matrix(), Matrix());
        }
        if (pivot != k) {
            for (int j = 0; j < m; ++j) std::swap(A(k, j), A(pivot, j));
            for (int j = 0; j < k; ++j) std::swap(L(k, j), L(pivot, j));
            std::swap(P[k], P[pivot]);
        }
        for (int j = k; j < m; ++j) U(k, j) = A(k, j);
        for (int i = k + 1; i < n; ++i) {
            L(i, k) = A(i, k) / U(k, k);
            for (int j = k + 1; j < m; ++j) {
                A(i, j) -= L(i, k) * U(k, j);
            }
            A(i, k) = 0.0;
        }
    }
    Matrix Pmat(n, n);
    for (int i = 0; i < n; ++i) Pmat(P[i], i) = 1.0;
    return std::make_tuple(Pmat, L, U);
}

std::tuple<Matrix, Matrix, Matrix> Matrix::PLU() const {
    return ::PLU(*this);
}

#endif