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
*    ����Ҫ��ȷ����ͼ������u,v֮�����d(u,v)�Ķ���:u��v֮������;���г�����̵���һ��.
*    ����ͼ��ĳ��i��ƫ�ľ�:��i���������е����������һ��ֵ.
*    ����ͼ��ֱ��:ͼ������ƫ�ľ൱������һ��ֵ.(Ҳ������������,������֮��ľ������)
*    ����ͼ�İ뾶:ͼ������ƫ�ľ൱����С��һ��ֵ.(����ͼ����(center)��ƫ�ľ��ǰ뾶)
*    ֻҪ���������������,ƫ�ľ�,ֱ��,�뾶�Ͷ������.
*    (һ)��Ȩͼ����:ÿ�ο��Զ�һ��û�з��ʹ��Ľڵ����,��BFS������������Զ��,ÿ�θ������ֵ����.
*    (��)��Ȩͼ����:��Floyd-warshall�������������뼴��.
*    ����ͼ��û��Ȧ,�ͳ�Ϊ����.����������ò��鼯��Ȧ,��û��Ȧ������������ķ���(BFS).
*    ͼ�ṹ�����ڽӾ���.
*/
const int maxn = 100;
const int inf = 1e8;
int n,m;
int diameter,radius;
int G[maxn][maxn];
int dist[maxn][maxn];	
int ecc[maxn];	 //���c��ƫ�ľ�
int p[maxn];     //���鼯��
int d[maxn];     //BFS�õļ�¼
int vis[maxn];   //��¼���ʹ���Щ���

inline void Init(){for(int i = 0;i < n;i++) p[i] = i;}
int Find(int i){return i == p[i]?i:p[i] = Find(p[i]);}
void Union(int u,int v){
	int pu = Find(u);
	int pv = Find(v);
	p[pu] = pv;
}

/*(һ)��Ȩͼ������BFS�ķ���*/
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

/*(��)��Ȩͼ���Կ��ǲ���*/
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
	//����ƫ�ľ�
	memset(ecc,0,sizeof(ecc));
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++)
			ecc[i] = max(ecc[i],dist[i][j]);
	}
	//����뾶��ֱ��
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
