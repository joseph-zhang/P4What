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
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define ULL unsigned LL
using namespace std;

const int maxe = 30;//最多多少条边
const int maxn = 60;//最多多少个点
int p[maxn+5];
struct Edge{
	int p1,p2,cost;
	Edge(){}
	Edge(int p1_,int p2_,int cost_):p1(p1_),p2(p2_),cost(cost_){}
	bool operator < (const Edge& rhs)const{
		return cost > rhs.cost;
	}
};
inline void Init(){
	for(int i = 0;i < maxn;i++)p[i] = i;
}
int Find(int x){
	return p[x] == x?x:(p[x] = Find(p[x]));
}
void Union(int x,int y){
	p[Find(x)] = Find(y);
}

int kruskal(priority_queue<Edge>& pque){
	Init();
	int res = 0;
	while(!pque.empty()){
		Edge e = pque.top();pque.pop();
		if(Find(e.p1) == Find(e.p2)){printf("Drop %d-%d..\n",e.p1,e.p2);continue;}
		printf("Union point %d and %d...\nthe cost on the edge is %d.\n",e.p1,e.p2,e.cost);
		Union(e.p1,e.p2);
		res += e.cost;
	}
	return res;
}
int main(){
	int n,m;//图上有n个点,m条边 
	while(cin >> n >> m){
		printf("So your graph has %d edges and %d points.\nNow give these edges to me.\n",m,n);
		int lc = 0;
		priority_queue<Edge> pque;
		for(int i = 0;i < m;i++){
			int u,v;
			scanf("%d%d%d",&u,&v,&lc);
			pque.push(Edge(u,v,lc));
		}
		cout << kruskal(pque)<< endl;
	}
	return 0;
}
