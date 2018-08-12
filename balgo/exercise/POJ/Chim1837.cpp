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

const int mw = 15000;
const int bw = 7500;
int weight[21];
int hook[21];
int d[21][15002];
int main(){
	int c,g;
	cin >> c >> g;
	memset(d,0,sizeof(d));
	for(int i = 0;i < c;i++) cin >> hook[i];
	for(int i = 0;i < g;i++) cin >> weight[i];
	for(int i = 0;i < c;i++) d[0][bw+hook[i]*weight[0]]++;
	for(int i = 1;i < g;i++)
		for(int j = 0;j < c;j++)
			for(int k = 0;k <= mw;k++){
				int bpre = k - hook[j]*weight[i];
				if(bpre < 0 || bpre > mw) continue;
				if(d[i-1][bpre]) d[i][k] += d[i-1][bpre];
			}
	cout << d[g-1][bw] << endl;
	return 0;
}

