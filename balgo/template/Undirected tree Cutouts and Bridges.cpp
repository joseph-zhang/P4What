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
#define Uint unsigned int
using namespace std;

/**
*    �ź͹ؽڵ�(�)������ͼ�е���Ҫ�ṹ,�������ۼٶ�ͼ����ͨ��.
*    �Ҹ���ŵķ�������һ��,����ͬʱ����,����������DFS��,������ͼ����DFS.
*    (ע��:�����Ҫ��,����ע�ⲻҪ��ȥ��)
*    �жϽ��u�ǲ��Ǹ:
*        (1)u���Ǹ�:���ڴ�u����ȥ��������,ֻҪ��һ������û������u���ȵķ����,u���Ǹ.
*           (Ҳ����˵,���u�������Ƕ�������u���ȵķ����,u�Ͳ��Ǹ)
*        (2)u�Ǹ�:�Ƚϼ�,Ҫ��u�в�ֹһ������,u���Ǹ. 
*    ����pre��post:pre(u)��dfs�״η���uʱ��ʱ���,post(u)��dfs����uʱ��ʱ���.
*    ����lowֵ:low(u)��u��׷�ݵ������类dfs���ֵ������ȵ�preֵ.
*    ���һ��,���ڷǸ��ڵ�u,u�Ǹ���ҽ�������u���ӽڵ�v,low(v)>=low(u);
*    ���Ҹʱ����˳������,����low(v)>low(u),�ž��Ǳ�(u,v),����u�Ǹ;
*    (ע��������ر�,������һ����Ϊ����,���඼���������)
*    ������ʽ��ͼ�ṹ��ǰ����,�ٶ�û���ر�.
*/
struct Edge{
	int u,v;
	Edge(){}
	Edge(int u_,int v_):u(u_),v(v_){}
};
const int maxn = 200;
const int maxm = 1000;
int n,m;
int pre[maxn];  //����ʱ��ʱ��
bool iscut[maxn];//�ǲ��Ǹ(�ؽڵ�)
bool isbridge[maxm];//�ǲ�����
int dfs_clock;  //����ʱ���
int low[maxn];  
int ei;        //�߼���������
Edge edges[maxm];
vector<int> G[maxn];


//���ѹ���,�������ϵ�lowֵ�������.
int dfs(int u,int fa){
	int lowu = pre[u] = ++dfs_clock;//��¼ʱ��
	int child = 0;
	for(int i = 0;i < G[u].size();i++){
		Edge& e = edges[G[u][i]];
		int v = e.v;
		if(!pre[v]){
			child++;
			int lowv = dfs(v,u);
			lowu = min(lowu,lowv); //���Ը���low(u)
			if(lowv >= pre[u])iscut[u] = true;
			if(lowv > pre[u])isbridge[G[u][i]] = true;
		}else if(pre[v] < pre[u] && v != fa)lowu = min(lowu,pre[v]);//�����ֻ��,����ȥ
	}
	if(fa < 0 && child == 1)iscut[u] = false; //���������ĸ������
	low[u] = lowu;
	return lowu;
}

void findBridge(){
	//��ʼ��
	memset(pre,0,sizeof(pre));
	memset(iscut,false,sizeof(iscut));
	memset(isbridge,false,sizeof(isbridge));
	dfs_clock = 0;
	//���Դ�ÿ���㿪ʼ��
	for(int i = 0;i < n;i++)
		if(!pre[i])dfs(i,-1);
}

void addEdge(int u,int v){
	edges[ei++] = Edge(u,v);
	G[u].push_back(ei-1);
	edges[ei++] = Edge(v,u);
	G[v].push_back(ei-1);
}
int main(){
	ei = 0;
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your graph.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		addEdge(u,v);
	}
	printf("finding...\n");
	findBridge();
	printf("articulation vertex sequence:\n");
	for(int i = 0;i < n;i++)if(iscut[i])cout << i << " ";
	cout << endl;
	printf("Bridge sequence:\n");
	for(int i = 0;i < (m<<1);i++)
		if(isbridge[i])printf("(%d,%d)\n",edges[i].u,edges[i].v);
	return 0;
}
