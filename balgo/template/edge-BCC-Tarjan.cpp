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
*    ��-˫��ͨ����(�������ͨ����Bridge-connected Component),������ͼ��-˫��ͨ�ļ�����ͼ
*    ��-˫��ͨ:�ڲ�û����.
*    �����Ų������κα�-˫��ͨ����֮��,����ÿ���߶�ǡ������һ����-˫��ͨ����.
*    ����ͨ����֮��û�й������,�������������˫��ͨ��������Щ,����˵��������.
*    (ʵ�������ź��ҹؽڵ���ͬһ�����㷨,������Ҳ��Tarjan�ķ���)
*    ��Ϊ�ݴ���ǵ㻹û�й������,���ʵ�ֺ�SCC��Tarjan�͸�����,��һ��ջ����"��ǰ��-BCC"�еĵ�.
*    ��������ͨ����Ҳ������SCC������������,��Ϊû�й�������.
*    ����ʵ�ֵĳ�ʽ�Ե���ڽӱ�ͼ.
*/

const int maxn = 200;
const int maxm = 1000;
int n,m;
int pre[maxn];  //����ʱ��ʱ��
int bccno[maxn];//�����ĸ���-BCC
int dfs_clock;  //����ʱ���
int low[maxn];
int bcc_cnt;    //��-BCC����������(��1��ʼ���)
vector<int> G[maxn],bcc[maxn];
stack<int> stk;//�ݴ���ջ

//���ѹ���,����SCC�ĺ���
int dfs(int u,int fa){
	low[u] = pre[u] = ++dfs_clock;
	stk.push(u);
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(!pre[v]){
			dfs(v,u);
			low[u] = min(low[u],low[v]);
		}else if(v!=fa && !bccno[v]){
			low[u] = min(low[u],pre[v]);
		}
	}
	if(pre[u] == low[u]){
		bcc[++bcc_cnt].clear();
		int x;
		do{
			x = stk.top();stk.pop();
			bcc[bcc_cnt].push_back(x);
			bccno[x] = bcc_cnt;
		}while(x!=u);
	}
}
//���ع���
void Tarjan(){
	//��ʼ��
	memset(pre,0,sizeof(pre));
	memset(bccno,0,sizeof(bccno));
	bcc_cnt = dfs_clock = 0;
	//�ұ�-BCC
	for(int i = 0;i < n;i++)
		if(!pre[i])dfs(i,-1);
}
int main(){
	printf("How many nodes and edges? ");
	scanf("%d%d",&n,&m);
	printf("Now give me your graph.\n");
	for(int i = 0;i < m;i++){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	printf("finding...\n");
	Tarjan();
	printf("The Bridge-connected Component are showed below.\n");
	for(int i = 1;i <= bcc_cnt;i++){
		cout << "BCC#" << i << endl;
		for(int j = 0;j < bcc[i].size();j++)
			cout << bcc[i][j] << " ";
		cout << endl;
	}
	return 0;
}
