#ifndef _LINPROG_H_
#define _LINPROG_H_

#include <iostream>
#include <random>
#include "matrix_simple.h"

#define SIMPLEX_BIGO 1e-9
#define SIMPLEX_EPS 1e-6

bool simplex_find(Matrix &a, int &x, int &y){
    const int n = a.n-1, m = a.m-1;
    double maxx = 0; x = y = 0;
    for(int j = 1; j <= m; j++)
        if(a[0][j] > SIMPLEX_EPS){
            int tp = 0;
            double minn = 0;
            for(int i = 1; i <= n; i++)
                if(a[i][j] < -SIMPLEX_EPS){
                    double tmp = -a[i][0]/a[i][j];
                    if(!tp || tmp<minn) minn = tmp, tp = i;
                }
            if(!tp){
                x = y = -1;
                return false;
            }
            double tmp = minn*a[0][j];
            if(!x || (tmp>maxx || (rand()&1)))
                maxx = tmp, x = tp, y = j;
        }
    return (bool)x;
}

void simplex_pivot(Matrix &a, int *id, const int &x, const int &y){
    const int n = a.n-1, m = a.m-1;
    std::swap(id[x+m], id[y]);
    double tmp = -a[x][y]; a[x][y] = -1;
    for(int i = 0; i <= m; i++) a[x][i] /= tmp;
    for(int i = 0; i <= n; i++){
        if(i==x || fabs(a[x][y])<SIMPLEX_BIGO) continue;
        double tmp = a[i][y]; a[i][y] = 0;
        for(int j = 0; j <= m; j++)
            a[i][j] += tmp * a[x][j];
    }
}

bool simplex_prework(Matrix &a, int *id){
    const int n = a.n-1, m = a.m-1;
    while(true){
        int x = 0;
        for(int i = 1; i <= n; i++)
            if(a[i][0] < -SIMPLEX_BIGO && (!x || rand()&1)) x = i;
        if(!x) return true;
        int y = 0;
        for(int j = 1; j <= m; j++)
            if(a[x][j] > SIMPLEX_BIGO && (!y || rand()&1)) y = j;
        if(!y) return false;
        simplex_pivot(a, id, x, y);
    }
}

/************************************************************************
 * 此函数用于求解标准型线性规划：
 * max. c^T x
 * s.t. Ax <= b
 *      x >= 0
 * 使用方法： sol = linprog(c,A,b)，返回值为最优点，无解将会返回空向量
*************************************************************************/
ColVector linprog(const ColVector &c, const Matrix &A, const ColVector &b){
    static int *id, x, y;
    const int n = A.n, m = A.m;
    id = new int[n+m+1];
    memset(id, 0, sizeof(int)*(n+m+1));
    Matrix a(n+1, m+1);
    a.setSubmatrix(0, 1, c.T());
    a.setSubmatrix(1, 1, -A);
    a.setSubmatrix(1, 0, b);
    for(int i = 1; i <= m; i++) id[i] = i;
    if(!simplex_prework(a, id)){
        std::cerr << "[linprog] Terminated. Infeasible." << std::endl;
        delete id;
        return Matrix();
    }
    while(simplex_find(a, x, y))
        simplex_pivot(a, id, x, y);
    if(x==-1 && y==-1){
        std::cerr << "[linprog] Terminated. Unbounded." << std::endl;
        delete id;
        return Matrix();
    }
    ColVector ans(m);
    for(int i = 1; i <= n; i++)
        if(id[m+i]) ans(id[m+i]-1) = a[i][0];
    delete id;
    return ans;
}


/**************************************************************************
 * 此函数用于求解带等式约束的线性规划：
 * max. c^T x
 * s.t. A1x <= b1
 *      A2x == b2
 *      x >= 0
 * 使用方法： sol = linprog(c,A1,b1,A2,b2)，返回值为最优点，无解将会返回空向量
***************************************************************************/
Matrix linprog(const Matrix &c, const Matrix &A1, const Matrix &b1, const Matrix &A2, const Matrix &b2){
    Matrix A(A1.n+2*A2.n, A1.m);
    A.setSubmatrix(0, 0, A1);
    A.setSubmatrix(A1.n, 0, A2);
    A.setSubmatrix(A1.n+A2.n, 0, -A2);
    Matrix b(b1.n+2*b2.n, 1);
    b.setSubmatrix(0, 0, b1);
    b.setSubmatrix(b1.n, 0, b2);
    b.setSubmatrix(b1.n+b2.n, 0, -b2);
    return linprog(c, A, b);
}


/*******************************************************************************
 * 此函数用于求解带等式约束及决策变量上下界的线性规划：
 * max. c^T x
 * s.t. A1x <= b1
 *      A2x == b2
 *      l <= x <= u
 * 使用方法： sol = linprog(c,A1,b1,A2,b2,l,u)，返回值为最优点，无解将会返回空向量
********************************************************************************/
Matrix linprog(const Matrix &c, const Matrix &A1, const Matrix &b1, const Matrix &A2, const Matrix &b2, const Matrix &l, const Matrix &u){
    Matrix _A1(A1.n+2*A1.m, A1.m);
    _A1.setSubmatrix(0, 0, A1);
    _A1.setSubmatrix(A1.n, 0, eye(A1.m));
    _A1.setSubmatrix(A1.n+A1.m, 0, -eye(A1.m));
    Matrix _b1(A1.n+2*A1.m, 1);
    _b1.setSubmatrix(0, 0, b1);
    _b1.setSubmatrix(A1.n, 0, u);
    _b1.setSubmatrix(A1.n+A1.m, 0, -l);
    return linprog(c, _A1, _b1, A2, b2);
}

#endif