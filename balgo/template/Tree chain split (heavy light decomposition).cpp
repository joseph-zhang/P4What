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
*    树链剖分,是一种处理树的方法,将树给剖成一条条的链.
*    长链上有很好的演算法:線段樹,BIT,Sparse-Table,BST,Heap...可据此设计高效的演算法.
*    长链的一种划分的思想是"重轻分解",利用DFS/BFS遍历树,树上每個结点都連向其最大的子樹。
*    剖分之后可以轻易求得树上两点的LCA.
*    剖分:O(V);建立所有長鏈:O(VlogV);查詢LCA:O(logV);查詢一條路徑:O((logV)^2).
*    程式简单给出,以点的邻接表建树,假设根结点编号为0,遍历过程采用DFS.
*/

const int maxn = 10000;
vector<int> G[maxn]; // adjacency list,是一棵樹
int parent[maxn],heavy[maxn]; //各點的父親、最重孩子
int depth[maxn],cnt[maxn];    // 各點的深度、子樹的點數
int chain[maxn],head[maxn];  // 各點所属的链的编号、各点所属链的開頭结点编号
int n,m;

//Traversal过程遍历树,计算各个结点的要素parent,heavy,depth,size;
void DFS(int u){
	cnt[u] = 1;
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(v == parent[u])continue; //避免搜到老爹
		
		parent[v] = u;
		depth[v] = depth[u]+1;
		
		DFS(v);
		cnt[u] += cnt[v];
		if(heavy[u]==-1 || cnt[heavy[u]] < cnt[v])
			heavy[u] = v;
	}
}
//主控过程,找出树上的各条链,重轻分解
void heavyLight(){
	memset(heavy,-1,sizeof(heavy));
	memset(chain,-1,sizeof(chain));
	parent[0] = -1;
	depth[0] = 0;
	
	DFS(0);
	int c = 0; // 鏈的編號计数器
	for(int i = 0;i < n;i++){
		if(chain[i]!=-1)continue;
		if(parent[i]==-1 || i != heavy[parent[i]]){
		// 这说明i點是鏈的開頭结点
			for(int k = i;k != -1;k = heavy[k]){
				chain[k] = c;
				head[k] = i;
			}
			c++;
		}
	}
}

int lca(int u,int v){
	//每次选择 所属链头部较深的结点向上走,直到两结点处于同一条链为止.
	while(chain[u]!=chain[v]){
		if(depth[head[u]] > depth[head[v]]) u = parent[head[u]];
		else v = parent[head[v]];
	}
	return depth[u]<depth[v]?u:v;
}

int main(){
	printf("How many nodes and edges on your tree? ");
	cin >> n >> m;
	printf("Now give me your tree.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
	}
	printf("Constructing...\n");
	heavyLight();
	int qn;
	printf("LCA relationship between nodes:\n");
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			int res = lca(i,j);
			printf("%d %d->%d\n",i,j,res);
		}
	}
	return 0;
}