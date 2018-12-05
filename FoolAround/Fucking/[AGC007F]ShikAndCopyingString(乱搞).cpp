#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	inline void reads(char *s)
	{
		char c=Get();int tot=0;
		while(c<'a'||c>'z') c=Get();
		while(c>='a'&&c<='z') s[++tot]=c,c=Get();
		s[++tot]='\0';
	}
}

inline void Falun_Dafa_is_good(const int &x){printf("%d\n",x);exit(0);}

const int N=1000010;
char S0[N],T[N];
int c[N];
vector<int> v[27];
deque<int> q;

int main()
{
	int n=IO::read(),tag=0,ans=0;
	IO::reads(S0);IO::reads(T);
	c[n+1]=n+1;
	if(strcmp(S0+1,T+1)==0) Falun_Dafa_is_good(0);
	if(n==1) Falun_Dafa_is_good(-1);
	for(int i=1;i<=n;i++) v[S0[i]-'a'].push_back(i);
    for(int i=n;i;i--)
    {
        if(T[i]==T[i+1]&&i>=c[i+1]){c[i]=c[i+1];continue;}
        else
        {
        	int x=T[i]-'a';
            while(!v[x].empty()&&v[x].back()>=c[i+1])
            {
                v[x].pop_back();
                if(v[x].empty()) Falun_Dafa_is_good(-1);
            }
            c[i]=v[x].back();
            if(i>=c[i+1])
            {
                tag++;
				q.push_front(c[i+1]-1+tag);
                while(q.back()-tag>=i) q.pop_back();
                q.push_back(i+tag);
            }
            else
			{
				while(!q.empty()) q.pop_back();
				if(c[i]<i) q.push_back(i+tag);
			}
            ans=max(ans,(int)q.size());
        }
    }
    printf("%d\n",ans);
    return 0;
}
