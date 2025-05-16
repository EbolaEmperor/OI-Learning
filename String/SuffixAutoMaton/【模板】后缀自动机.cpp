#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 4000010;
int ch[MAXN][26], prt[MAXN];
int len[MAXN], sz[MAXN];
int lst = 1, tot = 1;
char s[MAXN];
int c[MAXN], a[MAXN];
LL ans = 0;

// len[p]: 点 p 代表的子串的长度
// sz[p]: 点 p 对应的 endpos 等价类的集合大小
//       （不是 parent 树上的子树大小！！！）

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
	}
	sz[np] = 1;
	lst = np;
}

// 先做桶排得到 parent 树的内向拓扑序，然后自底向上累加求出 sz
void getsize()
{
	for (int i = 1; i <= tot; i++) c[len[i]]++;
	for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
	for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
	for (int i = tot; i >= 1; i--) sz[prt[a[i]]] += sz[a[i]];
}

int main()
{
	scanf("%s", s);
	int l = strlen(s);
	for (int i = 0; i < l; i++)
		insert(s[i] - 'a');
	getsize();
	for (int i = 1; i <= tot; i++)
		if (sz[i] > 1)
			ans = max(ans, (LL)sz[i] * len[i]);
	cout << ans << endl;
	return 0;
}