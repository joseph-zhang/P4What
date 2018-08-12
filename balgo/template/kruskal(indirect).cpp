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
#define ULL unsigned LL

/**
*    kruskal演算法可以有效地求出无向图的最小生成树(MST)
*    基于如下归纳:
*    (1)每个单独的顶点可以看做是一个MST;
*    (2)两棵MST连成一棵,以权重最小的边进行连接显然是最好的;
*    对(1),(2)进行归纳,可以得出kruskal的正确性.
*    实现时采用间接排序,提高了排序效率.
*    用UnionFind高效的判断连通分量加速,总时间O(ElogV)
*/
using namespace std;
const int maxm = 30;//最多多少条边
const int maxn = 60;//最多多少个点
int p[maxn+5];
//第i条边的顶点和值,相当于把结构体给拆开了..
int u[maxm+5],v[maxm+5],w[maxm+5];
int r[maxm+5];//间接排序数组 
inline void Init(){
	for(int i = 0;i < maxn;i++)p[i] = i;
}
int Find(int x){
	return p[x] == x?x:(p[x] = Find(p[x]));
}
void Union(int x,int y){
	p[Find(x)] = Find(y);
}
bool cmp(int i,int j){return w[i] < w[j];}
int kruskal(int m){
	Init();
	int res = 0;
	for(int i = 0;i < m;i++)r[i] = i;
	sort(r,r+m,cmp);
	for(int i = 0;i < m;i++){
		int e = r[i];
		int x = Find(u[e]),y = Find(v[e]);
		if(x!=y){res+=w[e];Union(u[e],v[e]);}
	}	
	return res;
}
int main(){
	int n,m;//图上有n个点,m条边 
	while(cin >> n >> m){
		printf("So your graph has %d edges and %d points.\nNow give these edges to me.\n",m,n);
		for(int i = 0;i < m;i++)
			scanf("%d%d%d",&u[i],&v[i],&w[i]);
		cout << kruskal(m)<< endl;
	}
	return 0;
}

