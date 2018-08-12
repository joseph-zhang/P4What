#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#define INF 0x7fffffff
using namespace std;

struct Edge{
	int c,f;
	Edge(){}
	Edge(int cap,int flow):c(cap),f(flow){}
};

Edge G[200][200];
int n,np,nc,m;
int path[200];
int a[200];

int EdmondsKarp(int s,int t){
	int maxflow = 0;
	memset(path,0,sizeof(path));
	for(;;){
		queue<int> que;
		memset(a,0,sizeof(a));
		que.push(s);
		a[s] = INF;
		while(!que.empty()){
			int u = que.front();que.pop();
			for(int i = 0;i < n+2;i++){
				if(G[u][i].c && (!a[i]) && (G[u][i].c > G[u][i].f)){
					path[i] = u;
					a[i] = min(a[u],G[u][i].c - G[u][i].f);
					que.push(i);
				}
			}
			if(a[t]) break;
		}  
		if(!a[t]) break;
		for(int u = t;u != s;u = path[u]){
			G[path[u]][u].f += a[t];
			G[u][path[u]].f -= a[t];	
		}
		maxflow += a[t];
	}	
	return maxflow;
}

int main(){
	while(scanf("%d%d%d%d",&n,&np,&nc,&m) != EOF){
		for(int i = 0;i < n+2;i++)
			for(int j = 0;j < n+2;j++)
				G[i][j].c = G[i][j].f = 0;
		char str[200];
		for(int i = 0;i < m;i++){
			int u,v,z;
			scanf("%s",str);
			sscanf(str,"(%d,%d)%d",&u,&v,&z);
			G[u][v] = Edge(z,0);	
		}
		for(int i = 0;i < np;i++){
			int u,z;
			scanf("%s",str);
			sscanf(str,"(%d)%d",&u,&z);
			G[n][u] = Edge(z,0);
		}
		for(int i = 0;i < nc;i++){
			int u,z;
			scanf("%s",str);
			sscanf(str,"(%d)%d",&u,&z);
			G[u][n+1] = Edge(z,0);
		}
		cout << EdmondsKarp(n,n+1) << endl;
	}
	return 0;
}
