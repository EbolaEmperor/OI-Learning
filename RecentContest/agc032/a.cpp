#include<bits/stdc++.h>
using namespace std;

const int N=105;
int n,a[N],b[N];
bool del[N];
vector<int> v;

int main()
{
    cin>>n;
	for(int i=1;i<=n;i++)
	{
        scanf("%d",&a[i]);b[i]=i;
		if(a[i]>i) return puts("-1"),0;
	}
	while(v.size()<n)
	{
        bool flag=0;
		for(int i=n;i>=1;i--)
            if(!del[i]&&a[i]==b[i])
            {
                del[i]=1;flag=1;
                v.emplace_back(a[i]);
                for(int j=i+1;j<=n;j++) b[j]--;
                break;
            }
		if(!flag) return puts("-1"),0;
	}
	reverse(v.begin(),v.end());
	for(auto x : v) printf("%d\n",x);
	return 0;
}