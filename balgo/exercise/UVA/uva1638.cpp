#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
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
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define ULL unsigned LL
using namespace std;
ULL d[25][25][25];

int main(){
	memset(d,0,sizeof(d));
	d[1][1][1] = 1;
	for(int i = 2;i<=20;i++){
		for(int j = 1;j <= i;j++){
			for(int k = 1;k <= i;k++){
				d[i][j][k] = d[i-1][j-1][k] +
								d[i-1][j][k-1] +
									(i-2)*d[i-1][j][k];
			}
		}
	}
	int t;cin >> t;
	int n,l,m;
	while(cin >> n >> l >> m){
		cout << d[n][l][m] << endl;
	}
	return 0;
}

