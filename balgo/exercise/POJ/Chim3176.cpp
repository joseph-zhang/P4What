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

int train[352][352];
int N;
int main(){
	cin >> N;
	for(int i = 1;i <= N;i++)
		for(int j = 1;j <= i;j++)
			scanf("%d",&train[i][j]);
	for(int i = N-1;i > 0;i--)
		for(int j = 1;j <= i;j++)
			train[i][j] = max(train[i+1][j],train[i+1][j+1])+train[i][j];
	cout << train[1][1]  << endl;
	return 0;
}
