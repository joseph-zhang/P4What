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
const int sz = 36;
bool vis[18];
bool seive[sz];
int res[20];
int N;
void Sei(){
	int prime[sz];
	int p = 0;
	memset(seive,false,sizeof(seive));
	seive[0] = seive[1] = true;
	for(int i = 2;i < sz;i++){
		if(!seive[i]) prime[p++] = i;
		for(int j = 0;i*prime[j]< sz;j++){
			seive[i*prime[j]] = true;
			if(i%prime[j] == 0)break;
 		}
	}
}
void backtracking(int x){
	if(x == N){
		if(!seive[res[0] + res[N-1]]){
			for(int i = 0;i < N-1;i++)
				cout << res[i] << " ";
			cout << res[N-1] << endl;
		}
		return;
	}
	for(int i = 2;i <= N;i++){
		if(!seive[i+res[x-1]] && !vis[i]){
			res[x] = i;
			vis[i] = true;
			backtracking(x+1);
			vis[i] = false;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int time = 0;
	Sei();
	vis[1] = true;
	res[0] = 1;
	while(cin >> N){
		if(time)cout << endl;
		printf("Case %d:\n",++time);
		backtracking(1);
	}
	return 0;
}
