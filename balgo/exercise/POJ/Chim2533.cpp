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


int seq[1001];
int d[1001];
int n;
int main(){
	while(cin >> n){
		if(!n) {cout << 0 << endl;continue;}
		for(int i = 0;i < n;i++)
			scanf("%d",&seq[i]);
		int res = 1;
		for(int i = 0;i < n;i++){
			d[i] = 1;
			for(int j = i-1;j >= 0;j--){
				if(seq[i] > seq[j]){
					d[i] = max(d[i],d[j]+1);
				}
			}
			res = max(res,d[i]);
		}
		cout << res << endl;
	}
	return 0;
}
