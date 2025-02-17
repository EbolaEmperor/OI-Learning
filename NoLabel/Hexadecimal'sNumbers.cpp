#include<iostream>
#include<cstdio>
using namespace std;

int n,cnt=0;

void find(int x)
{
	if(x>n) return;
	cnt++;
	find(10*x);
	find(10*x+1);
}

int main()
{
	cin>>n;
	find(1);
	cout<<cnt<<endl;
	return 0;
}
