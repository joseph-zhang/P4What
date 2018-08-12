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
int a[10];
int maxd,n;

bool isSorted(int *p){
	for(int i = 0;i < n-1;i++)
		if(p[i] >= p[i+1]) return false;
	return true;
}
int h(){
	int cnt = 0;
	for(int i = 0;i < n-1;i++)
		if(a[i]+1 != a[i+1])cnt++;
	if(a[n-1] != n)cnt++;
	return cnt;
}
bool IDAs(int d){
	if(isSorted(a))return true;
	if(3*(maxd - d) < h())return false;
	int olda[10],b[10];
	memcpy(olda,a,sizeof(a));
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			int cnt = 0;
			for(int k = 0;k < n;k++)
				if(k < i||k > j)b[cnt++] = olda[k];	
			for(int k = 0;k <= cnt;k++){
				int cnt1 = 0;
				for(int p = 0;p < k;p++)a[cnt1++] = b[p];
				for(int p = i;p <= j;p++)a[cnt1++] = olda[p];
				for(int p = k;p < cnt;p++)a[cnt1++] = b[p];
				if(IDAs(d+1)) return true;
			}
		}
	}
	return false;
}
int solve(){
	if(isSorted(a))return 0;
	for(maxd = 1;maxd < n;maxd++){
		if(IDAs(0))return maxd;
	}
	return n-1;
}
int main(){
	int times = 0;
	while(cin >> n){
		if(!n)break;
		for(int i = 0;i < n;i++)cin >> a[i];
		int res = solve();
		printf("Case %d: %d\n",++times,res);
	}
	return 0;
}
