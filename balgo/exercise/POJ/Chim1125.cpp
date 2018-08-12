#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
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
#include<sstream> 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
struct Edge{
	int from,to,nxt;
	double cost;
	Edge(){}
	Edge(int f,int t,double c,int nt):from(f),to(t),cost(c),nxt(nt){}
};
struct heapNode{
	int u;double sd; 
	heapNode(){}
	heapNode(int x,double d):u(x),sd(d){}
	bool operator < (const heapNode& rhs)const{
		return sd > rhs.sd;
	}
};
int N,M,K,Ds;
int head[1200];
vector<Edge> edges;
double res1,res2;
double var1,var2;
void addEdge(int u,int v,int d){
	edges.push_back(Edge(u,v,d,head[u]));
	head[u] = edges.size();
	edges.push_back(Edge(v,u,d,head[v]));
	head[v] = edges.size();
}
inline int Pars(char *s){
	if(s[0]=='G')return N+(s[1]-'0');
	else return (s[0]-'0');
}
bool dijkstra(int s){
	priority_queue<heapNode> pQue;
	double dis[N+M+5];
	bool done[N+M+5];
	double sum = 0.0;
	var1 = 1e7;var2 = 1e6;
	for(int i = 0;i < N+M+5;i++)dis[i] = 1e6;
	memset(done,false,sizeof(done));
	dis[s] = 0;
	pQue.push(heapNode(s,0));
	while(!pQue.empty()){
		heapNode p = pQue.top();pQue.pop();
		int u = p.u;
		if(done[u])continue;
		done[u] = true;	
		//cout << p.u << " " << p.sd << endl;
		if(u>=1 && u<=N){
			if(p.sd > Ds)return false;
			var1 = min(var1,p.sd);
			sum += p.sd;
		}
		for(int tmp = head[u];tmp!=-1;tmp = edges[tmp-1].nxt){
			Edge& e = edges[tmp-1];
			if(dis[e.to] > dis[u]+e.cost){
				dis[e.to] = dis[u] + e.cost;
				//cout << "add Node " << e.to << endl;
				pQue.push(heapNode(e.to,dis[e.to]));
			}
		}
	}
	var2 = sum/N;
	return true;
}

int main(){
	//freopen("input.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&K,&Ds)!=EOF){
		memset(head,-1,sizeof(head));
		edges.clear();
		char s[20];
		int resid = 1e4;
		res1 = res2 = 0;
		for(int i = 0;i < K;i++){
			int u,v,d;
			scanf("%s",s);u = Pars(s);
			scanf("%s",s);v = Pars(s);
			scanf("%d",&d);addEdge(u,v,d);
		}
		//for(int i = 0;i < edges.size();i++)printf("%d %d %f %d\n",edges[i].from,edges[i].to,edges[i].cost,edges[i].nxt);
		//cout << endl;
		//for(int i = 1;i <= N+M;i++)printf("%d\n",head[i]);
		for(int pp = N+1;pp <= N+M;pp++){
			//cout << endl;
			if(dijkstra(pp)){
				if(res1 < var1){ 
					res1 = var1;
					res2 = var2;
					resid = pp-N;
				}else if(res1 == var1){
					if(res2 >var2){
						res1 = var1;
						res2 = var2;
						resid = pp-N;
					}
				}
			}
		}
		if(resid == 1e4)printf("No Solution\n");
		else{
			printf("G%d\n",resid);
			printf("%.1f %.1f\n",res1,res2);
		}
	}
	return 0;
}

