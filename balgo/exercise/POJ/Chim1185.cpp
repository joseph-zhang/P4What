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
#define sys std::ios::sync_with_stdio(false);
using namespace std;
int pres[1200],cnt[1200];
int ps = 0;
int N,M;
int grid[120];
void init(){
	memset(cnt,0,sizeof(cnt));
	memset(grid,0,sizeof(grid));
	for(int i = 0;i < (1 << M);i++){
		if((i&(i<<1))||(i&(i<<2)))continue;
		pres[ps++] = i;
		int temp = i;
		for(;temp;temp &= (temp-1))
			cnt[ps-1] += 1;
	}
}
int main(){ 
	cin >> N >> M;
	init();
	char str[14];
	for(int i = 1;i <= N;i++){
		scanf("%s",str);
		for(int j = 0;j < M;j++){
			grid[i] <<= 1;
			if(str[j] == 'H')grid[i] += 1;
		}
	}
	int dp[N+2][ps+4][ps+4];
	memset(dp,0,sizeof(dp));
	for(int r = 1;r <= N;r++){
		for(int i = 0;i < ps;i++){
			for(int j = 0;j < ps;j++){
				for(int k = 0;k < ps;k++){
					if((pres[i]&grid[r]))
						continue;
					if((pres[i]&pres[j])||(pres[i]&pres[k]))
						continue;
					dp[r][i][j] = max(dp[r][i][j],dp[r-1][j][k]+cnt[i]);
					
				}
			}
		}
	}
	int res = 0;
	for(int i = 0;i < ps;i++)
		for(int j = 0;j < ps;j++)
			res = max(res,dp[N][i][j]);
	cout << res << endl;
	return 0;		
}
