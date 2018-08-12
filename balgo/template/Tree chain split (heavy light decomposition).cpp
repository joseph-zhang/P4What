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
*    �����ʷ�,��һ�ִ������ķ���,�������ʳ�һ��������.
*    �������кܺõ����㷨:���Θ�,BIT,Sparse-Table,BST,Heap...�ɾݴ���Ƹ�Ч�����㷨.
*    ������һ�ֻ��ֵ�˼����"����ֽ�",����DFS/BFS������,����ÿ����㶼�B���������Ә䡣
*    �ʷ�֮���������������������LCA.
*    �ʷ�:O(V);���������L�:O(VlogV);��ԃLCA:O(logV);��ԃһ�l·��:O((logV)^2).
*    ��ʽ�򵥸���,�Ե���ڽӱ���,����������Ϊ0,�������̲���DFS.
*/

const int maxn = 10000;
vector<int> G[maxn]; // adjacency list,��һ�Ø�
int parent[maxn],heavy[maxn]; //���c�ĸ��H�����غ���
int depth[maxn],cnt[maxn];    // ���c����ȡ��Ә���c��
int chain[maxn],head[maxn];  // ���c���������ı�š��������������_�^�����
int n,m;

//Traversal���̱�����,�����������Ҫ��parent,heavy,depth,size;
void DFS(int u){
	cnt[u] = 1;
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(v == parent[u])continue; //�����ѵ��ϵ�
		
		parent[v] = u;
		depth[v] = depth[u]+1;
		
		DFS(v);
		cnt[u] += cnt[v];
		if(heavy[u]==-1 || cnt[heavy[u]] < cnt[v])
			heavy[u] = v;
	}
}
//���ع���,�ҳ����ϵĸ�����,����ֽ�
void heavyLight(){
	memset(heavy,-1,sizeof(heavy));
	memset(chain,-1,sizeof(chain));
	parent[0] = -1;
	depth[0] = 0;
	
	DFS(0);
	int c = 0; // 朵ľ�̖������
	for(int i = 0;i < n;i++){
		if(chain[i]!=-1)continue;
		if(parent[i]==-1 || i != heavy[parent[i]]){
		// ��˵��i�c��朵��_�^���
			for(int k = i;k != -1;k = heavy[k]){
				chain[k] = c;
				head[k] = i;
			}
			c++;
		}
	}
}

int lca(int u,int v){
	//ÿ��ѡ�� ������ͷ������Ľ��������,ֱ������㴦��ͬһ����Ϊֹ.
	while(chain[u]!=chain[v]){
		if(depth[head[u]] > depth[head[v]]) u = parent[head[u]];
		else v = parent[head[v]];
	}
	return depth[u]<depth[v]?u:v;
}

int main(){
	printf("How many nodes and edges on your tree? ");
	cin >> n >> m;
	printf("Now give me your tree.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
	}
	printf("Constructing...\n");
	heavyLight();
	int qn;
	printf("LCA relationship between nodes:\n");
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++){
			int res = lca(i,j);
			printf("%d %d->%d\n",i,j,res);
		}
	}
	return 0;
}