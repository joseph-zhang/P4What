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
	int from,to;
	int time;
	Edge(){}
	Edge(int u,int v,int t):from(u),to(v),time(t){}
};
vector<Edge> edges;
vector<int> G[502];
int N,M,W;
int d[502];
int cnt[502];
bool inq[502];
bool SPFA_detect(){
	queue<int> q;
	memset(inq,0,sizeof(inq));
	memset(cnt,0,sizeof(cnt));
	for(int i = 1;i <= N;i++){
		d[i] = 0;
		inq[i] = true;
		q.push(i);
	}
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		for(int i = 0;i < G[u].size();i++){
			Edge& e = edges[G[u][i]];
			if(d[e.to] > d[e.from]+e.time){
				d[e.to] = d[e.from]+e.time;
				if(!inq[e.to]){
					q.push(e.to);
					inq[e.to] = true;
					if(++cnt[e.to] > N) return true;
				}
			}
		}
	}
	return false;
}
int main(){
	int n;cin >> n;
	while(n--){
		scanf("%d %d %d",&N,&M,&W);
		edges.clear();
		for(int i = 1;i <= N+1;i++)G[i].clear();
		for(int i = 0;i < M;i++){
			int u,v,t;
			scanf("%d %d %d",&u,&v,&t);
			edges.push_back(Edge(u,v,t));
			edges.push_back(Edge(v,u,t));
			G[u].push_back(edges.size()-2);
			G[v].push_back(edges.size()-1);
		}
		for(int i = 0;i < W;i++){
			int u,v,t;
			scanf("%d %d %d",&u,&v,&t);
			edges.push_back(Edge(u,v,-t));
			G[u].push_back(edges.size()-1);
		}
		if(SPFA_detect()) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
