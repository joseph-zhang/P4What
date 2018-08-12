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
bool sieve[10000];
int  step[10000];
int s,e;
int ok;
void linearSieve(){
	int prime[10000];
	int indi = 0;
	for(int i = 2;i < 10000;i++){
		if(!sieve[i]) prime[indi++] = i;
		for(int j = 0;prime[j]*i < 10000;j++){
			sieve[i*prime[j]] = true;
			if(i%prime[j] == 0) break;
		}
	}
} 
void bfs(){
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int temp = q.front();q.pop();
		int tuple[4];
		int orig = temp;
		for(int i = 0;i < 4;i++){
			tuple[3-i] = temp % 10;
			temp /= 10;
		}
		for(int i = 0;i < 4;i++){
			int num = tuple[i]; 
			for(int j = 0;j < 10;j++){
				if(i == 0 && j == 0) continue;
				if(num == j) continue;
				int newnum = 0;
				for(int k = 0;k < 4;k++){
					if(k != i) newnum = newnum*10+tuple[k];
					else newnum = newnum*10+j;
				}
				if(step[newnum] || sieve[newnum]) continue;
				step[newnum] = step[orig]+1;
				q.push(newnum);
			}
		}
		if(step[e]){ok = 1;break;}
	}
}
int main(){
	int m;
	cin >> m;
	linearSieve();
	while(m--){
		cin >> s >> e;
		if(s == e) {cout << 0 << endl;continue;}
		memset(step,0,sizeof(step));
		ok = 0;
		bfs();
		if(ok) cout << step[e] << endl;
		else cout << "Impossible" <<endl;
	}
	return 0;
}


