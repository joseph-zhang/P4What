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
#include<sstream>
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
int N;
int cube[32][3],d[32][3];
void getDim(int* v,int a,int b){
	int dx = 0;
	for(int i = 0;i < 3;i++){
		if(i == b)continue;
		v[dx++] = cube[a][i];
	}
}
int dp(int a,int b){
	int& ans = d[a][b];
	if(ans > 0)return ans;
	ans = 0;
	int v[2],v1[2];
	getDim(v,a,b);
	for(int i = 0;i < N;i++){
		for(int j = 0;j < 3;j++){
			getDim(v1,i,j);
			if(v[0] > v1[0] && v[1] > v1[1])
				ans = max(ans,dp(i,j));
		}
	}
	ans+=cube[a][b];
	return ans;
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int kase = 0;
	while(cin >> N){
		if(!N)break;
		for(int i = 0;i < N;i++){
			scanf("%d%d%d",&cube[i][0],&cube[i][1],&cube[i][2]);
			sort(cube[i],cube[i]+3);
		}
		memset(d,0,sizeof(d));
		int res = 0;
		for(int i = 0;i < N;i++){
			for(int j = 0;j < 3;j++)
				res = max(res,dp(i,j));
		}
		printf("Case %d: maximum height = %d\n",++kase,res);
	}
	return 0;
}

