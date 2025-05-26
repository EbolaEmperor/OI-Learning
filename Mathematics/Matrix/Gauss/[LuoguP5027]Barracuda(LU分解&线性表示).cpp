// 基于 LU 分解的 O(n^3) 做法，比原题的 O(n^4) 强
// 本质上要解决 Lx=b 的问题，其中 L 几乎是下三角的，但对角线上面那条斜线，从下往上有一些非零数
// 找到第一个违背下三角形式的位置，把它的值设为 x，然后代入时把所有答案表示成 kx+b 的形式，再通过最后一行算出 x

#include <bits/stdc++.h>
using namespace std;

const int M = 105;

class Matrix {
public:
    int n, m;
    double a[M][M];

    Matrix(int rows = 0, int cols = 0) : n(rows), m(cols) {
        memset(a, 0, sizeof(a));
    }

    Matrix (const Matrix &other) : n(other.n), m(other.m) {
        memcpy(a, other.a, sizeof(a));
    }

    std::pair<Matrix, Matrix> getPLU(vector<int> &b) const {
        Matrix A(*this);
        Matrix L(n, m), U(m, m);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                L.a[i][j] = (i == j ? 1.0 : 0.0);

        int mm = std::min(n, m);
        for (int k = 0; k < mm; ++k) {
            int pivot = k;
            double maxv = std::fabs(A.a[k][k]);
            for (int i = k + 1; i < n; ++i) {
                if (std::fabs(A.a[i][k]) > maxv) {
                    maxv = std::fabs(A.a[i][k]);
                    pivot = i;
                }
            }
            if (maxv == 0.0) {
                cout << "illegal" << endl;
                exit(0);
            }
            if (pivot != k) {
                for (int j = 0; j < m; ++j) std::swap(A.a[k][j], A.a[pivot][j]);
                for (int j = 0; j < k; ++j) std::swap(L.a[k][j], L.a[pivot][j]);
                std::swap(b[k], b[pivot]);
            }
            for (int j = k; j < m; ++j) U.a[k][j] = A.a[k][j];
            for (int i = k + 1; i < n; ++i) {
                L.a[i][k] = A.a[i][k] / U.a[k][k];
                for (int j = k + 1; j < m; ++j) {
                    A.a[i][j] -= L.a[i][k] * U.a[k][j];
                }
                A.a[i][k] = 0.0;
            }
        }

        return std::make_pair(L, U);
    }

    void randomize() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = rand() % 100 + 1;
    }

    Matrix operator * (const Matrix &b) const {
        Matrix c(n, b.m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < b.m; ++j) {
                c.a[i][j] = 0.0;
                for (int k = 0; k < m; ++k)
                    c.a[i][j] += a[i][k] * b.a[k][j];
            }
        return c;
    }

    void print() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout  << a[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

struct LinearPoly {
    double k, b;
    LinearPoly() : k(0), b(0) {}
    LinearPoly(double b) : k(0), b(b) {}
    LinearPoly(double k, double b) : k(k), b(b) {}
    double operator()(double x) const {
        return k * x + b;
    }
    LinearPoly operator+(const LinearPoly &other) const {
        return LinearPoly(k + other.k, b + other.b);
    }
    LinearPoly operator-(const LinearPoly &other) const {
        return LinearPoly(k - other.k, b - other.b);
    }
    LinearPoly operator*(double scalar) const {
        return LinearPoly(k * scalar, b * scalar);
    }
    friend LinearPoly operator*(double scalar, const LinearPoly &poly) {
        return poly * scalar;
    }
    LinearPoly operator/(double scalar) const {
        return LinearPoly(k / scalar, b / scalar);
    }
    LinearPoly operator*(const LinearPoly &other) const {
        return LinearPoly(k * other.k, k * other.b + b * other.k);
    }
    LinearPoly operator/(const LinearPoly &other) const {
        return LinearPoly(k / other.k, (b - k * other.b / other.k) / other.k);
    }
};

vector<double> solveUpper(const Matrix &U, const vector<double> &b) {
    int n = U.n;
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b[i];
        for (int j = i + 1; j < n; ++j) {
            sum -= U.a[i][j] * x[j];
        }
        if (fabs(U.a[i][i]) < 1e-12) {
            cout << "illegal" << endl;
            exit(0);
        }
        x[i] = sum / U.a[i][i];
    }
    return x;
}

int main() {
    int n;
    cin >> n;
    Matrix A(n + 1, n);
    vector<int> b(n + 1);

    for(int i = 0, m; i <= n; i++) {
        cin >> m;
        for(int j = 0, x; j < m; j++) {
            cin >> x;
            A.a[i][x - 1] += 1.0;
        }
        cin >> b[i];
    }
    auto [L, U] = A.getPLU(b);

    vector<int> nice;
    for(int k = 0; k <= n; k++){
        static LinearPoly ans[M];
        for(int i = 0; i < k; i++) {
            ans[i] = LinearPoly(0, b[i]);
            for(int j = 0; j < i; j++)
                ans[i] = ans[i] - L.a[i][j] * ans[j];
        }
        ans[k] = LinearPoly(1, 0);
        vector<double> res(n);

        if (k < n) {
            for(int i = k + 1; i < n; i++) {
                ans[i] = LinearPoly(0, b[i]);
                for(int j = 0; j < i; j++)
                    ans[i] = ans[i] - L.a[i][j] * ans[j];
            }
            LinearPoly lst(0, 0);
            for(int i = 0; i < n; i++)
                lst = lst + ans[i] * L.a[n][i];
            if(fabs(lst.k) < 1e-10) continue;

            double x = (b[n] - lst.b) / lst.k;
            for(int i = 0; i < n; i++)
                res[i] = ans[i](x);
        } else {
            for(int i = 0; i < n; i++)
                res[i] = ans[i].b;
        }
        res = solveUpper(U, res);

        bool good = 1;
        int max_val = 0;
        int cnt = 0, id = -1;
        for(int i = 0; i < n; i++) {
            if(res[i] <= 1e-15 || abs(res[i] - round(res[i])) > 1e-10) {
                good = 0;
                break;
            }
            int a = round(res[i]);
            if(a == max_val) cnt++;
            else if (a > max_val) max_val = a, cnt = 1, id = i;
        }
        if(!good || cnt > 1) continue;
        nice.push_back(id + 1);
    }

    if(nice.size() == 1) cout << nice[0] << endl;
    else cout << "illegal" << endl;
    
    return 0;
}