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
	Edge(int f,int t,int c,int nx):u(f),v(t),w(c),next(nx){}
}edges[302000];
int head[1200];
int N,M;
int cnt;
bool SPFA_cycle(){
	int count[1200];
	bool inq[1200];
	int d[1200];
	queue<int> q;
	memset(d,0,sizeof(d));
	memset(count,0,sizeof(count));
	for(int i = 1;i <= N;i++){
		inq[i] = true;//d[i] = 0;
		q.push(i);
	}
	while(!q.empty()){
		int u = q.front();q.pop();
		inq[u] = false;
		for(int i = head[u];i != -1;i = edges[i].next){
			Edge& e = edges[i];
			if(d[e.u]+e.w > d[e.v]){
				d[e.v] = d[e.u]+e.w;
				if(!inq[e.v]){
					q.push(e.v);inq[e.v] = true;
					if(++count[e.v] > N) return true;
				}
			}
		}
	}
	return false;
}
int main(){
	char tag;
 	while(cin >> N >> M){
		cnt = 0;
		memset(head,-1,sizeof(head));
		for(int i = 0;i < M;i++){
			cin >> tag;
			int a,b,c;
			if(tag == 'P'){
				scanf("%d %d %d",&a,&b,&c);
				edges[cnt++] = Edge(b,a,c,head[b]);
				head[b] = cnt-1;
				edges[cnt++] = Edge(a,b,-c,head[a]);
				head[a] = cnt-1;
			}
			else{
				scanf("%d %d",&a,&b);
				edges[cnt++] = Edge(b,a,1,head[b]);
				head[b] = cnt-1;
			}
		}
		cnt--;
		if(SPFA_cycle()) printf("Unreliable\n");
		else printf("Reliable\n");
	}
	return 0;
}
