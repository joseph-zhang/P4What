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
*    桥和关节点(割顶)是无向图中的重要结构,以下讨论假定图是连通的.
*    找割顶和桥的方法基本一致,可以同时进行,方法是利用DFS序,对无向图进行DFS.
*    (注意:反向边要走,但是注意不要过去了)
*    判断结点u是不是割顶:
*        (1)u不是根:对于从u连出去的子树们,只要有一个子树没有连向u祖先的反向边,u就是割顶.
*           (也就是说,如果u的子树们都有连向u祖先的反向边,u就不是割顶)
*        (2)u是根:比较简单,要是u有不止一个孩子,u就是割顶. 
*    定义pre和post:pre(u)是dfs首次发现u时的时间戳,post(u)是dfs返回u时的时间戳.
*    定义low值:low(u)是u能追溯到的最早被dfs发现的它祖先的pre值.
*    如此一来,对于非根节点u,u是割顶当且仅当存在u的子节点v,low(v)>=low(u);
*    在找割顶时可以顺手找桥,对于low(v)>low(u),桥就是边(u,v),其中u是割顶;
*    (注意如果有重边,将其中一条作为树边,其余都当做反向边)
*    下述程式建图结构是前向星,假定没有重边.
*/
struct Edge{
	int u,v;
	Edge(){}
	Edge(int u_,int v_):u(u_),v(v_){}
};
const int maxn = 200;
const int maxm = 1000;
int n,m;
int pre[maxn];  //访问时的时间
bool iscut[maxn];//是不是割顶(关节点)
bool isbridge[maxm];//是不是桥
int dfs_clock;  //深搜时间戳
int low[maxn];  
int ei;        //边计数分配器
Edge edges[maxm];
vector<int> G[maxn];


//深搜过程,将子树上的low值都算出来.
int dfs(int u,int fa){
	int lowu = pre[u] = ++dfs_clock;//记录时间
	int child = 0;
	for(int i = 0;i < G[u].size();i++){
		Edge& e = edges[G[u][i]];
		int v = e.v;
		if(!pre[v]){
			child++;
			int lowv = dfs(v,u);
			lowu = min(lowu,lowv); //尝试更新low(u)
			if(lowv >= pre[u])iscut[u] = true;
			if(lowv > pre[u])isbridge[G[u][i]] = true;
		}else if(pre[v] < pre[u] && v != fa)lowu = min(lowu,pre[v]);//反向边只走,不过去
	}
	if(fa < 0 && child == 1)iscut[u] = false; //处理整树的根的情况
	low[u] = lowu;
	return lowu;
}

void findBridge(){
	//初始化
	memset(pre,0,sizeof(pre));
	memset(iscut,false,sizeof(iscut));
	memset(isbridge,false,sizeof(isbridge));
	dfs_clock = 0;
	//尝试从每个点开始找
	for(int i = 0;i < n;i++)
		if(!pre[i])dfs(i,-1);
}

void addEdge(int u,int v){
	edges[ei++] = Edge(u,v);
	G[u].push_back(ei-1);
	edges[ei++] = Edge(v,u);
	G[v].push_back(ei-1);
}
int main(){
	ei = 0;
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your graph.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		addEdge(u,v);
	}
	printf("finding...\n");
	findBridge();
	printf("articulation vertex sequence:\n");
	for(int i = 0;i < n;i++)if(iscut[i])cout << i << " ";
	cout << endl;
	printf("Bridge sequence:\n");
	for(int i = 0;i < (m<<1);i++)
		if(isbridge[i])printf("(%d,%d)\n",edges[i].u,edges[i].v);
	return 0;
}
