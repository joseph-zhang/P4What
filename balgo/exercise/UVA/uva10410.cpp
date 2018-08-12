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

const int maxn = 1002;
int n;
int pos[maxn];
vector<int> tree[maxn];


void print(){
	for(int i = 1;i <= n;i++){
		printf("%d:",i);
		for(int j = 0;j < tree[i].size();j++)
			printf(" %d",tree[i][j]);
		cout << endl;
	}
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> n){
		int node;
		for(int i = 0;i < n;i++){
			scanf("%d",&node);
			pos[node] = i;
			tree[node].clear();
		}
		stack<int> stk;
		int root;
		scanf("%d",&root);
		stk.push(root);
		for(int i = 1;i < n;i++){
			scanf("%d",&node);
			while(true){
				int u = stk.top();
				if((pos[u]+1==pos[node] && node<u)||(pos[u]+1 < pos[node])||(u==root)){
					tree[u].push_back(node);
					stk.push(node);
					break;
				}
				else stk.pop();
			}
		}
		print();
	}
	return 0;
}
