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
short d[5001][5001];
char str[5002];
int N;
int main(){
	cin >> N;
	scanf("%s",str);
	memset(d,0,sizeof(d));
	for(int i = N-2;i >= 0;i--){
		for(int j = i+1;j < N;j++){
			if(str[i] == str[j]){
				if((i+1)<= (j-1))
					d[i][j] = d[i+1][j-1];
			}
			else
				d[i][j] = min(d[i+1][j],d[i][j-1])+1;
		}
	}
	cout << d[0][N-1] << endl;
	return 0;
}
