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
*    SPFA(又名lable correcting)可应用于带负权的图的单源最短路径;
*    SPFA是Bellman-ford演算法的改进,基于队列实现;
*    同时SPFA还可用于赋权图的正/负圈检测.
*    下面的程式判断SPFA搜索时沿路有没有负圈,想要判断整张图上有没有负圈,只要设置一个"超级结点"即可.
*    建图方式采用前向星.
*/
const int maxn = 50;
const int maxm = 100<<1;
struct Edge{
	int to; 
	/*int from;*/
	int len;
	/*int hook;*/
	Edge(){}
	Edge(int t,int l):to(t),len(l){}
}edges[maxm];
//vector<Edge> edges;
vector<int> G[maxn+2];
int d[maxn+2],p[maxn+2];
int r;

inline void addEdge(int u,int v,int l){
	edges[r++] = Edge(v,l);
	G[u].push_back(r-1);
}
bool SPFA(int s,int n){
	queue<int> que;
	int cnt[maxn+2]; //用于判断一个点进了几次队列
	bool inq[maxn+2];
	memset(inq,false,sizeof(inq));
	memset(cnt,0,sizeof(cnt));
	for(int i = 0;i < n;i++)d[i] = INF;
	d[s] = 0;
	inq[s] = true;que.push(s);
	while(!que.empty()){
		int u = que.front();que.pop();
		inq[u] =  false;
		for(int i = 0;i < G[u].size();i++){
			Edge& e = edges[G[u][i]];
			if(d[e.to]>d[u]+e.len){ //松弛
				d[e.to] = d[u] + e.len;
				p[e.to] = u;
				if(!inq[e.to]){
					inq[e.to] = true;que.push(e.to);
					if(++cnt[e.to]>n)return false; //一个点进了超过n次,沿路上有负圈,没有最短路
				}
			}
		}
	}
	return true;
}
void printPath(int v){
	printf("%d ",v);
	if(!v)return;
	printPath(p[v]);
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		r = 0;
		for(int i = 0;i < n;i++)p[i] = i;
		for(int i = 0;i < m;i++){
			int u,v,l;
			scanf("%d%d%d",&u,&v,&l);
			addEdge(u,v,l);
		}
		if(!SPFA(0,n)){printf("Your graph has negative circle from 0!\n",);continue;}
		int qurey;scanf("%d",&qurey);
		for(int i = 0;i < qurey;i++){
			int v;scanf("%d",&v);
			printPath(v);cout << endl;
			printf("%d",d[v]);cout << endl;
		}
	}
	return 0;
}