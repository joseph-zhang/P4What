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

int d[120000];
int n,k;
void Search(){
	fill(d,d+110000,INF);
	queue<int> que;
	d[n] = 0;
	que.push(n);
	while(!que.empty()){
		int u = que.front();que.pop();
		if(u+1 >= 0 && u+1 <= 100000 && d[u+1]==INF ){	que.push(u+1);d[u+1] = d[u]+1;}
		if(u-1 >= 0 && u-1 <= 100000 && d[u-1]==INF ){	que.push(u-1);d[u-1] = d[u]+1;}
		if(u+u >= 0 && u+u <= 100000 && d[u+u]==INF ){	que.push(u+u);d[u+u] = d[u]+1;}
		if(d[k]!=INF) break;
	}
}

int main(){
	while(cin >> n >> k){
		Search();
		cout << d[k] << endl;
	}
	return 0;
}

