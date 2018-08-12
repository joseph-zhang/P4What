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
	int u,v;
	double comi,rate;
	Edge(){}
	Edge(int n1,int n2,double c,double r):u(n1),v(n2),comi(c),rate(r){}
};
vector<Edge> edges;
int N,M,S;
double V;
bool detect(){
	double d[N+2];
	memset(d,0,sizeof(d));
	d[S] = V;
	bool ok = false;
	for(int i = 0;i < N-1;i++){
		ok = false;
		for(int j = 0; j < edges.size();j++){
			Edge& e = edges[j];
			int u = e.u,v = e.v;
			double rate = e.rate,comi = e.comi;
			if((d[u] - comi)*rate > d[v]){
				d[v] = (d[u] - comi)*rate;
				ok = true;
			}
		}
		if(!ok) break;
	}
	for(int i = 0;i < edges.size();i++){
			Edge& e = edges[i];
			int u = e.u,v = e.v;
			double rate = e.rate,comi = e.comi;	
			if((d[u] - comi)*rate > d[v]) return true;
	}
	return false;
}
int main(){
	cin >> N >> M >> S >> V;
	int ue,ve;
	double rab,cab,rba,cba;
	for(int i = 0 ;i < M;i++){
		cin >> ue >> ve >> rab >> cab >> rba >> cba;
		edges.push_back(Edge(ue,ve,cab,rab));
		edges.push_back(Edge(ve,ue,cba,rba));
	}
	if(detect()) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}

