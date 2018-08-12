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
#define INF 1000000000
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
const int maxn = 125;
const int maxm = 25;
const int maxs = 10;
int S,M,N;
int cable[maxn],costs[maxn];
int d[maxn][1<<maxs][1<<maxs];
int dp(int i,int s0,int s1,int s2){
	if(i == M+N)return s2 == (1 << S)-1?0:INF;
	int& ds = d[i][s1][s2];
	if(ds >= 0)return ds;
	ds = INF;
	if(i >= M)ds = dp(i+1,s0,s1,s2);
	int p0 = cable[i]&s0;int p1 = cable[i]&s1;
	s0 ^= p0;s1 = (s1^p1)|p0;s2 = s2|p1;
	ds = min(ds,dp(i+1,s0,s1,s2)+costs[i]);
	return ds;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int cab;string line;
	while(getline(cin,line)){
		stringstream ss(line);
		ss >> S >> M >> N;
		if(!S)break;
		for(int i = 0;i < M+N;i++){
			getline(cin,line);
			stringstream ss(line);
			ss >> costs[i];
			cable[i] = 0;
			while(ss >> cab){cable[i] |= (1 << (cab-1));}
		}
		memset(d,-1,sizeof(d));
		cout << dp(0,(1 << S)-1,0,0) << endl;
	}
	return 0;
}

