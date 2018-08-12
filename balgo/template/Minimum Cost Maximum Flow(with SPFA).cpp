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
*    最小费用最大s-t流,在网络流的基础上,为每个管道(边)再附加上"每单位流量的费用"这一权重.
*    最大流的Edmonds-Karp利用BFS找最短路然后增广,但是现在的问题是边上又有权重.
*    所以我们发展Edmonds-Karp的方法,用SPFA找最短路然后增广,即可实现最小费用最大s-t流.
*    将此新方法称为Successive Shortest Path Algorithm.
*    测试程式以前向星建图,因而可以处理重边的情况,这在最小费用流问题中经常遇到.\
*    假设图上无负圈.
*/

struct Edge{
	int from,to,cap,flow,cost;
	Edge(){}
	Edge(int from_,int to_,int cap_,int flow_,int cost_):
		from(from_),to(to_),cap(cap_),flow(flow_),cost(cost_){};
};
int n,m;
const int maxn = 100;
const int maxm = 10000;
int d[maxn];
int p[maxn];//记录增广的路径上到达该点的上一条弧
int a[maxn];//记录从该点到s点的最小剩余容量,以备增广
bool inq[maxn];
vector<int> G[maxn];
Edge edges[maxm];
int r = 0;//边增加计数器
//进行一次增广.找到最短s-t路返回true,否则返回false
bool SPFA(int s,int t,int& flow,int& cost){
	fill(d,d+n,INF);
	memset(inq,false,sizeof(inq));
	d[s] = 0;inq[s] = true;p[s] = 0;a[s] = INF;
	queue<int> que;
	que.push(s);
	
	while(!que.empty()){
		int u = que.front();que.pop();inq[u] = false;
		for(int i = 0;i < G[u].size();i++){
			Edge& e = edges[G[u][i]];
			//在剩余网络上进行松弛
			if(e.cap > e.flow && d[e.to] > d[u]+e.cost){
				d[e.to] = d[u]+e.cost;
				p[e.to] = G[u][i];
				a[e.to] = min(a[u],e.cap-e.flow);
				if(!inq[e.to]){que.push(e.to);inq[e.to] = true;}
			}
		}
	}
	if(d[t] == INF) return false;//s-t不连通
	flow += a[t];
	cost += d[t]*a[t];
	int u = t;
	while(u!=s){
		edges[p[u]].flow += a[t];
		edges[p[u]^1].flow -= a[t];
		u = edges[p[u]].from;
	}
	return true;
}
//以参数的形式返回flow和cost的结果
void MCMF(int s,int t,int& flow,int& cost){
	flow = cost = 0;
	while(SPFA(s,t,flow,cost));
}
void addEdges(int from,int to,int cap,int cost){
	edges[r++] = Edge(from,to,cap,0,cost);
	G[from].push_back(r-1);
	edges[r++] = Edge(to,from,0,0,-cost);
	G[to].push_back(r-1);
}

int main(){
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your network.\n");
	r = 0;
	for(int i = 0;i < n;i++)G[i].clear();
	for(int i = 0;i < m;i++){
		int u,v,cap,cost;
		scanf("%d%d%d%d",&u,&v,&cap,&cost);
		addEdges(u,v,cap,cost);
	}
	int s,t,flow,cost;
	printf("s and t? ");
	scanf("%d%d",&s,&t);
	MCMF(s,t,flow,cost);
	printf("max-flow is %d,and mini-cost is %d",flow,cost);
	return 0;
}
