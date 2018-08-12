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
int num[104],pay[104];
int d[104];
int N;
int main(){
	int m;
	cin >> m;
	while(m--){
		cin >> N;
		for(int i = 1;i <= N;i++)
			cin >> num[i] >> pay[i];
		fill(d,d+102,INF);
		d[0] = 0;
		for(int i = 1;i <= N;i++){
			for(int j = 0;j < i;j++){
				int temp = 10; 
				for(int k = j+1;k <= i;k++)
					temp += num[k];
				temp = temp*pay[i];
				d[i] = min(d[i],d[j]+temp);
			}
		}
		cout << d[N] << endl;
	}
	return 0;
}
