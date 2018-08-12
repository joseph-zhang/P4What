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

string str,words[602];
int match[602];
int d[302];
int w,l;

int main(){
	cin >> w >> l;
	cin >> str;
	str = "0" + str; 
	for(int i = 1;i <= w;i++) cin >> words[i];
	for(int i = 1;i <= l;i++){
		for(int j = 1;j <= w;j++) match[j] = words[j].size()-1;
		d[i] = i;
		for(int j = i;j > 0;j--){
			for(int k = 1;k <= w;k++){
				if(match[k] >=0 && str[j] == words[k][match[k]])
					match[k]--;
				if(match[k] < 0){
					int sz = words[k].size();
					d[i] = min(d[i],d[j-1]+i-j+1-sz);
				}
			}
		}
	}
	cout << d[l] << endl;
	return 0;
}
