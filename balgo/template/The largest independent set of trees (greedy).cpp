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
*    树的最大独立集可以用Dp,但是有实践性更好的贪心方法.
*    由于树的结构很好,每个结点只有唯一的父节点,于就得到了一个贪心演算法.
*    由树叶往树根方向选出独立集,尽量選擇树叶,最后就得到最大独立集.(看看图示)
*    注意:最大独立集不止一个,但这种方式无法得到字典序最小的最大独立集.
*    实现时依然先无根树转有根树,再不断标记树根即可.时间复杂度相当于一次Graph Traversal.
*/
const int maxn = 100;
int n;
vector<int> G[maxn];//采用邻接表来表示
int parent[maxn];	//转化成有根的DFS树
int preorder[maxn];	// DFS树的preorder
bool mark[maxn];    //标记:在不在最大独立集里
int  independent[maxn];//最大独立集
int t = 0;          //分配计数器:记录preorder用
int cnt = 0;        //分配计数器:记录最大独立集用
//对结点u生成DFS树
void dfs(int u,int fa){
	preorder[t++] = u;
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(v == fa)continue;
		dfs(v,u);
		parent[v] = u;
	}
}
//主控过程,求树的最大独立集
void MIS(){
	memset(parent,-1,sizeof(parent));
	memset(mark,true,sizeof(mark));
	cnt = t = 0;
	dfs(0,-1);//随便挑一个点做根
	for(int i = 0;i < n;i++)cout << i << " f-> " << parent[i] << endl;
	for(int i = n-1;i>=0;i--){
		cout << preorder[i] << " ";
		int u = preorder[i];
		if(!mark[u])continue;
		independent[cnt++] = u;
		if(parent[u]!=-1)mark[parent[u]] = false;
	}
	cout << endl;
}
int main(){
	int k,u,v;
	printf("how many nodes on your tree? ");
	scanf("%d",&n);
	cout << "give me your tree.\n";
	for(int i = 0;i < n-1;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	printf("Constructing...\n");
	MIS();
	printf("the independent Set:\n");
	for(int i = 0;i < cnt;i++)
		cout << independent[i] << " ";
	cout << endl;
	return 0;
}










