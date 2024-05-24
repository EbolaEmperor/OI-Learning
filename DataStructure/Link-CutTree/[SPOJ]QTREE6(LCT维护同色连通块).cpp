// LCT 维护树上同色连通块，支持单点颜色修改
// 若一个点是黑的，则向父亲连边，每次颜色修改只需要  link 或者 cut 和父亲的连边
// 询问时，assert 一次，再把根节点 splay 上去，右子树（含所有虚子树）的大小就是答案
// 黑、白各建一棵 LCT，用一样的方式处理，每次修改都要处理两棵 LCT，询问时根据颜色在对应的 LCT 上询问
#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N = 400010;
int treefa[N], n, m;
vector<int> g[N];

class LCT{
public:
	struct Node
	{
        bool isBlack;
		int allsize;
        int imsize;
		int son[2], fa;
	} nd[N];
	int sta[N],top=0;
	int colcnt = 0;

	inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
	inline void maintain(int x){
		nd[x].allsize = nd[ls].allsize + nd[rs].allsize + nd[x].imsize + 1;
	}

	void rotate(int x)
	{
		int y=nd[x].fa,z=nd[y].fa;
		int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
		if(nroot(y)) nd[z].son[nd[z].son[1]==y]=x;
		nd[x].son[k^1]=y;
		nd[y].son[k]=w;
		if(w) nd[w].fa=y;
		nd[x].fa=z;
		nd[y].fa=x;
		maintain(y);
		maintain(x);
	}

	void splay(int x)
	{
		int y=x,z;
		while(nroot(x))
		{
			y=nd[x].fa;
			z=nd[y].fa;
			if(nroot(y)) rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
			rotate(x);
		}
		maintain(x);
	}

	void access(int x)
	{
		int y=0;
		while(x)
		{
			splay(x);
            nd[x].imsize -= nd[y].allsize;
            nd[x].imsize += nd[rs].allsize;
			rs=y;
			maintain(x);
			y=x;x=nd[x].fa;
		}
	}
	int find(int x)
	{
		access(x);splay(x);
		while(ls) x=ls;
		return x;
	}
    // y 在 x 上面
	void cut(int x,int y)
	{
		access(x);
        splay(x);
        nd[ls].fa = 0;
        ls = 0;
        maintain(x); 
	}
    // y 在 x 上面
	void link(int x,int y)
    {
        access(y);
        splay(y);
        access(x);
        splay(x);
        nd[y].son[1] = x;
        nd[x].fa = y;
        maintain(y);
    }

    void modify(int u){
        int y = treefa[u];
        if(nd[u].isBlack) cut(u, y);
        else link(u, y);
        nd[u].isBlack ^= 1;
    }

    int qBlackSize(int u){
        assert(nd[u].isBlack);
        access(u);
        int x = find(u);
        splay(x);
        return nd[rs].allsize;
    }
};

LCT blackLCT, whiteLCT;

void dfs(int u){
    blackLCT.nd[u].isBlack = true;
    for(int v : g[u]){
        if(v == treefa[u]) continue;
        treefa[v] = u;
        blackLCT.link(v, u);
        dfs(v);
    }
}

int main()
{
    n = read();
    for(int i = 1; i < n; ++i){
        int u = read(), v = read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n + 1; ++i){
        blackLCT.nd[i].allsize = whiteLCT.nd[i].allsize = 1;
    }
    dfs(1);
    treefa[1] = n + 1;
    blackLCT.link(1, n+1);

    m = read();
    for(int i = 1; i <= m; ++i){
        int op = read(), u = read();
        if(op == 0){
            int ans = blackLCT.nd[u].isBlack ? blackLCT.qBlackSize(u) : whiteLCT.qBlackSize(u);
            printf("%d\n", ans);
        } else {
            blackLCT.modify(u);
            whiteLCT.modify(u);
        }
    }
	return 0;
}
