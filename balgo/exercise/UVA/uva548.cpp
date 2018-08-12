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
#include<sstream>
#include<algorithm>
#include<cstdlib>
#include<stack>
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
const int maxn = 10000+10;
int Left[maxn],Right[maxn];
int inorder[maxn],postorder[maxn];
int N,u = 12000,res = 120000000;
bool readInput(int *arr){
	N = 0;
	string line;
	int x;
	if(!getline(cin,line))return false;
	stringstream ss(line);
	while(ss >> x)arr[++N] = x;
	return N > 0;
}
int build(int L1,int R1,int L2,int R2){
	if(L1 > R1) return 0;
	int root = postorder[R2];
	int pi = L1;
	while(inorder[pi] != root) pi++;
	int cntLeft = pi - L1;
	Left[root] = build(L1,pi-1,L2,L2+cntLeft-1);
	Right[root] = build(pi+1,R1,L2+cntLeft,R2-1);
	return root;
}
void dfs(int root,int sum){
	sum += root;
	if((!Left[root]) && (!Right[root])){
		if(sum < res || (sum == res && root < u)){
			u = root;
			res = sum;
		}
		return;
	}
	if(Left[root])dfs(Left[root],sum);
	if(Right[root])dfs(Right[root],sum);
}
int main(){
	while(readInput(inorder)){
		u = 12000;res = 120000000;
		memset(Left,0,sizeof(Left));
		memset(Right,0,sizeof(Right));
		readInput(postorder);
		build(1,N,1,N);
		dfs(postorder[N],0);
		cout << u << endl;
	}
	return 0;
}
