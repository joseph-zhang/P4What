#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
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
#include<sstream>
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
int r,c;
int main(){
	freopen("input.txt","r",stdin);
	 
	while(cin >> r >> c){
		char line[c+5];
		int cnt = 0;
		for(int i = 0;i < r;i++){
			scanf("%s",line);
			for(int j = 0;j < c;j++){
				if(line[j]!= '.')cnt++;
				else if(cnt&1)cnt+=2;
			}
		}
		printf("%d\n",cnt>>1);
	}
	return 0;
}

