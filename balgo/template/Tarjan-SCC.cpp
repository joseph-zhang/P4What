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
*    强连通分量(SCC)的Tarjan演算法可在线性时间复杂度下计算SCC。
*    Tarjan允许多个SCC并存于同一DFS树中,然后想办法把它们分开。
*    该方法的关键是判定某点是否是一个SCC中最先被DFS发现的点。
*    程式以点的邻接表建图.
*/
const int maxn = 200; //最多maxn个点
int n,m;
int pre[maxn];  //访问时的时间
int lowlink[maxn]; //能追溯到的最早被发现的祖先的pre值
int sccno[maxn];  //属于哪个SCC
int dfs_clock;  //深搜时间戳
int scc_cnt;   //SCC的个数
vector<int> G[maxn];
stack<int> stk; //附加栈,用于保存当前SCC中的节点(这些节点形成一颗子树)
//dfs过程
void dfs(int u){
	lowlink[u] = pre[u] = ++dfs_clock;
	stk.push(u);
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(!pre[v]){ //还没拜访过
			dfs(v);
			lowlink[u] = min(lowlink[u],lowlink[v]);
		}else if(!sccno[v]){ //访问到DFS树祖先,但还没确定它分在哪个SCC
			lowlink[u] = min(lowlink[u],pre[v]);
		}
	}
	if(lowlink[u] == pre[u]){ //这说明这时的u就是其所在SCC最早被发现的点
		scc_cnt++;
		for(;;){ //把栈中u之后的点都算进这个SCC中
			int x = stk.top();stk.pop();
			sccno[x] = scc_cnt;
			if(x == u)break;
		}
	}
}
//主驱过程
void findScc(){
	dfs_clock = scc_cnt = 0;
	memset(sccno,0,sizeof(sccno));
	memset(pre,0,sizeof(pre));
	for(int i = 0;i < n;i++)
		if(!pre[i]) dfs(i);
}

int main(){
	//freopen("input.txt","r",stdin);

	printf("How many nodes and edges in total? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your grapth.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}
	printf("Finding...\n");
	findScc();
	printf("Ok,%d SCC founded;\n",scc_cnt);
	for(int i = 0;i < n;i++){
		cout << sccno[i] << " ";
	}
	return 0;
}

/**
*    用Tarjan过后就得到了sccno[maxn]和scc_cnt的具体值,
*    即得到了各个点都属于哪个SCC,一共有多少个SCC.
*    然后可以进行缩点,将各个SCC都缩成一个点(结构上的),一共缩成scc_cnt个.
*    缩点之后原来的图就成了DAG,可以再次结构上设计高效的演算法.
*    缩点的过程统计各个缩点的出入度,或写成标准的图结构.
*    具体过程如下程式描述.
*/
int indegree[maxn];
int outdegree[maxn];
//(统计各个缩点的出入度)
void shrink(){
	memset(indegree,0,sizeof(indegree));
	memset(outdegree,0,sizeof(outdegree));
	for(int u = 0;u < n;u++){
		for(int i = 0;i < G[u].size();i++){
			int v = G[u][i];
			if(sccno[v] != sccno[u]){
				indegree[v]++;
				outdegree[u]++;
			}
		}
	}
}
