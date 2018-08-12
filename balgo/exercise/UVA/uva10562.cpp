#include<iostream>
#include<vector>
#include<cstring>
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
const int maxn = 220;
int T,N;
char pic[maxn][maxn];
void dfs(int r,int c){
	printf("%c(",pic[r][c]);
	if(r+1 < N && pic[r+1][c]=='|'){
		int j = c;
		while(j-1 >= 0 && pic[r+2][j-1] == '-')j--;
		while(pic[r+2][j] == '-' && pic[r+3][j] != '\0'){
			if(!isspace(pic[r+3][j]))dfs(r+3,j);
			j++;
		}
	}
	cout << ")";
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	fgets(pic[0],maxn,stdin);
	sscanf(pic[0],"%d",&T);
	while(T--){
		N = 0;
		for(;;){
			fgets(pic[N],maxn,stdin);
			if(pic[N][0] == '#') break;
			N++;
		}
		if(N){		
			cout << "(";
			for(int i = 0;i < strlen(pic[0]);i++)
				if(!isspace(pic[0][i])){dfs(0,i);break;}
			cout << ")" << endl;
		}
	}
	return 0;
}
