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
*    ���ı�������������,����������в�һ���ܰ�������ȫ����Ϣ.
*    �����������������:ͨ�����а�������ԭ����.
*    ����ı���:����-����-����,��������bfs��dfs.
*    ������Ϊ����:
*    (1)������������,������.
*    (2)��Сֵ���ȵ�bfs,dfs����.
*/
const int maxn = 1002;
int n;
vector<int> tree[maxn];

/*(1)�ݹ�ؽ���*/
int build(int *preod,int *inod,int ps,int pe,int is,int ie){
	if(ps>pe)return -1;
	int pos = is;
	while(inod[pos]!=preod[ps])pos++;
	tree[inod[pos]].push_back(build(preod,inod,ps+1,ps+pos-is,is,pos-1));
	tree[inod[pos]].push_back(build(preod,inod,ps+pos-is+1,pe,pos+1,ie));
	return inod[pos];
}

/*(2)����ջ��ģ��dfs������ɽ���*/
void solve(int* bfsod,int* dfsod){
	int pos[maxn];
	for(int i = 0;i < n;i++){
		pos[bfsod[i]] = i;
		tree[bfsod[i]].clear();
	}
	stack<int> stk;
	int root = dfsod[0];
	stk.push(dfsod[0]);
	for(int i = 1;i < n;i++){
		int node = dfsod[i];
		while(true){
			int u = stk.top();
			if((pos[u]+1 < pos[node])||(pos[u]+1==pos[node] && node < u)||(u==root)){
				tree[u].push_back(node);
				stk.push(node);
				break;
			}else stk.pop();
		}
	}
}

int main(){
	int seq1[maxn],seq2[maxn];
	printf("how many number? ");
	scanf("%d",&n);
	printf("give me two sequence.\n");
	for(int i = 0;i < n;i++)cin >> seq1[i];
	for(int i = 0;i < n;i++)cin >> seq2[i];
	printf("building...\n");
	//solve(seq1,seq2);
	build(seq1,seq2,0,n-1,0,n-1);
	for(int i = 1;i <= n;i++){
		printf("%d:",i);
		for(int j = 0;j < tree[i].size();j++)
			printf(" %d",tree[i][j]);
		cout << endl;
	}
	return 0;
}
