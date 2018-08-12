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
bool G[28][28];
int N;
bool ok = false;
int color[28];
void dfs(int dot,int c,const int k){
	if(dot == N){
		ok = true;
		return;
	}
	for(int i = 0;i < N;i++){
		if(G[dot][i] && color[i] == c)
			return;
	}
	color[dot] = c;
	for(int i = 1;i <= k;i++){  
		if(color[0] != 1) return; 
		dfs(dot+1,i,k);
		if(ok) return;
	}
	color[dot] = 0;
}
int main(){
	while(cin >> N){
		if(!N) break;
		char str[N+2][28];
		memset(G,false,sizeof(G));
		int res = 0;
		for(int i = 0;i < N;i++){
			cin >> str[i];
		}
		for(int i = 0;i < N;i++){
			int p = str[i][0] - 'A';
			for(int j = 2;str[i][j];j++)
				G[p][str[i][j] - 'A'] = G[str[i][j] - 'A'][p] = true;
		}
		for(int i = 1;i <=N;i++){
			memset(color,0,sizeof(color));
			ok = false;
			dfs(0,1,i);
			if(ok){res = i;break;}
		}
		cout << res << ((res > 1)?" channels ":" channel ") << "needed." << endl;
	}
	return 0;
}
