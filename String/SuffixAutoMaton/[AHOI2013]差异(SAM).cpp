#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1000010;
LL ans = 0;
char s[N];
int ch[N][26], prt[N];
int len[N], cnt[N];
int lst = 1, tot = 1;
vector<int> G[N];

void insert(int c)
{
	int p = lst, np = ++tot;
	len[np] = len[p] + 1;
	while (p && !ch[p][c]) ch[p][c] = np, p = prt[p];
	if (!p) prt[np] = 1;
	else
	{
		int q = ch[p][c];
		if (len[q] == len[p] + 1) prt[np] = q;
		else
		{
			int nq = ++tot;
			len[nq] = len[p] + 1;
			prt[nq] = prt[q];
			prt[q] = prt[np] = nq;
			memcpy(ch[nq], ch[q], sizeof(ch[nq]));
			while (ch[p][c] == q)
				ch[p][c] = nq, p = prt[p];
		}
	}
	lst = np;
	cnt[lst] = 1;
}

void dfs(int u, int fa)
{
	// 统计每个 LCA 的贡献，即，统计有多少对前缀以 u 为 LCA
	// cnt[u] 就是 u 的子树里的节点一共表示了几个前缀
	for (int v : G[u])
	{
		if (v == fa) continue;
		dfs(v, u);
		ans -= 2ll * cnt[v] * cnt[u] * len[u];
		cnt[u] += cnt[v];
	}
}

int main()
{
	scanf("%s", s);
	int l = strlen(s);
	ans = (LL)l * (l - 1) * (l + 1) / 2;
	// 反转，变成求每对前缀的最长公共后缀
	// 在 SAM 的 parent 树上，任意两个串的最长公共后缀就是它们的 LCA
	for (int i = l - 1; i >= 0; i--)
		insert(s[i] - 'a');
	for (int i = 2; i <= tot; i++)
		G[prt[i]].push_back(i);
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}
