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
int n,k;
int sum[100010][35];
int d[100010][35];
const int hashSize = 500;
vector<int> hashTable[hashSize];

bool judge(int x,int y){
	for(int i = 0;i < k;i++)
		if(d[x][i] != d[y][i]) return false;
	return true;
}
int main(){
	cin >> n >> k;
	memset(sum,0,sizeof(sum));
	memset(d,0,sizeof(d));
	for(int i = 1;i <= n;i++){
		int num;
		scanf("%d",&num);
		for(int j = 0;j < k;j++){
			sum[i][j] = sum[i-1][j]+(num&1);
			num >>= 1;
		}
	}
	for(int i = 0;i <= n;i++){
		int hv = 0;
		for(int j = 0;j < k;j++){
			d[i][j] = sum[i][j] - sum[i][0];
			hv += d[i][j];
		}
		hv = abs(hv);
		hv %= hashSize;
		hashTable[hv].push_back(i);
	}
	int res = 0;
	for(int k = 0;k < hashSize;k++)
		if(hashTable[k].size() > 1)
			for(int i = 0;i < hashTable[k].size()-1;i++)
				for(int j = i+1;j < hashTable[k].size();j++)
					if(judge(hashTable[k][i],hashTable[k][j]))
						res = max(res,abs(hashTable[k][i]-hashTable[k][j]));
	cout << res << endl;
	return 0;
}
