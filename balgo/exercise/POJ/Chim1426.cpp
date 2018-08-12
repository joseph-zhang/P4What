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

vector<int> remind;
int main(){
	int n;
	while(cin >> n){
		if(!n) break;
		int res[101];
		remind.clear();
		remind.push_back(INF);
		remind.push_back(1);
		int cnt;
		for(cnt = 2;remind[cnt-1];cnt++)
				remind.push_back((remind[cnt>>1]*10+(cnt&1))%n);
		cnt--;
		int dex = 0;
		for(;cnt;cnt>>=1)
			res[dex++] = cnt&1;
		for(dex -= 1;dex >= 0;dex--)
			cout << res[dex];
		cout << endl;
	}
	return 0;
}
