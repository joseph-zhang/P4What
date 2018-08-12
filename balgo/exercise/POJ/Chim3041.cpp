#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<string.h>
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

bool adj[502][502];
int n,k;
int mx[502],my[502];
bool vis[502];
bool eds(int x){
	for(int y = 1;y <= n;y++){
		if(adj[x][y] && (!vis[y])){
			vis[y] = true;
			if(my[y]==-1 || eds(my[y])){
				my[y] = x;
				mx[x] = y;
				return true;
			}
		}	
	}
	return false;
}
int main(){
	while(cin >> n >> k){
		memset(adj,false,sizeof(adj));
		for(int i = 0;i < k;i++){
			int x1,x2;
			cin >> x1 >> x2;
			adj[x1][x2] = true;
		}
		fill(mx,mx+500,-1);
		fill(my,my+500,-1);
		int cnt = 0;
		for(int i = 1;i <= n;i++){
			memset(vis,false,sizeof(vis));
			if(eds(i)) cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}
