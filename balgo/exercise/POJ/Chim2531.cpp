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

int N;
int G[22][22];
int s1[22],s2[22];
int ts = 0;
void dfs(int sum,int n1,int n2,int cur){
	if(sum > ts) return;
	if(cur == N){
		ts = sum;
		return;
	}
	int curadd = 0,temp;
	temp = s1[n1];
	s1[n1] = cur;
	for(int i = 0;i < n1;i++)
		curadd += G[s1[i]][cur];
	dfs(sum+curadd,n1+1,n2,cur+1);
	s1[n1] = temp;
	
	curadd = 0;
	temp = s2[n2];
	s2[n2] = cur;
	for(int i = 0;i < n2;i++)
		curadd += G[s2[i]][cur];
	dfs(sum+curadd,n1,n2+1,cur+1);
	s2[n2] = temp;
}
int main(){
	cin >> N;
	int total = 0;
	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			scanf("%d",&G[i][j]);
			if(j > i)
				total += G[i][j];
		}
	}
	for(int i = 0;i < N/2;i++){
		for(int j = 0;j < N/2;j++){
			if(j <= i) continue;
			ts += G[i][j];
		}
	}
	for(int i = N/2;i < N;i++){
		for(int j = N/2;j < N;j++){
			if(j <= i) continue;
			ts += G[i][j];
		}
	}
	fill(s1,s1+21,-1);
	fill(s2,s2+21,-1);
	s1[0] = 0;
	dfs(0,1,0,1);
	int res = total - ts;
	cout << res << endl;
	return 0;
}
