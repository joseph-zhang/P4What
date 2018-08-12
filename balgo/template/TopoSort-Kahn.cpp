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
*    拓扑排序理论上讲就是从偏序构造相容的全序.
*    给定偏序集,可能有许多种拓扑排序.只要不违背图上每一条边的先后規定,要怎麼排列图上的點都行。
*    當圖上有圈，拓樸順序就不存在.
*    下面的程式实现了拓扑排序的Kahn演算法.
*    实现时优先删除入度为零的点,实际也可以根据问题自行设计边的方向。
*/

bool adj[20][20];	// adjacency matrix
int ref[20];		//记录各点的入度
void topological_ordering(int n)
{
	memset(ref,0,sizeof(ref));
	// 统计入度信息(可以在建图时就完成)
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			if (adj[i][j]) ref[j]++;
	// 開始找出一個合理的排列順序
	for (int i=0; i<n; ++i){
		// 尋找入度为零的点
		int s = 0;
		while (s < n && ref[s] != 0) ++s;
		if (s == n) break;	// 找不到,表示目前殘存的圖有圈。
		ref[s] = -1;		// 設為已找過（刪去s點）
		cout << s;			// 印出合理的排列順序的第i點
		// 更新ref的值（刪去由s點連出去的邊）
		for (int t=0; t<n; ++t)
			if (adj[s][t]) ref[t]--;
	}
}
int main(){
	printf("How many nodes on DAG?(<9) ");
	int n;cin >> n;
	printf("how many edges? ");
	int m;cin >> m;
	printf("Now give me adjacency relationship.\n");
	memset(adj,false,sizeof(adj));
	for(int i = 0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		adj[u][v] = true;
	}
	topological_ordering(n);
	return 0;
}
