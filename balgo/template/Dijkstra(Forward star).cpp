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
*    Dijkstra�Ǿ�������·���㷨,��������Ȩͼ.
*    ˼����̰�ĵ�(̰�ĵ�ǰ����û�и�Ȩ),����״̬�ռ���Ѱ���뷨,�������ɿ���Ȩ�ص�BFS.
*    ̰��˼��: ÿ��d[i]����С�߶�����̾����ѱ�ȷ���ĵ�,��Ϊͼ��û�и�Ȩ,����֮���������ܸ�С��.
*    ʵ��ʱ���������ȶ��м���: O(ElogV)
*    ��������ǳ��޴�,Ҳ�������ڽӾ���������Բ��ҵ�dijkstra: O(V^2)
*    ����ĳ�ʽ���������ȶ��м��ٵ���ʽ.
*/

const int maxn = 50;
const int maxm = 100<<1;
struct Edge{
	int from,to;
	int len;
	int nxt;
	Edge(){}
	Edge(int u,int v,int l,int f):from(u),to(v),len(l),nxt(f){}
};
//ע��STL��priority_queue �Ǵ����,�����������ȼ�
struct heapNode{
	int u,relx;//relx���ɳ���,��¼��ǰ�׶��½��u��s�����̾���
	heapNode(){}
	heapNode(int u_,int relx_):u(u_),relx(relx_){}
	bool operator < (const heapNode& rhs)const{
		return relx > rhs.relx;
	} 
};
Edge edges[maxm];
int d[maxn],p[maxn]; //d�Ǿ�������,p��¼��Dijkstra���Ľ���ϵ
int head[maxn]; //ǰ���Ǳ�ͷ
int r,n,m;
void addEdge(int u,int v,int len){ //����д��������ͼ�����Ը���������� 
	edges[r++] = Edge(u,v,len,head[u]);
	head[u] = r-1;
	edges[r++] = Edge(v,u,len,head[v]);
	head[v] = r-1;
}
void Dijkstra(int s){
	bool done[maxn];//��¼�����Ƿ��Ѿ���Dijkstra����
	memset(done,false,sizeof(done));
	for(int i = 0;i < n;i++)p[i] = i;
	for(int i = 0;i < n;i++)d[i] = INF; //��ʼ��(�����������·)
	priority_queue<heapNode> pque;
	d[s] = 0;pque.push(heapNode(s,0));
	while(!pque.empty()){
		heapNode node = pque.top();pque.pop(); //ÿ�������ɳ�����С�߼���Dijkstra��
		int u = node.u;
		if(done[u])continue;
		//if(done[t])break;
		done[u] = true;
		for(int i = head[u];i!=-1;i = edges[i].nxt){
			Edge& e = edges[i];
			if(d[e.to]>d[u]+e.len){ //�ɳڣ�
				d[e.to] = d[u]+e.len;
				p[e.to] = u;
				pque.push(heapNode(e.to,d[e.to]));
			}
		}
	}
}
void printPath(int s,int cur){
	if(cur == s){cout << s;return;}
	printPath(s,p[cur]);
	printf(" %d",cur);
}
int main(){
	freopen("input.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		r = 0;memset(head,-1,sizeof(head));
		for(int i = 0;i < m;i++){
			int u,v,l;
			scanf("%d%d%d",&u,&v,&l);
			addEdge(u,v,l);
		}
		Dijkstra(0);//����Dijkstra��
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			int t;scanf("%d",&t);
			printPath(0,t);cout << endl;
			printf("%d\n",d[t]);
		}
	}
	return 0;
}

