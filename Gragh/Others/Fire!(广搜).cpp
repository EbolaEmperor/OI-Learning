#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct XY
{
	int x,y;
	XY(int _x=0,int _y=0):x(_x),y(_y){}
};
char map[1005][1005];
int deep[1005][1005];

void read(char &c)
{
	char ch=getchar();
	while(ch!='F'&&ch!='#'&&ch!='.'&&ch!='J') ch=getchar();
	c=ch;
}

int main()
{
	int T;
	for(cin>>T;T;T--)
	{
		int r,c;
		XY tmp;
		scanf("%d%d",&r,&c);
		queue<XY> q;
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
				deep[i][j]=0x3fffffff;
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
			{
				read(map[i][j]);
				if(map[i][j]=='F') q.push(XY(i,j)),deep[i][j]=1;
				if(map[i][j]=='J') tmp=XY(i,j),deep[i][j]=1;
			}
		q.push(tmp);
		while(!q.empty())
		{
			XY o=q.front();
			char ch=map[o.x][o.y];
			if(o.x>1&&map[o.x-1][o.y]=='.') q.push(XY(o.x-1,o.y)),deep[o.x-1][o.y]=deep[o.x][o.y]+1,map[o.x-1][o.y]=ch;
			if(o.x<r&&map[o.x+1][o.y]=='.') q.push(XY(o.x+1,o.y)),deep[o.x+1][o.y]=deep[o.x][o.y]+1,map[o.x+1][o.y]=ch;
			if(o.y>1&&map[o.x][o.y-1]=='.') q.push(XY(o.x,o.y-1)),deep[o.x][o.y-1]=deep[o.x][o.y]+1,map[o.x][o.y-1]=ch;
			if(o.y<c&&map[o.x][o.y+1]=='.') q.push(XY(o.x,o.y+1)),deep[o.x][o.y+1]=deep[o.x][o.y]+1,map[o.x][o.y+1]=ch;
			q.pop();
		}
		int ans=0x3fffffff;
		for(int i=1;i<=r;i++)
		{
			if(map[i][1]=='J') ans=min(ans,deep[i][1]);
			if(map[i][c]=='J') ans=min(ans,deep[i][c]);
		}
		for(int i=1;i<=c;i++)
		{
			if(map[1][i]=='J') ans=min(ans,deep[1][i]);
			if(map[r][i]=='J') ans=min(ans,deep[r][i]);
		}
		if(ans==0x3fffffff) puts("IMPOSSIBLE");
		else printf("%d\n",ans);
	}
	return 0;
}
