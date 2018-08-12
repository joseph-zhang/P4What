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
*	 区间最值快速查询,RMQ.
*    方法是使用DP预处理,建立稀疏表(Sparse-Table).
*    状态及指标:d(i,j) 从下标 i 开始长度为 2^j 的区间的最小值
*    已知恒等式:2^j = 2^(j-1) + 2^(j-1),有:
*        状态转移:d(i,j) = min(d(i,j-1), d(i+2^(j-1),j-1))
*        边界: d(i,0) = A[i]
*        Query: RMQ(l,k) = (d(l,p),d(k-2^p+1,p)) , p = lb(k-l+1)
*        (以靠左、靠右的兩條等寬區間，求得查詢區間的最值)
*    预处理:O(NlogN),查询:O(1).
*/
const int maxn = 202;
int d[maxn][maxn];
/**
*	 版本一
*    该版本的结果给出了区间内最小值
*/
void initRMQ1(int* A,int num){
	for(int i = 0;i < num;i++)d[i][0] = A[i];
	for(int j = 1;(1<<j) <= num;j++)
		for(int i = 0;i+(1<<j)-1<num;i++)
			d[i][j] = min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}
int RMQ1(int u,int v){
	if(u > v)swap(u,v);
	int k = (int)(log(v-u+1.0)/log(2.0));
	return min(d[u][k],d[v-(1<<k)+1][k]);
}

/**
*	版本二,可配合下面的 LCA 问题。
*   该版本的结果给出了区间内最小值的下标
*/
void initRMQ(int* A,int num){
	for(int i = 0;i < num;i++)d[i][0] = i;
	for(int j = 1;(1<<j) <= num;j++)
		for(int i = 0;i+(1<<j)-1<num;i++)
			d[i][j] = (A[d[i][j-1]]<A[d[i+(1<<(j-1))][j-1]])?d[i][j-1]:d[i+(1<<(j-1))][j-1];
}
int RMQ(int* A,int u,int v){
	if(u > v)swap(u,v);
	int k = (int)(log(v-u+1.0)/log(2.0));
	return (A[d[u][k]]<A[d[v-(1<<k)+1][k]])?d[u][k]:d[v-(1<<k)+1][k];
}
/**
*    最低公共祖先问题,LCA。
*    LCA 和 RMQ 问题数学上等价,可以相互转换。
*    可利用 RMQ 来求 LCA ,基本方法是 DFS。
*    在树上执行 DFS :
*	      1)depth[time] 记录随时间访问的节点的深度
*         2)val[time]   记录随时间访问的节点
*         3)firsts[indx] 记录第一次访问某节点 indx 的时间
*    LCA(x,y) = val[RMQ(depth,firsts[x],firsts[y])]
*    我们用邻接表表示树来进行测试程式的编写。为了方便我们采用的是有向边。
*/
//需要预先估计各个数组的大小范围,设n为节点数，t 用于记时
int depth[maxn<<1+2],val[maxn<<1+2],firsts[maxn+2],t = 0;
vector<int> tree[maxn];
void dfs(int indx,int dep){
	depth[t] = dep;val[t] = indx;firsts[indx] = t++;
	for(int i = 0;i < tree[indx].size();i++){
		dfs(tree[indx][i],dep+1);
		depth[t] = dep;val[t] = indx;t++;
	}
}
void initLCA(){initRMQ(depth,t);}
int LCA(int x,int y){
	return val[RMQ(depth,firsts[x],firsts[y])];
}


int main(){
	int n;
	printf("Now we will construct a tree,suppose the root is zero.\n");
	printf("How many edges? ");
	scanf("%d",&n);
	printf("Now give me them.\n");
	for(int i = 0;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		tree[u].push_back(v);
	}
	dfs(0,0);
	initLCA();
	printf("how many query times? ");
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("the LCA of %d and %d is: %d.\n",u,v,LCA(u,v));
	}
	return 0;
}
