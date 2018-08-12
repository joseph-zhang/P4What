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
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
struct Edge{
	int flow,cap;
	Edge(){}
	Edge(int f,int c):flow(f),cap(c){}
};
struct edge{
	int from,to;
	edge(){}
	edge(int u,int v):from(u),to(v){}
};
Edge G[120][120];
int data[54][24];
int P,N;
int EK(int s,int t){
	int maxflow = 0;
	int a[120];
	int p[120];
	for(;;){
		memset(a,0,sizeof(a));
		queue<int> q;
		q.push(s);
		a[s] = INF;
		while(!q.empty()){
			int u = q.front();q.pop();
			for(int i = 0;i <= 2*N+2;i++){
				Edge& e = G[u][i];
				if((!a[i]) && e.cap > e.flow){
					p[i] = u;
					a[i] = min(a[u],e.cap-e.flow);
					q.push(i);
				}
			}
			if(a[t]) break;
		}
		if(!a[t]) break;
		for(int x = t;x != s;x = p[x]){
			G[p[x]][x].flow += a[t];
			G[x][p[x]].flow -= a[t];
		}
		maxflow += a[t];
	}
	return maxflow;
}
int main(){
	while(cin >> P >> N){
		for(int i = 0;i <= 2*N+2;i++)
			for(int j = 0;j <= 2*N+2;j++)
				G[i][j] = Edge(0,0);
		for(int i = 1;i <= N;i++)
			for(int j = 0;j < 2*P+1;j++)
				scanf("%d",&data[i][j]);
		for(int i = 1;i <= N;i++){
			for(int j = 1;j <= N;j++){
				if(i == j){
					G[i][N+i] = Edge(0,data[i][0]);
					continue;
				}
				int cnt = 0;
				for(int k = P+1;k < 2*P+1;k++){
					if(data[j][k-P] == 2){cnt++;continue;}
					if(data[j][k-P] == data[i][k])cnt++;
				}
				if(cnt == P) G[N+i][j] = Edge(0,INF);
			}
		}
		for(int i = 1;i <= N;i++){
			bool tag = true;
			for(int j = 1;j <= P;j++)
				if(data[i][j] == 1){tag = false;break;}
			if(tag) G[0][i] = Edge(0,INF);
		}
		for(int i = 1;i <= N;i++){
			bool tag = true;
			for(int j = P+1;j < 2*P+1;j++)
				if(data[i][j] != 1){tag = false;break;}
			if(tag) G[N+i][2*N+1] = Edge(0,INF);
		}
		int maxflow = EK(0,2*N+1);
		vector<edge> res;
		for(int i = N+1;i <= 2*N;i++)
			for(int j = 1;j <= N;j++)
				if(i-N != j && G[i][j].flow)
					res.push_back(edge(i-N,j));
		cout << maxflow << " " << res.size() << endl;
		for(int i = 0;i < res.size();i++){
			edge& r = res[i];
			Edge& e = G[r.from+N][r.to];
			printf("%d %d %d\n",r.from,r.to,e.flow);
		}
	}
	return 0;
}

