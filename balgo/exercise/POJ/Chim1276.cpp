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
int weight[1002],number[1002];
bool c[100002];
int main(){
	int cash,N;
	while(cin >> cash >> N){
		for(int i = 1;i <= N;i++)
			scanf("%d%d",&number[i],&weight[i]);
		memset(c,false,sizeof(c));
		c[0] = true;
		for(int i = 1;i <= N;i++){
			int num = min(number[i],cash/weight[i]);
			for(int k = 1;num > 0;k *= 2){
				if(k > num) k = num;
				num -= k;
				for(int j = cash;j >= weight[i]*k;j--)
					c[j] = c[j] || c[j - weight[i]*k];
			}
		}
		int res = cash;
		for(;c[res] >= 0;res--)
			if(c[res]) break;
		cout << res << endl;
	}
	return 0;
}
