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
#include<cctype>
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
int N,L;
int s[100];
int cnt = -1;
bool ok = false;
bool judge(int site){
	for(int i = site-1;i >= 0;i -= 2){
		int p = i+(site-i+1)/2;
		bool isdif = false;
		for(int j = 0;j < (site-i+1)/2;j++)
			if(s[i+j] != s[p+j]){isdif = true;break;}
		if(!isdif) return false;
	}
	return true;
}
void backtracking(int x){
	if(++cnt == N){
		int gap1 = 0,gap2 = 0;
		for(int i = 0;i < x;i++){
			if(++gap1 == 5) {
				++gap2;
				if(gap2 == 16){ cout <<endl;gap2 = 0;}
				else cout << " ";
				gap1 = 1;
			}
			printf("%c",s[i]+'A');
		}
		cout << endl;
		cout << x << endl;
		ok = true;return;
	}
	for(int i = 0;i < L;i++){
		s[x] = i;
		if(judge(x))
			backtracking(x+1);
		if(ok) return;
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(cin >> N >> L){
		if(!(N||L)) break;
		ok = false;cnt = -1;
		backtracking(0);
	}
	return 0;
}
