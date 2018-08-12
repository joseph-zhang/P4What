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
*    点-双连通分量(简称双连通分量Biconnected Component/块Block),是无向图点-双连通的极大子图.
*    点-双连通:内部没有关节点(割顶).
*    求点-BCC可以用Tarjan的方法(Tarjan发明的演算法很多,注意区分).
*    每条边都恰好属于一个点-BCC,但是不同的两个点-BCC可以有公共结点(最多一个),且它是割顶.
*    反过来,每个割顶都是两个不同点-BCC的公共结点,所以只要找出所有的割顶即可.
*    每找到一个割顶,我们就知道会有一个BCC,整个演算法过程和和求割顶基本一致.
*    实现时用栈来保存"当前BCC"中的边(而不是点).
*    下述实现的程式以点的邻接表建图.
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
int bccno[maxn];//属于哪个BCC
int dfs_clock;  //深搜时间戳
int bcc_cnt;    //BCC计数分配器(从1开始编号)
vector<int> G[maxn],bcc[maxn];
stack<Edge> stk;//暂存边的栈

//深搜过程,将子树上的low值都算出来
int dfs(int u,int fa){
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		Edge e = Edge(u,v);
		if(!pre[v]){  //还没拜访过,走的是树边
			stk.push(e);
			child++;
			int lowv = dfs(v,u);
			lowu = min(lowu,lowv);
			if(lowv >= pre[u]){ //u是割顶
				iscut[u] = true;
				bcc[++bcc_cnt].clear();
				for(;;){
					//将栈中前面那些边们的两端点都依次加进新的BCC
					Edge x = stk.top();stk.pop();
					if(bccno[x.u] != bcc_cnt){
						bcc[bcc_cnt].push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if(bccno[x.v] != bcc_cnt){
						bcc[bcc_cnt].push_back(x.v);
						bccno[x.v] = bcc_cnt;
					}
					if(x.u == u && x.v == v)break;//回到了原来的边的位置
				}
			}
		}else if(pre[v] < pre[u] && v != fa){//原来拜访过,走的是反向边
			stk.push(e);//反向边也要加进来
			lowu = min(lowu,pre[v]);
		}
	}
	if(fa < 0 && child == 1) iscut[u] = 0; //处理根的情况
	return lowu;
}

//主控过程
void Tarjan(){
	//初始化
	memset(pre,0,sizeof(pre));
	memset(iscut,false,sizeof(iscut));
	memset(bccno,0,sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	//找BCC
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
	printf("The Biconnected Component are showed below.\n");
	for(int i = 1;i <= bcc_cnt;i++){
		cout << "BCC#" << i << endl;
		for(int j = 0;j < bcc[i].size();j++)
			cout << bcc[i][j] << " ";
		cout << endl;
	}
	return 0;
}
