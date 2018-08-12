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
int prime[1040000];
int bigNum[102];
int L,cnt;
int n;
int sieve(){
	bool sie[1040000];
	int k = 0;
	for(int i = 2;i < 1040000;i++){
		if(!sie[i]) prime[k++] = i;
		for(int j = 0;i*prime[j] < 1040000;j++){
			sie[i*prime[j]] = true;
			if(i%prime[j] == 0) break;
		}
	}
}
void transfer(char *num){
	cnt = strlen(num);
	int trial = cnt-1;
	for(int i = 0;i <= cnt/3;i++){
		if(trial < 0) {n = i-1;break;}
		if(trial == 1) {bigNum[i] = num[trial]-'0' + (num[trial-1]-'0')*10;n = i;break;}
		if(trial == 0) {bigNum[i] = num[trial]-'0';n = i;break;}
		bigNum[i] = (num[trial]-'0') + 
					(num[trial-1]-'0')*10 + (num[trial-2]-'0')*100;
		trial -= 3;
	}
}
int main(){
	char k[102];
	sieve();
	while(scanf("%s%d",k,&L) != EOF){
		if(!L) break;
		memset(bigNum,0,sizeof(bigNum));
		transfer(k);
		int res = 0;
		for(int i = 0;prime[i] < L;i++){
			int s = 0;
			for(int j = n;j >= 0;j--)
				s = (s*1000 + bigNum[j])%prime[i];
			if(!s){res = prime[i];break;}
		}
		if(res) cout << "BAD" <<" " << res << endl;
		else cout << "GOOD" << endl;
	}
	return 0;
}
