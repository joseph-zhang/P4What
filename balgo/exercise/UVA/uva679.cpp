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
#define LL long long
using namespace std;
int N,D,I;
int main(){
	cin >> N;
	for(int i = 0;i < N;i++){
		cin >> D >> I;
		int k = 1;
		for(int i = 0;i < D-1;i++){
			if(I&1){k = 2*k;I = (I+1)/2;}
			else{k = 2*k+1;I = I/2;}
		}
		cout << k << endl;
	}
	scanf("%d",&D);
	return 0;
}
