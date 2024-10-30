#include <cstring>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 1000010;
char s[N], ss[N];
int p[N], f[N];
vector<int> hang[N];
// 设 f[i] 表示以 i 位置结尾有几个 beautiful 串
// 设以 i 位置结尾的最短偶回文串长度为 k，则有 f[i] = f[i-k] + 1
// 求 k 需要使用扫描线：从左往右扫描，遇到一个偶回文中心，就加入 set，
//                   在偶回文中心对应的极大回文右端点处将其移出 set，
//                   每次求以 i 结尾的最短偶回文串时，在 set 里取最靠后的偶回文中心
// 由于 manacher 引入了分隔符，实际处理时下标会有些许不同，注意处理

int manacher(){
	int l=strlen(s),len=0;
	ss[len++]='$';ss[len++]='#';
	for(int i=0;i<l;i++)
		ss[len++]=s[i],ss[len++]='#';
	ss[len]='\0';
	int mx=0,id,ans=-1;
	for(int i=1;i<len;i++){
		if(i<mx) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while(ss[i+p[i]]==ss[i-p[i]]) p[i]++;
		if(mx<i+p[i]) mx=i+p[i],id=i;
	}
    return len;
}

int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--){
        scanf("%d%s", &n, s);
        int len = manacher();
        long long ans = 0;
        set<int> pos;
        for(int i = 0; i < len; i++){
            if(ss[i] != '#') continue;
            if(!pos.empty()){
                int lst = *(--pos.end());
                f[i] = f[2 * lst - i] + 1;
                ans += f[i];
            }
            for(int x : hang[i]) pos.erase(x);
            hang[i].clear();
            if(p[i] > 1){
                pos.insert(i);
                hang[i + p[i] - 1].push_back(i);
            }
        }
        printf("%lld\n", ans);
        memset(f, 0, sizeof(int) * (len + 2));
    }
	return 0;
}
