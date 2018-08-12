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
int t;
bool solve(int& W){
	int w1,l1,w2,l2;
	cin >> w1 >> l1 >> w2 >> l2;
	bool b1 = true,b2 = true;
	if(!w1)b1 = solve(w1);
	if(!w2)b2 = solve(w2);
	W = w1+w2;
	if(b1&&b2&&(w1*l1==w2*l2))return true;
	else return false;
}
int main(){
	cin >> t;
	while(t--){
		int W;
		if(solve(W))cout << "YES" << endl;
		else cout << "NO" << endl;
		if(t)cout << endl;
	}
	return 0;
}
