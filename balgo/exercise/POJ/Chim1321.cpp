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
using namespace std;
int n,k;
char region[9][9];
bool ocu[9];
int res;
void dfs(int row,int login){
	if(login == k){
		res++;
		return;
	}
	if(row > n || (login + n - row + 1) < k) return;
	dfs(row+1,login);
	for(int i = 0;i < n;i++){
		if((!ocu[i]) && region[row][i] == '#'){
			ocu[i] = true;
			dfs(row+1,login+1);
			ocu[i] = false;
		}
	}
}

int main(){
	while(cin >> n >> k){
		if(n == -1 && k == -1) break;
		for(int i = 0;i < n;i++){
			ocu[i] = false;
			for(int j = 0;j < n;j++){
				cin >> region[i][j];
			}
		}
		res = 0;
		dfs(0,0);
		cout << res << endl;
	}
	return 0;
}
