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
int track[1200];
int N;
int main(){
	while(cin >> N){
		if(!N){cout << endl;break;} 
		while(true){
			cin >> track[1];
			if(!track[1]){cout << endl;break;}
			for(int i = 2;i <= N;i++)scanf("%d",&track[i]);
			stack<int> station;
			int a =1,pb = 1;
			bool ok = true;
			while(pb <= N){
				if(a <= N && a == track[pb]){a++;pb++;}
				else if(!station.empty() && track[pb] == station.top()){
					pb++;
					station.pop();
				}
				else if(a <= N){station.push(a);a++;}
				else{ok = false;break;}
			}
			if(ok)cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
	return 0;	
}
