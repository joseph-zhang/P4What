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
*    Dijkstra是经典的最短路演算法,可用于正权图.
*    思想是贪心的(贪心的前提是没有负权),按照状态空间搜寻的想法,可以理解成考虑权重的BFS.
*    贪心思想: 每次d[i]的最小者都是最短距离已被确定的点,因为图上没有负权,所以之后它不可能更小了.
*    实作时可以用优先队列加速: O(ElogV)
*    如果边数非常巨大,也可以用邻接矩阵基于线性查找的dijkstra: O(V^2)
*    下面的程式采用了优先队列加速的形式.
*/

const int maxn = 50;
const int maxm = 100<<1;
struct Edge{
	int from,to;
	int len;
	int nxt;
	Edge(){}
	Edge(int u,int v,int l,int f):from(u),to(v),len(l),nxt(f){}
};
//注意STL的priority_queue 是大根堆,可以理解成优先级
struct heapNode{
	int u,relx;//relx是松弛量,记录当前阶段下结点u离s点的最短距离
	heapNode(){}
	heapNode(int u_,int relx_):u(u_),relx(relx_){}
	bool operator < (const heapNode& rhs)const{
		return relx > rhs.relx;
	} 
};
Edge edges[maxm];
int d[maxn],p[maxn]; //d是距离数组,p记录了Dijkstra树的结点关系
int head[maxn]; //前向星表头
int r,n,m;
void addEdge(int u,int v,int len){ //这里写的是无向图，可以根据题意调整 
	edges[r++] = Edge(u,v,len,head[u]);
	head[u] = r-1;
	edges[r++] = Edge(v,u,len,head[v]);
	head[v] = r-1;
}
void Dijkstra(int s){
	bool done[maxn];//记录各点是否已经在Dijkstra树中
	memset(done,false,sizeof(done));
	for(int i = 0;i < n;i++)p[i] = i;
	for(int i = 0;i < n;i++)d[i] = INF; //初始化(适用于求最短路)
	priority_queue<heapNode> pque;
	d[s] = 0;pque.push(heapNode(s,0));
	while(!pque.empty()){
		heapNode node = pque.top();pque.pop(); //每次挑出松弛量最小者加入Dijkstra树
		int u = node.u;
		if(done[u])continue;
		//if(done[t])break;
		done[u] = true;
		for(int i = head[u];i!=-1;i = edges[i].nxt){
			Edge& e = edges[i];
			if(d[e.to]>d[u]+e.len){ //松弛！
				d[e.to] = d[u]+e.len;
				p[e.to] = u;
				pque.push(heapNode(e.to,d[e.to]));
			}
		}
	}
}
void printPath(int s,int cur){
	if(cur == s){cout << s;return;}
	printPath(s,p[cur]);
	printf(" %d",cur);
}
int main(){
	freopen("input.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		r = 0;memset(head,-1,sizeof(head));
		for(int i = 0;i < m;i++){
			int u,v,l;
			scanf("%d%d%d",&u,&v,&l);
			addEdge(u,v,l);
		}
		Dijkstra(0);//构造Dijkstra树
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			int t;scanf("%d",&t);
			printPath(0,t);cout << endl;
			printf("%d\n",d[t]);
		}
	}
	return 0;
}

