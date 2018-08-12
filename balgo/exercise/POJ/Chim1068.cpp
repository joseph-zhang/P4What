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
int N;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		cin >> N;
		char str[N+4];
		vector<int> ans;
		int sp = 0;
		int prenum = 0;
		for(int i = 0;i < N;i++){
			int num;scanf("%d",&num);
			for(int j = 0;j < num-prenum;j++)str[sp++] = '(';
			str[sp++] = ')';
			prenum = num;
		}
		for(int i = 0;i < sp;i++){
			if(str[i] == ')'){
				int balance = 1;
				int cnt = 0;
				for(int j = i-1;j >= 0;j--){
					if(balance == 0)break;
					if(str[j] == ')')balance+=1;
					if(str[j] == '('){balance-=1;cnt++;}
				}
				ans.push_back(cnt);
			}
		}
		for(int i = 0;i < ans.size()-1;i++)
			cout << ans[i] << " ";
		cout << ans[ans.size()-1] << endl;
	}
	return 0;
}
