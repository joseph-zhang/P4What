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
*    树上的两结点有LCA,可以利用RMQ或树链剖分来求,也可以用LCA的Tarjan演算法.
*    RMQ和树链剖分的方法在另一个文档里,这里我们看Tarjan(和SCC的Tarjan不是一个东西).
*    具体的思想是:利用DFS序,将已拜访过的点按照层级聚合起来.构成并查集森林(Disjoint-set Forest),
*    下列程式简单的描述了演算法思想,利用点的邻接表建图并假设树根节点编号为0.
*/

const int maxn = 200;
int lca[maxn][maxn]; // 所有兩點之間的LCA
bool vis[maxn];   // DFS當下已經拜訪過的點
int p[maxn];    //并查集用
vector<int> vislog;  //记录那些结点已经拜访过
vector<int> G[maxn]; 
int n,m;

void init(){
	for(int i = 0;i < n;i++)p[i] = i;
	memset(vis,false,sizeof(vis));
}
int find(int x){ return x == p[x]?x:(p[x] = find(p[x]));}
void DFS(int x){
	if(vis[x]) return;
	else vis[x] = true;
	vislog.push_back(x);
	
	for(int i = 0;i < vislog.size();i++){
		int v = vislog[i];
		lca[x][v] = lca[v][x] = find(v); // 計算LCA
		// cout << x << " " << v <<"->" << lca[x][v] << endl;  
	}
	for(int i = 0;i < G[x].size();i++){
		DFS(G[x][i]);
		p[G[x][i]] = x;  // union(y, x)，並讓x是樹根。
	}
}
int main(){
	int t,u,v;
	printf("how many nodes and edges on your tree? ");
	scanf("%d%d",&n,&m);
	cout << "give me your tree.(0 is root)\n";
	for(int i = 0;i < m;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}
	printf("Constructing...\n");
	init();
	DFS(0);
	printf("How many query times? ");
	scanf("%d",&t);
	printf("Now input your query:\n");
	while(t--){
		cin >> u >> v;
		cout << lca[u][v] << endl;
	}
	return 0;
}

