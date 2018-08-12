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
*    ISAP演算法,可用于求最大流.首次出现在 Ahuja 和 Orlin 的教材中.
*    定义数组d[i],表示剩余网络中节点i到汇点t距离的下界,在增广过程中会不断被修正.
*    称满足 d[i]=d[j]+1 的弧 i->j 为"允许弧".增广的时候只允许沿着允许弧走,必然有：
*        (1)d[t] = 0;
*        (2)在剩余网络上对任意弧(i,j),满足 d[i]<=d[j]+1;
*        (3)当 d[s]>=n 时,剩余网络中不存在s-t路.
*    ISAP 的思想很简单:找增广路的过程就是从源点s沿着"允许弧"往前走(Advance).
*    如果在走的过程中走不动了,往回走一步,做下述修正:
*        (1)在从结点i往回走的时候,修正d[i]为 d[i]= min{d[j]|(i,j)是剩余网络中的弧}+1 (Retreat).
*        (2)若从i出发没有弧,则设置 d[i]=n.
*    具体的实现中有一些技巧:
*        (1)使用"当前弧"来加速"允许弧"的查找.
*           "当前弧"结构:cur[i] 是从结点i出发前行时,从i出发的所有的弧的走动记录.
*        (2)使用num[i]数组优化:下标i是距离,值是满足d[k]=i的点的个数.
*           当一个结点的距离标号从x改到y时,num[x]减1,num[y]加1,然后检查num[x]是否为零/
*           若为零,说明s,t不连通,算法终止.(这叫gap优化)
*        (3)可以使用BFS找出d[]的初始值.(从t开始进行逆向BFS)
*           也可以将d[i]初始值全设为零.
*           单次执行ISAP效率相差不大,但若是多次求解小规模网络流,先用BFS处理效率有明显提升.
*/
struct Edge{
	int from,to,cap,flow;
	Edge(){}
	Edge(int from_,int to_,int cap_,int flow_):
			from(from_),to(to_),cap(cap_),flow(flow_){}
};

const int maxn = 100;
const int maxm = 10000;
int n,m;
int p[maxn]; //记录增广路
int num[maxn];//距离标号计数
int d[maxn]; //定义的距离数组d
int cur[maxn]; //当前弧结构
bool vis[maxn];//BFS查重用
Edge edges[maxm];
vector<int> G[maxn];
int r; //节点分配计数器
void addEdge(int from,int to,int cap){
	edges[r++] = Edge(from,to,cap,0);
	G[from].push_back(r-1);
	edges[r++] = Edge(to,from,0,0);
	G[to].push_back(r-1);
}
//BFS过程,算出d[i]初始值
void BFS(int s,int t){
	memset(vis,false,sizeof(vis));
	queue<int> que;
	que.push(t);
	vis[t] = true;
	d[t] = 0;
	while(!que.empty()){
		int x = que.front();que.pop();
		for(int i = 0;i < G[x].size();i++){
			Edge& e = edges[G[x][i]];
			if(!vis[e.to]){
				d[e.to] = d[x]+1;
				vis[e.to] = true;
			}
		}
	}
}
//增广过程
int Augment(int s,int t){
	int x = t,a = INF;
	//倒着回去算出增广值a
	while(x!=s){
		Edge& e = edges[p[x]];
		a = min(a,e.cap-e.flow);
		x = edges[p[x]].from;
	}
	x = t;
	//再倒着来一遍进行增广
	while(x!=s){
		edges[p[x]].flow += a;
		edges[p[x]^1].flow -= a;
		x = edges[p[x]].from;
	}
	return a;
}

//主控过程
int Maxflow(int s,int t){
	BFS(s,t);        //用逆向BFS算出d[]的初始值
	int flow = 0;
	memset(num,0,sizeof(num));
	for(int i = 0;i < n;i++)num[d[i]]++;
	int x = s;    //从源点s开始
	memset(cur,0,sizeof(cur));
	//从当前结点x走起,根据情况前进后退,遇到汇点t时就可以进行增广
	while(d[s]<n){
		if(x==t){ //走到了t,进行增广
			flow+=Augment(s,t);
			x = s;
		}
		bool ok = false;
		for(int i = cur[x];i < G[x].size();i++){
			Edge& e = edges[G[x][i]];
			if(e.cap > e.flow && d[x]==d[e.to]+1 ){ //沿着允许弧走
				ok = true;
				p[e.to] = G[x][i];
				cur[x] = i;
				x = e.to;
				break;
			}
		}
		if(!ok){ //若发现走不动了,从x 进行Retreat
			int k = n-1;
			for(int i = 0;i < G[x].size();i++){
				Edge& e = edges[G[x][i]];
				if(e.cap > e.flow) k = min(k,d[e.to]); //找min{d[j]|(x,j)是剩余网络中的弧}
			}
			if(--num[d[x]] == 0)break; //gap优化
			num[d[x] = k+1]++;        //d[x]= min{d[j]|(x,j)是剩余网络中的弧}+1 
			cur[x] = 0;
			if(x!=s) x = edges[p[x]].from; //回走一步
		}
	}
	return flow;
}
int main(){
	freopen("input.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i = 0;i < m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			addEdge(u,v,c);
		}
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			memset(p,0,sizeof(p));
			int s,t;scanf("%d%d",&s,&t);
			printf("%d\n",Maxflow(s,t));
		}
	}
	return 0;
}
