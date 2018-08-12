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
*    ��-˫��ͨ����(���˫��ͨ����Biconnected Component/��Block),������ͼ��-˫��ͨ�ļ�����ͼ.
*    ��-˫��ͨ:�ڲ�û�йؽڵ�(�).
*    ���-BCC������Tarjan�ķ���(Tarjan���������㷨�ܶ�,ע������).
*    ÿ���߶�ǡ������һ����-BCC,���ǲ�ͬ��������-BCC�����й������(���һ��),�����Ǹ.
*    ������,ÿ�������������ͬ��-BCC�Ĺ������,����ֻҪ�ҳ����еĸ����.
*    ÿ�ҵ�һ���,���Ǿ�֪������һ��BCC,�������㷨���̺ͺ�������һ��.
*    ʵ��ʱ��ջ������"��ǰBCC"�еı�(�����ǵ�).
*    ����ʵ�ֵĳ�ʽ�Ե���ڽӱ�ͼ.
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
int bccno[maxn];//�����ĸ�BCC
int dfs_clock;  //����ʱ���
int bcc_cnt;    //BCC����������(��1��ʼ���)
vector<int> G[maxn],bcc[maxn];
stack<Edge> stk;//�ݴ�ߵ�ջ

//���ѹ���,�������ϵ�lowֵ�������
int dfs(int u,int fa){
	int lowu = pre[u] = ++dfs_clock;
	int child = 0;
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		Edge e = Edge(u,v);
		if(!pre[v]){  //��û�ݷù�,�ߵ�������
			stk.push(e);
			child++;
			int lowv = dfs(v,u);
			lowu = min(lowu,lowv);
			if(lowv >= pre[u]){ //u�Ǹ
				iscut[u] = true;
				bcc[++bcc_cnt].clear();
				for(;;){
					//��ջ��ǰ����Щ���ǵ����˵㶼���μӽ��µ�BCC
					Edge x = stk.top();stk.pop();
					if(bccno[x.u] != bcc_cnt){
						bcc[bcc_cnt].push_back(x.u);
						bccno[x.u] = bcc_cnt;
					}
					if(bccno[x.v] != bcc_cnt){
						bcc[bcc_cnt].push_back(x.v);
						bccno[x.v] = bcc_cnt;
					}
					if(x.u == u && x.v == v)break;//�ص���ԭ���ıߵ�λ��
				}
			}
		}else if(pre[v] < pre[u] && v != fa){//ԭ���ݷù�,�ߵ��Ƿ����
			stk.push(e);//�����ҲҪ�ӽ���
			lowu = min(lowu,pre[v]);
		}
	}
	if(fa < 0 && child == 1) iscut[u] = 0; //����������
	return lowu;
}

//���ع���
void Tarjan(){
	//��ʼ��
	memset(pre,0,sizeof(pre));
	memset(iscut,false,sizeof(iscut));
	memset(bccno,0,sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	//��BCC
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
	printf("The Biconnected Component are showed below.\n");
	for(int i = 1;i <= bcc_cnt;i++){
		cout << "BCC#" << i << endl;
		for(int j = 0;j < bcc[i].size();j++)
			cout << bcc[i][j] << " ";
		cout << endl;
	}
	return 0;
}
