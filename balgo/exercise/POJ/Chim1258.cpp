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
int n;
int p[102];

struct Edge{
	int x,y,cost;
	Edge(int m1,int m2,int c):x(m1),y(m2),cost(c){}
	bool operator < (const Edge& rhs) const {
		return cost > rhs.cost; 
	}
};


void Init(){
	for(int i = 1;i <= n;i++)
		p[i] = i;
}
int Find(int x){
	return x == p[x]?x:(p[x] = Find(p[x]));
}
void Union(int x,int y){
	p[Find(x)] = Find(y);
}

int kruskal(priority_queue<Edge>& que){
	int minCost = 0;
	int cnt = 0;
	while(!que.empty()){
		if(cnt > n) break;
		Edge e = que.top();que.pop();
		if(Find(e.x) == Find(e.y)) continue;
		minCost += e.cost;
		Union(e.x,e.y);
		cnt++;
	}	
	return minCost;
}
int main(){
	while(cin >> n){
		priority_queue<Edge> que;
		Init();
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				int c;
				scanf("%d",&c);
				if(j <= i) continue;
				que.push(Edge(i,j,c));
			}
		}
		cout << kruskal(que) << endl;
	}
	return 0;
}
	
	
