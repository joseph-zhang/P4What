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
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
bool paro[1002][1002];
char str[1002];
int d[1002];

void init(int sz){
	memset(paro,false,sizeof(paro));	
	for(int i = 0;i < sz;i++)paro[i][i] = true;
	for(int i = sz-1;i >= 0;i--){
		for(int j = i+1;j < sz;j++){
			if(j == i+1){
				if(str[i] == str[j])paro[i][j] = true;
				continue;
			}
			if(str[i] != str[j])continue;
			if(paro[i+1][j-1])paro[i][j] = true;
		}
	}
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int time;cin >> time;
	while(time--){
		scanf("%s",str);
		int sz = strlen(str);
		init(sz);
		d[0] = 1;
		for(int i = 1;i < sz;i++){
			d[i] = i+1;
			if(paro[0][i]){d[i] = 1;continue;}
			for(int j = 1;j <= i;j++){
				if(paro[j][i])d[i] = min(d[i],d[j-1]+1);
			}
		}
		cout << d[sz-1] << endl; 
	}
	return 0;
}
