#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1200010;
int ch[MAXN][31], prt[MAXN], len[MAXN];
int lst = 1, tot = 1;

void insert(int c)
{
	int p = lst, np = ++tot;
	len[np] = len[p] + 1;
	while (p && !ch[p][c])
		ch[p][c] = np, p = prt[p];
	if (!p) prt[np] = 1;
	else
	{
		int q = ch[p][c];
		if (len[p] + 1 == len[q]) prt[np] = q;
		else
		{
			int nq = ++tot;
			len[nq] = len[p] + 1;
			memcpy(ch[nq], ch[q], sizeof(ch[nq]));
			prt[nq] = prt[q];
			prt[q] = prt[np] = nq;
			while (ch[p][c] == q)
				ch[p][c] = nq, p = prt[p];
		}
	};
	lst = np;
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) insert(a[i]);
    for(int i = 0; i < n; i++) insert(a[i]);

    int cur = 1, c;
    for(int i = 0; i < n; i++)
    {
        for(c = 0; c <= 30; c++)
            if(ch[cur][c]) break;
        cout << c << " ";
        cur = ch[cur][c];
    }
    cout << endl;

	return 0;
}

// 题意：给一个串，求字典序最小的循环同构串
// 做法：把串复制一遍，建 SAM，在 SAM 上跑，每次贪心走能走的、最小字母的边