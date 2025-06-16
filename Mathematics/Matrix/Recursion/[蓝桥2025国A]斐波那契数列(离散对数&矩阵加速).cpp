#include <iostream>
#include <cstdio>
#define MOD 998244353
using namespace std;

typedef long long LL;

struct Matrix
{
	int m, n;
	LL a[3][3];
	Matrix(int _m = 0, int _n = 0) : m(_m), n(_n) {}
	Matrix(int _m, int _n, std::initializer_list<LL> list)
	{
		m = _m, n = _n;
		auto it = list.begin();
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				a[i][j] = *it, ++it;
	}
};

Matrix operator*(Matrix a, Matrix b)
{
	if (a.n != b.m)
		return Matrix(0, 0);
	Matrix ans;
	ans.m = a.m;
	ans.n = b.n;
	for (int i = 0; i < a.m; i++)
		for (int j = 0; j < b.n; j++)
		{
			ans.a[i][j] = 0;
			for (int k = 0; k < a.n; k++)
				ans.a[i][j] = (ans.a[i][j] + a.a[i][k] * b.a[k][j]) % (MOD-1);
		}
	return ans;
}

Matrix Pow(Matrix a, LL b)
{
	Matrix ans = a;
	b--;
	while (b)
	{
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

LL Pow(LL a, LL b)
{
	LL ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ans;
}

int main()
{
	LL n;
	cin >> n;
	if (n == 1)
		cout << 2 << endl;
	else if (n == 2)
		cout << 6 << endl;
	else
	{
		Matrix A(3, 3, {1, 1, 1, 0, 1, 1, 0, 1, 0});
		A = Pow(A, n - 2);
		Matrix ans(3, 1, {640079067, 1, 640079066});
		ans = A * ans;
		cout << Pow(3, ans.a[0][0]) << endl;
	}
	return 0;
}
