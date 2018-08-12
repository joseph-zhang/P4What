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
#define INF 0x7fffffff 
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
int grid[14];
int dp[13][1<<13];
int M,N;
const int mask = 100000000;
bool judge(int i,int j){
	if((grid[i]|j) != grid[i]) return false;
	if(j&(j<<1))return false;
	return true;
}
int main(){
	cin >> M >> N;
	int res = 0;
	for(int i = 1;i <= M;i++){
		grid[i] = 0;
		for(int j = 0;j < N;j++){
			int c;scanf("%d",&c);
			grid[i] = (grid[i] << 1)+c;
		}
	}
	memset(dp,0,sizeof(dp));
	dp[0][0] = 1;
	for(int i = 1;i <= M;i++){
		for(int j = 0;j <(1<<N);j++){
			if(!judge(i,j)) continue;
			for(int k = 0;k <(1<<N);k++){
				if(k&j)continue;
				dp[i][j] += dp[i-1][k];
				dp[i][j] %= mask;
			}
		}
	}
	for(int i = 0;i < (1<<N);i++){
		res += dp[M][i];
		res %= mask;
	}
	cout << res << endl;
	return 0;
}
