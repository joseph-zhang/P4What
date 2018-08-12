#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    KM(kuhn-munkres)演算法,可求出一張二分圖的最大（小）權完美二分匹配。
*    稍做修改，也能用來求出最大（小）權最大二分匹配、最大（小）權二分匹配。
*    KM应用了Hungarian,建立V次交錯樹。
*/
const int xmax = 50;
const int ymax = 50; 
int X;	// X的點數
int Y;	// Y的點數
int adj[xmax][ymax];		// 精簡過的adjacency matrix
int lx[xmax], ly[ymax];	// 可行顶点标号
int mx[xmax], my[ymax];	// X各點的配對對象、Y各點的配對對象
int q[xmax], *qf, *qb;	// BFS queue
int p[xmax];			// BFS parent，交錯樹之偶點，指向上一個偶點
bool vx[xmax], vy[ymax];	// 記錄是否在交錯樹上
int dy[ymax], pdy[ymax];	// DP表格,记录最小差值

// relaxation
void relax(int x)
{
	for (int y=0; y<Y; ++y)
		if (adj[x][y] != 1e9)
			if (lx[x] + ly[y] - adj[x][y] < dy[y])
			{
				dy[y] = lx[x] + ly[y] - adj[x][y];
				pdy[y] = x;	// 記錄好是從哪個樹葉連出去的
			}
}

// 調整交錯樹上的label、調整DP表格
void reweight()
{
	int d = 1e9;
	for (int y=0; y<Y; ++y) if (!vy[y]) d = min(d, dy[y]);
	for (int x=0; x<X; ++x) if ( vx[x]) lx[x] -= d;
	for (int y=0; y<Y; ++y) if ( vy[y]) ly[y] += d;
	for (int y=0; y<Y; ++y) if (!vy[y]) dy[y] -= d;
}

// 擴充路徑
void augment(int x, int y)
{
	for (int ty; x != -1; x = p[x], y = ty)
	{
		ty = mx[x]; my[y] = x; mx[x] = y;
	}
}

// 延展交錯樹：使用既有的等邊
bool branch1()
{
	while (qf < qb){
		for (int x=*qf++, y=0; y<Y; ++y)
			if (!vy[y] && lx[x] + ly[y] == adj[x][y])
			{
				vy[y] = true;
				if (my[y] == -1)
				{
					augment(x, y);
					return true;
				}

				int z = my[y];
				*qb++ = z; p[z] = x; vx[z] = true; relax(z);
			}
	}
	return false;
}

// 延展交錯樹：使用新添的等邊
bool branch2()
{
	for (int y=0; y<Y; ++y)
	{
		if (!vy[y] && dy[y] == 0)
		{
			vy[y] = true;
			if (my[y] == -1)
			{
				augment(pdy[y], y);
				return true;
			}

			int z = my[y];
			*qb++ = z; p[z] = pdy[y]; vx[z] = true; relax(z);
		}
	}
	return false;
}

int KM()
{
	// 初始化vertex labeling
//	memset(lx, 0, sizeof(lx));	// 任意值皆可
	memset(ly, 0, sizeof(ly));
	for (int x=0; x<X; ++x)
		for (int y=0; y<Y; ++y)
			lx[x] = max(lx[x], adj[x][y]);

	// X側每一個點，分別建立「等邊」交錯樹。
	memset(mx, -1, sizeof(mx));
	memset(my, -1, sizeof(my));
	for (int x=0; x<X; ++x)
	{
		memset(vx, false, sizeof(vx));
		memset(vy, false, sizeof(vy));
		memset(dy, 0x7f, sizeof(dy));
		qf = qb = q;
		*qb++ = x; p[x] = -1; vx[x] = true; relax(x);
		while (true)
		{
			if (branch1()) break;
			reweight();
			if (branch2()) break;
		}
	}

	// 計算最大權完美匹配的權重
	int weight = 0;
	for (int x=0; x<X; ++x)
		weight += adj[x][mx[x]];
	return weight;
}

int main(){
	int m;
	while(cin >> X >> Y >> m){
		for(int i = 0;i < X;i++)fill(adj[i],adj[i]+Y,-1e9);
		for(int i = 0;i < m;i++){
			int x,y,val;
			cin >> x >> y >> val;
			adj[x][y] = val;
		}
		cout << KM() << endl;
		for(int i = 0;i < X;i++) cout << mx[i] << " ";
		cout << endl;
		for(int i = 0;i < Y;i++) cout << my[i] << " ";
	}
	return 0;
}




 
