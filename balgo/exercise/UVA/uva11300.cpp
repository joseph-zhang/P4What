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
LL A[1000020],C[1000020];
int N;
int main(){
	while(cin >> N){
		LL tot = 0;
		for(int i = 1;i <= N;i++){
			scanf("%lld",&A[i]);
			tot += A[i];
		}
		memset(C,0,sizeof(long long)*(N+2));
		LL M = tot/N;
		for(int i = 1;i < N;i++)
			C[i] = C[i-1]-M+A[i];
		sort(C,C+N);
		LL median = C[(N+1)/2];
		LL res = 0;
		for(int i = 0;i < N;i++)
			res += abs(median-C[i]);
		cout << res << endl;
	}
	return 0;
}
