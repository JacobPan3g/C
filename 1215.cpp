#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

struct Node
{
	int pX, pY;
	int hX, hY;
	int step;
};

bool vis[20][20][20][20];

int main()
{
freopen( "input.txt","r",stdin );
freopen( "output.txt","w",stdout );

	int n, m;
	char map[20][20];
	char pWay[4] = {'N','S', 'W', 'E'};
	char hWay[4];
	int pDis[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	int hDis[4][2];
	Node fro, rear;
	queue<Node> q;	

	// 记录地图，并记录H和P的位置
	cin >> n >> m;
	for ( int i = 0; i < n; i++ )
		for ( int j = 0; j < m; j++ )
		{
			cin >> map[i][j];
			if ( map[i][j] == 'P' )
			{
				fro.pX = i;
				fro.pY = j;
			}
			if ( map[i][j] == 'H' )
			{
				fro.hX = i;
				fro.hY = j;
			}
		}

	// 把第一个节点入队
	fro.step = 0;
	q.push( fro );
	vis[fro.pX][fro.pY][fro.hX][fro.hY] = true;
	
	cin >> hWay;
	// 设置H的方向数组
	for ( int i = 0; i < 4; i++ )
		for ( int j = 0; j < 4; j++ )
			if ( hWay[i] == pWay[j] )
			{
				hDis[i][0] = pDis[j][0];
				hDis[i][1] = pDis[j][1];
			}
	
	bool ok = false;
	int tmpPx, tmpPy;
	int tmpHx, tmpHy;
	while ( !ok && !q.empty() && q.front().step < 255 )
	{
		fro = q.front();
		q.pop();
		for ( int i = 0; i < 4; i++ )
		{
			tmpPx = fro.pX + pDis[i][0];
			tmpPy = fro.pY + pDis[i][1];
			tmpHx = fro.hX + hDis[i][0];
			tmpHy = fro.hY + hDis[i][1];
			
			// P不会往岩石和溶浆里走，同时也不用让H往溶浆里走
			if ( map[tmpPx][tmpPy] == '#' || map[tmpPx][tmpPy] == '!' || map[tmpHx][tmpHy] == '!' )
				continue;
			// 如何H碰到岩石，停在原地不动
			if ( map[tmpHx][tmpHy] == '#' )
			{
				tmpHx = fro.hX;
				tmpHy = fro.hY;
			}

			if ( vis[tmpPx][tmpPy][tmpHx][tmpHy] )
				continue;
			
			// 判断是否相遇，这里在展开处就判断
			if ( (tmpPx == tmpHx && tmpPy == tmpHy) 
					|| (fro.pX == tmpHx && fro.pY == tmpHy) && (fro.hX == tmpPx && fro.hY == tmpPy) )
			{
				cout << fro.step + 1 << endl; 
				ok = true;
				break;
			}

			// 做标记，并放进队尾
			vis[tmpPx][tmpPy][tmpHx][tmpHy] = true;
			rear.step = fro.step + 1;
			rear.pX = tmpPx;
			rear.pY = tmpPy;
			rear.hX = tmpHx;
			rear.hY = tmpHy;
			q.push(rear);
				
		}
	}

	if ( !ok )
		cout << "Impossible" << endl;

	return 0;
}
