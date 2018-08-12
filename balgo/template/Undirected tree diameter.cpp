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
*    首先要明确无向图上两点u,v之间距离d(u,v)的定义:u和v之间所有途径中长度最短的那一个.
*    无向图中某点i的偏心距:点i到其他所有点距离中最大的一个值.
*    无向图的直径:图上所有偏心距当中最大的一個值.(也就是找两个点,让它们之间的距离最大)
*    无向图的半径:图上所有偏心距当中最小的一個值.(无向图中心(center)的偏心距是半径)
*    只要求出任意两点间距离,偏心距,直径,半径就都能求出.
*    (一)无权图情形:每次可以对一个没有访问过的节点进行,用BFS连续查两次最远点,每次更新最大值即可.
*    (二)有权图情形:用Floyd-warshall求任意两点间距离即可.
*    无向图上没有圈,就成为了树.因而可以先用并查集判圈,若没有圈可以用针对树的方法(BFS).
*    图结构采用邻接矩阵.
*/
const int maxn = 100;
const int inf = 1e8;
int n,m;
int diameter,radius;
int G[maxn][maxn];
int dist[maxn][maxn];	
int ecc[maxn];	 //各點的偏心距
int p[maxn];     //并查集用
int d[maxn];     //BFS用的记录
int vis[maxn];   //记录访问过那些结点

inline void Init(){for(int i = 0;i < n;i++) p[i] = i;}
int Find(int i){return i == p[i]?i:p[i] = Find(p[i]);}
void Union(int u,int v){
	int pu = Find(u);
	int pv = Find(v);
	p[pu] = pv;
}

/*(一)无权图可以用BFS的方法*/
int BFS(int s){
	memset(d,-1,sizeof(d));
	queue<int> que;
	que.push(s);
	d[s] = 0;
	int maxval = 0;
	while(!que.empty()){
		int u = que.front();que.pop();
		for(int i = 0;i < n;i++){
			if(G[u][i] == inf || u == i) continue;
			if(d[i]!=-1)continue;
			d[i] = d[u]+1;
			maxval = max(maxval,d[i]);
			que.push(i);
		}
	}
	return maxval;
}

void func(){
	diameter = 0;
	memset(vis,false,sizeof(vis));
	for(int i = 0;i < n;i++){
		if(vis[i])continue;
		vis[i] = true;
		int dt = BFS(i);
		for(int j = 0;j < n;j++){
			cout << d[j] << " ";
		}
		cout << endl;
		for(int j = 0;j < n;j++){
			if(d[j] == dt){
				dt = BFS(j);
				break;
			}
		}
		diameter = max(diameter,dt);
	}
}

/*(二)有权图可以考虑采用*/
void diameter_radius(){
	//init
	for(int i = 0;i < n;i++)G[i][i] = 0;
	for(int i = 0;i < n;i++){
		for(int j = i+1;j < n;j++)
			dist[i][j] = dist[j][i] = G[i][j];
	}
	// Floyd-Warshall Algorithm
	for(int k = 0;k < n;k++){
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
				dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
	}
	//算算偏心距
	memset(ecc,0,sizeof(ecc));
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++)
			ecc[i] = max(ecc[i],dist[i][j]);
	}
	//算出半径和直径
	diameter = 0;
	radius = 1e9;
	for(int i = 0;i < n;i++){
		diameter = max(diameter,ecc[i]);
		radius = min(radius,ecc[i]);
	}
}


int main(){
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("now give me your graph.\n");
	Init();
	for(int i = 0;i < n;i++)fill(G[i],G[i]+n,inf);
	for(int i = 0;i < m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u][v] = w;G[v][u] = w;
		if(Find(u) == Find(v))cout << "Has circle!\n" << endl;
		else Union(u,v);
	}
	printf("constructing...\n");
	//func();
	diameter_radius();
	printf("diameter is %d\n",diameter);
	return 0;
}
