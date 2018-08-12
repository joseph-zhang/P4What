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
char s[100020];
int next[100020];
int last,cur;
int main(){
	while(scanf("%s",s+1) != EOF){
		memset(next,0,sizeof(next)); 
		next[0] = 0;
		last = cur = 0;
		int N = strlen(s+1);
		for(int i = 1;i <= N;i++){
			char cc = s[i];
			if(cc == '[') cur = 0;
			else if(cc == ']') cur = last;
			else{
				next[i] = next[cur];
				next[cur] = i;
				if(cur == last)last = i;
				cur = i;
			}
		}
		for(int i = next[0];i != 0;i = next[i])
			printf("%c",s[i]);
		cout << endl;
	}
	return 0;
}
