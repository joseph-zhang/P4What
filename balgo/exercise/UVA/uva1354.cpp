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
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
struct Tree{
	double L,R;
	Tree(){}
	Tree(double l1,double l2):L(l1),R(l2){}
};
const int maxn = 7;
double r,w[maxn],sum[1 << maxn];
int n,t;
vector<Tree> vec[1 << maxn];
bool vis[1 << maxn];
void backtracking(int subset){
	if(vis[subset])return;
	vis[subset] = true;
	bool hasChild = false;
	for(int left = (subset-1)&subset;left;left = (left-1)&subset){ //枚举真子集
		hasChild = true;
		int right = subset^left;
		double dl = sum[right]/sum[subset];
		double dr = sum[left]/sum[subset];
		backtracking(left);backtracking(right);
		
		for(int i = 0;i < vec[left].size();i++){
			for(int j = 0;j < vec[right].size();j++){
				double L = max(dl + vec[left][i].L,vec[right][j].L-dr);
				double R = max(vec[left][i].R-dl,vec[right][j].R+dr);
				if(L+R < r){
					Tree t = Tree(L,R);
					vec[subset].push_back(t);
				}
			}
		}
	}
	if(!hasChild) vec[subset].push_back(Tree());
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	cin >> t;
	while(t--){
		scanf("%lf%d",&r,&n);
		for(int i = 0;i < n;i++)cin >> w[i];
		//预处理,将各种状态对应的和算出来
		for(int i = 0;i < (1 << n);i++){
			vec[i].clear();
			sum[i] = 0;
			for(int j = 0;j < n;j++)
				if(i & (1 << j)) sum[i] += w[j];
		}
		
		int startSet = (1 << n)-1;
		memset(vis,false,sizeof(vis));
		backtracking(startSet);
		double res = -1;
		for(int i = 0;i < vec[startSet].size();i++){
			Tree t = vec[startSet][i];
			res = max(res,t.L+t.R);
		}
		printf("%.15lf\n",res);
	}
	return 0;
}
