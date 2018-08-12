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
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/** 
*    EdmondsKarp 是 Ford-Fulkerson方法 的一种实现.
*    具体来说,对于Ford-Fulkerson方法中找增广路经这一环节,用BFS找最短的.
*    可以证明,沿最短s-t路增广,需要O(nm)次增广.
*    每次增广由BFS寻找增广路,需要O(m).总时间复杂度为O(n*m^2)
*    下列程式的实现采用边的邻接表(前向星),假设图是有向图.
*/
const int maxn = 50;//点数上限
const int maxm = 100<<1; //边数上限
struct Edge{
	int from,to;
	int cap,flow;
	Edge(){}
	Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
int r = 0; //结点分配计数器
Edge edges[maxm];
vector<int> G[maxn];//前向星结构
int p[maxn]; //记录搜到的最短增广路
void addEdge(int from,int to,int cap){
	edges[r++] = Edge(from,to,cap,0);
	G[from].push_back(r-1);
	edges[r++] = Edge(to,from,0,0);
	G[to].push_back(r-1);
}
int EDK(int s,int t){
	int flow = 0;
	int a[maxn];//a数组记录目前搜到的路径上从s到i的最小剩余
	for(;;){
		memset(a,0,sizeof(a));
		queue<int> que;
		que.push(s);a[s] = INF;
		while(!que.empty()){//实际上就是个BFS
			int x = que.front();que.pop();
			for(int i = 0;i < G[x].size();i++){
				Edge& e = edges[G[x][i]];
				if(!a[e.to] && e.cap > e.flow){ //!a[e.to]是为了查重
					que.push(e.to);
					a[e.to] = min(a[x],e.cap-e.flow);
					p[e.to] = G[x][i];
				}
			}
			if(a[t])break;//已找到完整的s-t增广路
		}	
		if(!a[t])break;//已经没有增广路径了
		for(int u = t;u!=s;u = edges[p[u]].from){
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
		}
		flow += a[t]; 
	}
	return flow;
}
int main(){
	freopen("input.txt","r",stdin);
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i = 0;i < m;i++){
			int u,v,c,f;
			scanf("%d%d%d",&u,&v,&c);
			addEdge(u,v,c);
		}
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			memset(p,0,sizeof(p));
			int s,t;scanf("%d%d",&s,&t);
			printf("%d\n",EDK(s,t));
		}
	}
	return 0;
}

