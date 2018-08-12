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
	int m1,m2,cost,index;
	Edge(int f,int t,int c,int i):m1(f),m2(t),cost(c),index(i){}
	bool operator < (const Edge& rhf) const{
		return cost > rhf.cost;
	}
};

int p[600];
int t;

void init(){
	for(int i = 1;i <= t;i++)
		p[i] = i;	
}
int find(int x){
	return x == p[x]?x:(p[x] = find(p[x]));
}
void un(int x,int y){
	p[find(x)] = find(y);
}

int kruskal(priority_queue<Edge>& que,int t){
	int cnt = 1;
	int val = 0;
	while(!que.empty()){
		if(cnt > t) break;
		Edge e = que.top();que.pop();
		if(find(e.m1) == find(e.m2)) continue;
		val = max(val,e.cost);
		un(e.m1,e.m2);
		cnt++; 
	}
	return val;
}
int main(){
	int n;
	cin >> n;
	while(n--){
		scanf("%d",&t);
		int cnt = 1;
		init();
		priority_queue<Edge> que;
		for(int i = 1;i <= t;i++){
			for(int j = 1;j <= t;j++){
					int c;
					scanf("%d",&c);
					if(j <= i) continue;
					que.push(Edge(i,j,c,cnt++));
			}
		}
		cout << kruskal(que,t) << endl;	
	}
	return 0;
}

