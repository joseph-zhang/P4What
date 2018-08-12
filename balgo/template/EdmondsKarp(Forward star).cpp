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

/** 
*    EdmondsKarp �� Ford-Fulkerson���� ��һ��ʵ��.
*    ������˵,����Ford-Fulkerson������������·����һ����,��BFS����̵�.
*    ����֤��,�����s-t·����,��ҪO(nm)������.
*    ÿ��������BFSѰ������·,��ҪO(m).��ʱ�临�Ӷ�ΪO(n*m^2)
*    ���г�ʽ��ʵ�ֲ��ñߵ��ڽӱ�(ǰ����),����ͼ������ͼ.
*/
const int maxn = 50;//��������
const int maxm = 100<<1; //��������
struct Edge{
	int from,to;
	int cap,flow;
	Edge(){}
	Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
int r = 0; //�����������
Edge edges[maxm];
vector<int> G[maxn];//ǰ���ǽṹ
int p[maxn]; //��¼�ѵ����������·
void addEdge(int from,int to,int cap){
	edges[r++] = Edge(from,to,cap,0);
	G[from].push_back(r-1);
	edges[r++] = Edge(to,from,0,0);
	G[to].push_back(r-1);
}
int EDK(int s,int t){
	int flow = 0;
	int a[maxn];//a�����¼Ŀǰ�ѵ���·���ϴ�s��i����Сʣ��
	for(;;){
		memset(a,0,sizeof(a));
		queue<int> que;
		que.push(s);a[s] = INF;
		while(!que.empty()){//ʵ���Ͼ��Ǹ�BFS
			int x = que.front();que.pop();
			for(int i = 0;i < G[x].size();i++){
				Edge& e = edges[G[x][i]];
				if(!a[e.to] && e.cap > e.flow){ //!a[e.to]��Ϊ�˲���
					que.push(e.to);
					a[e.to] = min(a[x],e.cap-e.flow);
					p[e.to] = G[x][i];
				}
			}
			if(a[t])break;//���ҵ�������s-t����·
		}	
		if(!a[t])break;//�Ѿ�û������·����
		for(int u = t;u!=s;u = edges[p[u]].from){
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
		}
		flow += a[t]; 
	}
	return flow;
}
int main(){
	freopen("input.txt","r",stdin);
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i = 0;i < m;i++){
			int u,v,c,f;
			scanf("%d%d%d",&u,&v,&c);
			addEdge(u,v,c);
		}
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			memset(p,0,sizeof(p));
			int s,t;scanf("%d%d",&s,&t);
			printf("%d\n",EDK(s,t));
		}
	}
	return 0;
}

