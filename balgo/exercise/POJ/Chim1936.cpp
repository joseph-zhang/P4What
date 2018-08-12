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
string s,t;
int main(){
	while(cin >> s >> t){
		int i = 0,j = 0;
		while(i < s.size() && j < t.size()){
			if(s[i] == t[j])i++;
			j++;
		}
		cout << i << endl;
		if(i == s.size()) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}

