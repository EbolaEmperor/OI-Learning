#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
// len[p]: 节点 p 代表的串的长度
// cnt[p]: 节点 p 代表的串是几个串的子串
int ch[N][26], prt[N], len[N], cnt[N], bef[N];
int lst = 1, tot = 1, T = 0;
char s[N];
int sum[N];
string str[N];

void insert(int c, int id)
{
	int np;
	if (ch[lst][c] && len[ch[lst][c]] == len[lst] + 1)
		np = lst = ch[lst][c];
	else
	{
		int p = lst; np = ++tot;
		len[np] = len[p] + 1;
		while (p && !ch[p][c]) ch[p][c] = np, p = prt[p];
		if (!p) prt[np] = 1;
		else
		{
			int q = ch[p][c];
			if (len[q] == len[p] + 1) prt[np] = q;
			else
			{
				bool fuck = 0;
				if (p == lst) fuck = 1, np = 0, tot--;
				int nq = ++tot;
				len[nq] = len[p] + 1;
				bef[nq] = bef[q];
				cnt[nq] = cnt[q];
				memcpy(ch[nq], ch[q], sizeof(ch[nq]));
				prt[nq] = prt[q];
				prt[q] = prt[np] = nq;
				while (ch[p][c] == q) ch[p][c] = nq, p = prt[p];
				if (fuck) np = nq;
			}
		}
		lst = np;
	}
	while(np && bef[np] != id)
		++cnt[np], bef[np] = id, np = prt[np];
}

void insert_string(char *s)
{
	str[++T] = s;
	int l = strlen(s);
	lst = 1;
	for (int i = 0; i < l; i++)
		insert(s[i] - 'a', T);
}

int main()
{
	int n; scanf("%d", &n);
	while(n--) scanf("%s", s), insert_string(s);
	long long ans = 0;
	for (int i = 1; i <= tot; i++)
		ans += len[i] - len[prt[i]];
	printf("%lld\n", ans);
	printf("%d\n", tot);

	// 下面输入一个串，询问这个串在几个子串里出现过
	// scanf("%s", s);
	// int now = 1;
	// for (int i = 0; s[i]; i++)
	// {
	// 	int c = s[i] - 'a';
	// 	now = ch[now][c];
	// 	if (now == 0) break;
	// }
	// printf("%d\n", cnt[now]);
	return 0;
}