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
*    ISAP���㷨,�������������.�״γ����� Ahuja �� Orlin �Ľ̲���.
*    ��������d[i],��ʾʣ�������нڵ�i�����t������½�,����������л᲻�ϱ�����.
*    ������ d[i]=d[j]+1 �Ļ� i->j Ϊ"����".�����ʱ��ֻ��������������,��Ȼ�У�
*        (1)d[t] = 0;
*        (2)��ʣ�������϶����⻡(i,j),���� d[i]<=d[j]+1;
*        (3)�� d[s]>=n ʱ,ʣ�������в�����s-t·.
*    ISAP ��˼��ܼ�:������·�Ĺ��̾��Ǵ�Դ��s����"����"��ǰ��(Advance).
*    ������ߵĹ������߲�����,������һ��,����������:
*        (1)�ڴӽ��i�����ߵ�ʱ��,����d[i]Ϊ d[i]= min{d[j]|(i,j)��ʣ�������еĻ�}+1 (Retreat).
*        (2)����i����û�л�,������ d[i]=n.
*    �����ʵ������һЩ����:
*        (1)ʹ��"��ǰ��"������"����"�Ĳ���.
*           "��ǰ��"�ṹ:cur[i] �Ǵӽ��i����ǰ��ʱ,��i���������еĻ����߶���¼.
*        (2)ʹ��num[i]�����Ż�:�±�i�Ǿ���,ֵ������d[k]=i�ĵ�ĸ���.
*           ��һ�����ľ����Ŵ�x�ĵ�yʱ,num[x]��1,num[y]��1,Ȼ����num[x]�Ƿ�Ϊ��/
*           ��Ϊ��,˵��s,t����ͨ,�㷨��ֹ.(���gap�Ż�)
*        (3)����ʹ��BFS�ҳ�d[]�ĳ�ʼֵ.(��t��ʼ��������BFS)
*           Ҳ���Խ�d[i]��ʼֵȫ��Ϊ��.
*           ����ִ��ISAPЧ������,�����Ƕ�����С��ģ������,����BFS����Ч������������.
*/
struct Edge{
	int from,to,cap,flow;
	Edge(){}
	Edge(int from_,int to_,int cap_,int flow_):
			from(from_),to(to_),cap(cap_),flow(flow_){}
};

const int maxn = 100;
const int maxm = 10000;
int n,m;
int p[maxn]; //��¼����·
int num[maxn];//�����ż���
int d[maxn]; //����ľ�������d
int cur[maxn]; //��ǰ���ṹ
bool vis[maxn];//BFS������
Edge edges[maxm];
vector<int> G[maxn];
int r; //�ڵ���������
void addEdge(int from,int to,int cap){
	edges[r++] = Edge(from,to,cap,0);
	G[from].push_back(r-1);
	edges[r++] = Edge(to,from,0,0);
	G[to].push_back(r-1);
}
//BFS����,���d[i]��ʼֵ
void BFS(int s,int t){
	memset(vis,false,sizeof(vis));
	queue<int> que;
	que.push(t);
	vis[t] = true;
	d[t] = 0;
	while(!que.empty()){
		int x = que.front();que.pop();
		for(int i = 0;i < G[x].size();i++){
			Edge& e = edges[G[x][i]];
			if(!vis[e.to]){
				d[e.to] = d[x]+1;
				vis[e.to] = true;
			}
		}
	}
}
//�������
int Augment(int s,int t){
	int x = t,a = INF;
	//���Ż�ȥ�������ֵa
	while(x!=s){
		Edge& e = edges[p[x]];
		a = min(a,e.cap-e.flow);
		x = edges[p[x]].from;
	}
	x = t;
	//�ٵ�����һ���������
	while(x!=s){
		edges[p[x]].flow += a;
		edges[p[x]^1].flow -= a;
		x = edges[p[x]].from;
	}
	return a;
}

//���ع���
int Maxflow(int s,int t){
	BFS(s,t);        //������BFS���d[]�ĳ�ʼֵ
	int flow = 0;
	memset(num,0,sizeof(num));
	for(int i = 0;i < n;i++)num[d[i]]++;
	int x = s;    //��Դ��s��ʼ
	memset(cur,0,sizeof(cur));
	//�ӵ�ǰ���x����,�������ǰ������,�������tʱ�Ϳ��Խ�������
	while(d[s]<n){
		if(x==t){ //�ߵ���t,��������
			flow+=Augment(s,t);
			x = s;
		}
		bool ok = false;
		for(int i = cur[x];i < G[x].size();i++){
			Edge& e = edges[G[x][i]];
			if(e.cap > e.flow && d[x]==d[e.to]+1 ){ //����������
				ok = true;
				p[e.to] = G[x][i];
				cur[x] = i;
				x = e.to;
				break;
			}
		}
		if(!ok){ //�������߲�����,��x ����Retreat
			int k = n-1;
			for(int i = 0;i < G[x].size();i++){
				Edge& e = edges[G[x][i]];
				if(e.cap > e.flow) k = min(k,d[e.to]); //��min{d[j]|(x,j)��ʣ�������еĻ�}
			}
			if(--num[d[x]] == 0)break; //gap�Ż�
			num[d[x] = k+1]++;        //d[x]= min{d[j]|(x,j)��ʣ�������еĻ�}+1 
			cur[x] = 0;
			if(x!=s) x = edges[p[x]].from; //����һ��
		}
	}
	return flow;
}
int main(){
	freopen("input.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i = 0;i < m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			addEdge(u,v,c);
		}
		int qurey;scanf("%d",&qurey);
		while(qurey--){
			memset(p,0,sizeof(p));
			int s,t;scanf("%d%d",&s,&t);
			printf("%d\n",Maxflow(s,t));
		}
	}
	return 0;
}
