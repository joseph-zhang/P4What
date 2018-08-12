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

float line[1004];
int lis[1004],lds[1004];
int N;

void LIS(){
	fill(lis,lis+1002,1);
	lis[0] = 0;
	for(int i = 2;i <= N;i++)
		for(int j = 1;j < i;j++)
			if(line[j] < line[i])
				lis[i] = max(lis[i],lis[j]+1);
}
void LDS(){
	fill(lds,lds+1002,1);
	lds[N+1] = 0;
	for(int i = N-1;i > 0;i--)
		for(int j = i+1;j <= N;j++)
			if(line[i] > line[j])
				lds[i] = max(lds[i],lds[j]+1);
}
int main(){
	cin >> N;
	int res = 0;
	for(int i = 1;i <= N;i++)
		scanf("%f",&line[i]);
	LIS();LDS();
	for(int i = 0;i <= N;i++)
		for(int j = i+1;j <= N+1;j++)
				res = max(res,lis[i]+lds[j]);
	cout << N-res << endl;
	return 0;
}
