#include<bits/stdc++.h>
using namespace std;

struct Triad
{
	int x,y,val;
	Triad(int _x=0,int _y=0,int _v=0):x(_x),y(_y),val(_v){}
};
struct SparseMatrix
{
	int n,nx,ny;
	Triad a[8000];
} A,B,C;
map<pair<int,int>,int> mat;

SparseMatrix operator * (const SparseMatrix &A,const SparseMatrix &B)
{
	mat.clear();
	for(int i=1;i<=A.n;i++)
		for(int j=1;j<=B.n;j++)
			if(A.a[i].y==B.a[j].x) mat[pair<int,int>(A.a[i].x,B.a[j].y)]+=A.a[i].val*B.a[j].val;
	C.n=0;C.nx=A.nx;C.ny=B.ny;
	for(int i=1;i<=C.nx;i++)
		for(int j=1;j<=C.ny;j++)
			if(mat.count(pair<int,int>(i,j))) C.a[++C.n]=Triad(i,j,mat[pair<int,int>(i,j)]);
	return C;
}

int main()
{
	cin>>A.n>>A.nx>>A.ny;
	for(int i=1;i<=A.n;i++)
		scanf("%d%d%d",&A.a[i].x,&A.a[i].y,&A.a[i].val);
	cin>>B.n>>B.nx>>B.ny;
	for(int i=1;i<=B.n;i++)
		scanf("%d%d%d",&B.a[i].x,&B.a[i].y,&B.a[i].val);
	C=A*B;
	cout<<C.n<<endl;
	for(int i=1;i<=C.n;i++)
		printf("%d %d %d\n",C.a[i].x,C.a[i].y,C.a[i].val);
	return 0;
}
