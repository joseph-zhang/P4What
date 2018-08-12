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
*    Prim演算法也可以求最小生成树,这个演算法仿效Dijkstra,也采用了贪心的思想.
*    以单顶点树T开始,贪心的选取T和其他顶点之间相连的最小权边,将其加入T中,不断进行.
*    和Dijkstra的差异:
*    (1)Dijkstra屡次找不在树上,离dijkstra树的根最近的點;Prim屢次找不在树上,离整棵树最近的點。
*    (2)Dijkstra選擇特定一點做為起點,得到不同的最短路徑樹;Prim選擇任意一點做為樹根,得到相同的最小生成樹.
*    程式的实现依然可以用priority_queue加速,O(ElogV).
*    也可以不采用优先队列,O(V^2).
*    因为Dijkstra的程式里我们用了优先队列,这里我们采用邻接矩阵来实现.假定图是连通的.
*/

const int maxn = 500;
int adj[maxn][maxn];
int d[maxn];
bool done[maxn];
int n,m;

int prim(){
	//初始化
	for(int i = 0;i < n;i++){
		done[i] = false;
		d[i] = 1e6; 
	}
	d[0] = 0; //选结点0作为起始树T
	int res = 0;
	for(;;){
		int u = -1;
		//找未加进T的所有结点中的最小者
		for(int i = 0;i < n;i++)
			if(!done[i]&&(u == -1 || d[i] < d[u]))u = i;
		if(u == -1)break; //没找到说明已经完成
		done[u] = true;
		res += d[u];
		//更新与u相连的点们所对应的值
		for(int i = 0;i < n;i++) d[i] = min(d[i],adj[u][i]);
	}
	return res;
}
int main(){
	//假设所有边权小于1e6
	cin >> n >> m;
	for(int i = 0;i < n;i++) fill(adj[i],adj[i]+n,1e6);
	printf("So your graph has %d edges and %d points.\nNow give these edges to me.\n",m,n);
	for(int i = 0;i < m;i++){
		int u,v,val;
		cin >> u >> v >> val;
		adj[u][v] = adj[v][u] = val;
	}
	printf("The MST value is: %d\n",prim());
	return 0;
}


