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
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
int d[4098][4098],vis[4098][4098];
int cnt[4098][4098];
int val[130];
int M,N,kase = 0;
//记忆化搜索
int dp(int s,int a){
	if(cnt[s][a] <= 1){d[s][a] = 0;return 0;}
	if(cnt[s][a] == 2){d[s][a] = 1;return 1;}
	if(vis[s][a] == kase)return d[s][a];
	d[s][a] = M;vis[s][a] = kase;
	//尝试对某一位询问
	for(int i = 1;i != 1 << M;i <<= 1){
		if(!(s&i)){
			int tmps = max(dp(s|i,a),dp(s|i,a|i))+1;
			d[s][a] = min(d[s][a],tmps);
		}
	}
	return d[s][a];
}
int main(){
	char str[16];
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> M >> N){
		if(!(M||N))break;
		++kase;
		memset(val,0,sizeof(val));
		for(int i = 0;i < N;i++){
			scanf("%s",str);
			for(int j = 0;j < M;j++){
				if(str[j]-'0')val[i] |= (1<<j);
			}
		}
		for(int s = 0;s < (1 << M);s++){
			for(int a = s;a;a = (a-1)&s)
				cnt[s][a] = 0;
			cnt[s][0] = 0;
		}
		//预处理
		for(int s = 0;s < (1 << M);s++){
			for(int j = 0;j < N;j++){
				int a = val[j]&s;
				cnt[s][a]++;
			}
		}
		dp(0,0);
		//printf("Kase: %d ",++kase);
		cout << d[0][0] << endl;
	}
	return 0;
}


