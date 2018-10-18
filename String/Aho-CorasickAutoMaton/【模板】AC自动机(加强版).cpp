#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

int n;
char s[1000005];
int val[500010],f[500010];
int ch[500010][26];
int sz=0;
struct Result
{
	char s[100];
	int order;
	int cnt;
} result[160];
bool operator < (Result a,Result b)
{
	if(a.cnt!=b.cnt)
		return a.cnt>b.cnt;
	else
		return a.order<b.order;
}

void insert(char* s,int id)
{
    int u=0,len=strlen(s);
    for(int i=0;i<len;i++)
    {
        int idx=s[i]-'a';
        if(ch[u][idx]==0)
        {
            sz++;
            memset(ch[sz],0,sizeof(ch[sz]));
            ch[u][idx]=sz;
        }
        u=ch[u][idx];
    }
    val[u]=id;
}

void GetFail()
{
    queue<int> q;
    f[0]=0;
    for(int c=0;c<26;c++)
    {
        int u=ch[0][c];
        if(u!=0) f[u]=0,q.push(u);
    }
    while(!q.empty())
    {
        int o=q.front();
        for(int c=0;c<26;c++)
        {
            int u=ch[o][c];
            if(u==0) continue;
            q.push(u);
            int v=f[o];
            while(v!=0&&ch[v][c]==0) v=f[v];
            f[u]=ch[v][c];
        }
        q.pop();
    }
}

void search()
{
    int n=strlen(s);
    int p=0;
    for(int i=0;i<n;i++)
    {
        int idx=s[i]-'a';
        while(p!=0&&ch[p][idx]==0) p=f[p];
        p=ch[p][idx];
        if(val[p]>0||val[f[p]]>0)
        {
            int q=p;
            result[val[p]].cnt++;
            while(f[q]!=0)
            {
                q=f[q];
                if(val[q]>0) result[val[q]].cnt++;
            }
        }
    }
}

int main()
{
	while(true)
	{
		memset(val,0,sizeof(val));
		memset(ch,0,sizeof(ch));
		memset(f,0,sizeof(f));
		sz=0;
		scanf("%d",&n);
		if(n==0) break;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",result[i].s);
			insert(result[i].s,i);
			result[i].cnt=0;
			result[i].order=i;
		}
		GetFail();
		scanf("%s",s);
		search();
		sort(result+1,result+1+n);
		cout<<result[1].cnt<<endl;
		for(int i=1;i<=n;i++)
			if(result[i].cnt==result[1].cnt) printf("%s\n",result[i].s);
	}
    return 0;
}
