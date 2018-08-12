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
#include <iomanip>
#define INF 0x7fffffff
using namespace std;

struct Point{
	int x,y;
	Point(){}
	Point(int m1,int m2):x(m1),y(m2){}
};
double getDist(int x1,int y1,int x2,int y2){
	return sqrt((double)((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
};
struct Edge{
	int from,to;
	double cost;
	Edge(int f,int t,double c):from(f),to(t),cost(c){}
};
struct heapNode{
	int index;
	double indi;
	heapNode(int i,double d):index(i),indi(d){}
	bool operator < (const heapNode& rhs) const{
		return indi > rhs.indi;
	}
};
vector<Edge> G[202];
double d[202];
int n;
int cnt = 0;
void dijkstra(int s){
	for(int i = 1;i <= n;i++) d[i] = INF;
	d[s] = 0;
	priority_queue<heapNode> que;
	bool done[n+1];
	memset(done,false,sizeof(done));
	que.push(heapNode(s,0));
	while(!que.empty()){
		heapNode p = que.top();que.pop();
		if(done[p.index]) continue;
		done[p.index] = true;
		int u = p.index;
		for(int i = 0;i < G[u].size();i++){
			Edge& e = G[u][i];
			if(d[e.to] > max(d[u],e.cost)){
				d[e.to] = max(d[u],e.cost);
				que.push(heapNode(e.to,d[e.to]));
			}
		}
	}

}
int main(){
	while(cin >> n){
		if(!n) break;
		Point points[n+1];
		for(int i = 1;i <= n;i++) G[i].clear();
		for(int i = 1;i <= n;i++){
			int x,y;
			cin >> x >> y;
			points[i] = Point(x,y);
		}
		for(int i = 1;i <= n;i++){
			for(int j = i+1;j <= n;j++){
				double dis = getDist(points[i].x,points[i].y,points[j].x,points[j].y);
				G[i].push_back(Edge(i,j,dis));
				G[j].push_back(Edge(j,i,dis));
			}
		}
		dijkstra(1);
		cout << "Scenario " <<"#" << ++cnt << endl;
		cout<<"Frog Distance = "<<showpoint<<setprecision(3)<<fixed<<d[2]<<endl;
		cout << endl;	
	}
	return 0;
}
