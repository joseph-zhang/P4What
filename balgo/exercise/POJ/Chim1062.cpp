#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<string.h>
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
	int to;
	int weight;
	Edge(int t,int c):to(t),weight(c){}
};

int level[120];
int d[120];
bool inque[120];
vector<Edge> G[110];
void bellmanFord(int n,int fl,int fa){
	queue<int> q;
	memset(inque,false,n+1);
	fill(d,d+n+1,INF);
	d[0] = 0;
	q.push(0);
	inque[0] = true;
	while(!q.empty()){
		int p = q.front();
		q.pop();
		inque[p] = false;
		for(int i = 0;i < G[p].size();i++){
			Edge& e = G[p][i];
			if(level[e.to] >= fl && level[e.to] <= fa){
				if(d[e.to] > d[p] + e.weight){
					d[e.to] = d[p] + e.weight;
					if(!inque[e.to]){
						q.push(e.to);
						inque[e.to] = true;
					}
				}
			}
		}
	}	
}
int main(){
	int m,n;
	cin >> m >> n;
		int p,l,x;
		memset(level,0,sizeof(level));
		for(int i = 1;i <= n;i++){
			cin >> p >> l >> x;
			G[0].push_back(Edge(i,p));
			level[i] = l;
			while(x--){
				int t,v;
				cin >> t >> v;
				G[t].push_back(Edge(i,v)); 
			}
		}	
		int res = INF;
		for(int i = level[1]-m;i <= level[1];i++){
			bellmanFord(n,i,i+m);
			res = min(res,d[1]);
		}
		cout << res << endl;	
	return 0;
}	
