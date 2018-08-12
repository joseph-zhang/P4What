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
*    DFS返回的順序顛倒之後,正好就是拓撲順序。
*    DFS执行中每次返回上一层时都会有节点被加入合理的拓扑顺序中。
*    建图结构是邻接矩阵. 
*/
bool adj[9][9];		// adjacency matrix
int visit[9];		// 访问记录
int order[9];
int r,n;	        //r是分配器 
bool cycle;			// 記錄DFS的過程中是否偵測到圈

void DFS(int s){
	// back edge，有圈。
	if (visit[s] == 1) {cycle = true; return;}
	// forward edge、cross edge。
	if (visit[s] == 2) return;
	visit[s] = 1;
	for (int t=0; t<n; ++t)
		if (adj[s][t]) DFS(t);
	visit[s] = 2;
	order[r--] = s;		// 倒着记录就可以得到需要的topo序
}

void topological_ordering(){
	memset(visit,0,sizeof(visit));
	cycle = false;
	r = n-1;
	// 進行DFS,首次进入标1,返回时标2
	for (int s=0; s<n ; ++s)
		if (!visit[s]) DFS(s);
	// 輸出結果
	if (cycle) cout << "圖上有圈";
	else{
		for (int i=0; i<9; ++i)
			cout << order[i];
	}
}

int main(){
	printf("How many nodes on DAG?(<9) ");
	cin >> n;
	printf("how many edges? ");
	int m;cin >> m;
	printf("Now give me adjacency relationship.\n");
	memset(adj,false,sizeof(adj));
	for(int i = 0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		adj[u][v] = true;
	}
	topological_ordering();
	return 0;
}
