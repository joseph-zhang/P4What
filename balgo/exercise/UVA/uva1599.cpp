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
#include<cctype>
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
const int maxn = 100000;
const int maxm = 200000;
struct Edge{
	int u,v,w;
	int next;
	Edge(){}
	Edge(int a,int b,int color,int nxt):u(a),v(b),w(color),next(nxt){}
};
Edge edges[maxm+10];
int head[maxn+10];
int N,M;
int d[maxn+10];
int p[maxn+10];
int cnt = 1;
void getTree(){
	memset(d,-1,sizeof(d));	
	d[N] = 0;
	queue<int> q;
	q.push(N);
	while(!q.empty()){
		int u = q.front();q.pop();
		if(u == 1) break;
		for(int i = head[u];i != -1;i = edges[i].next){
			Edge& e = edges[i];
			if(d[e.v] == -1){
				d[e.v] = d[e.u]+1;
				q.push(e.v);
			}
		}
	}
}
void SPFA(){
	int db[N+5];
	bool inq[N+5];
	queue<int> q;
	memset(inq,false,sizeof(inq));
	fill(db,db+N+2,INF);
	memset(p,0,sizeof(p));
	db[1] = 0;
	q.push(1);
	inq[1] = true;
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		for(int i = head[u];i != -1;i = edges[i].next){
			Edge& e = edges[i];
			if(d[e.v] == d[e.u]-1 && db[e.v] > e.w){
				db[e.v] = e.w;
				p[e.v] = i;
				if(!inq[e.v]){q.push(e.v);inq[e.v] = true;}
			}
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> N){
		cin >> M;
		cnt = 1;
		memset(head,-1,sizeof(head));
		for(int i = 0;i < M;i++){
			int a,b,w;
			cin >> a >> b >> w;
			edges[cnt++] = Edge(a,b,w,head[a]);
			head[a] = cnt-1;
			edges[cnt++] = Edge(b,a,w,head[b]);
			head[b] = cnt-1;
		}
		getTree();
		SPFA();
		stack<int> stk;
		cout << d[1] << endl;
		for(int i = p[N];;i = p[edges[i].u]){
			Edge& e = edges[i];
			stk.push(e.w);
			if(e.u == 1) break;
		}
		for(;;){
			int color = stk.top();
			stk.pop();
			if(!stk.empty()) cout << color << " ";
			else {cout << color << endl;break;}
		}
	}
	return 0;
}
