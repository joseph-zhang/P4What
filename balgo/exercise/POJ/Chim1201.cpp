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
	int u,v,w,next;
	Edge(){}
	Edge(int from,int to,int weight,int nex_p):
		u(from),v(to),w(weight),next(nex_p){}
}edges[200000];
int head[52000];
int Count = 0;
int N;
int minval = 0,maxval = 0;

inline void addEdge(int u,int v,int w){
	edges[Count] = Edge(u,v,w,head[u]);
	head[u] = Count++;
}
int SPFA(){
	bool inq[52000];
	int d[52000];
	fill(d,d+51000,-INF);
	memset(inq,false,sizeof(inq));
	queue<int> q;
	q.push(minval);d[minval] = 0;
	inq[minval] = true;
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		for(int i = head[u];i != -1;i = edges[i].next){
			Edge& e = edges[i];
			if(d[u] + e.w > d[e.v]){
				d[e.v] = d[u] + e.w;
				if(!inq[e.v]){
					q.push(e.v);
					inq[e.v] = true;
				}
			}
		}
	}
	return d[maxval+1];
}
int main(){
	cin >> N;
	int ai,bi,ci;
	int res = 0;
	fill(head,head+50002,-1);
	for(int i = 0;i < N;i++){
		scanf("%d %d %d",&ai,&bi,&ci);
		minval = min(minval,ai);
		maxval = max(maxval,bi);
		addEdge(ai,bi+1,ci);
	}
	for(int i = minval;i <= maxval;i++){
		addEdge(i,i+1,0);
		addEdge(i+1,i,-1);
	} 
	res = SPFA();
	cout << res << endl;
	return 0;
}

