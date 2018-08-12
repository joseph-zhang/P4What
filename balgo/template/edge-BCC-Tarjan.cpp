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
*    边-双连通分量(简称桥连通分量Bridge-connected Component),是无向图边-双连通的极大子图
*    边-双连通:内部没有桥.
*    除了桥不属于任何边-双连通分量之外,其他每条边都恰好属于一个边-双连通分量.
*    桥连通分量之间没有公共结点,因而求起来比起双连通分量更简单些,简单来说就是找桥.
*    (实际上找桥和找关节点是同一个演算法,因而这个也是Tarjan的方法)
*    因为暂存的是点还没有公共结点,这个实现和SCC的Tarjan就更像了,用一个栈保存"当前边-BCC"中的点.
*    找完桥连通分量也可以像SCC那样进行缩点,因为没有公共点嘛.
*    下述实现的程式以点的邻接表建图.
*/

const int maxn = 200;
const int maxm = 1000;
int n,m;
int pre[maxn];  //访问时的时间
int bccno[maxn];//属于哪个边-BCC
int dfs_clock;  //深搜时间戳
int low[maxn];
int bcc_cnt;    //边-BCC计数分配器(从1开始编号)
vector<int> G[maxn],bcc[maxn];
stack<int> stk;//暂存点的栈

//深搜过程,和找SCC的很像
int dfs(int u,int fa){
	low[u] = pre[u] = ++dfs_clock;
	stk.push(u);
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(!pre[v]){
			dfs(v,u);
			low[u] = min(low[u],low[v]);
		}else if(v!=fa && !bccno[v]){
			low[u] = min(low[u],pre[v]);
		}
	}
	if(pre[u] == low[u]){
		bcc[++bcc_cnt].clear();
		int x;
		do{
			x = stk.top();stk.pop();
			bcc[bcc_cnt].push_back(x);
			bccno[x] = bcc_cnt;
		}while(x!=u);
	}
}
//主控过程
void Tarjan(){
	//初始化
	memset(pre,0,sizeof(pre));
	memset(bccno,0,sizeof(bccno));
	bcc_cnt = dfs_clock = 0;
	//找边-BCC
	for(int i = 0;i < n;i++)
		if(!pre[i])dfs(i,-1);
}
int main(){
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your graph.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	printf("finding...\n");
	Tarjan();
	printf("The Bridge-connected Component are showed below.\n");
	for(int i = 1;i <= bcc_cnt;i++){
		cout << "BCC#" << i << endl;
		for(int j = 0;j < bcc[i].size();j++)
			cout << bcc[i][j] << " ";
		cout << endl;
	}
	return 0;
}
