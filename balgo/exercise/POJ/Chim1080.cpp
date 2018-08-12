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
const int marktable[5][5] = {5,-1,-2,-1,-3,-1,5,-3,-2,-4,-2,-3,5,-2,-2,-1,-2,-2,5,-1,-3,-4,-2,-1,-(INF-1)};
short s1[102];
short s2[102];
short d[102][102];
int N1,N2;
int main(){
	int n;cin>>n;
	while(n--){
		char str[102];
		//memset(d,0,sizeof(d));
		cin >> N1;
		scanf("%s",str);
		for(int i = 0;i<N1;i++){
			if(str[i] == 'A') s1[i+1] = 0;
			else if(str[i] == 'C') s1[i+1] = 1;
			else if(str[i] == 'G') s1[i+1] = 2;
			else s1[i+1] = 3;
		}
		cin >> N2;
		scanf("%s",str);
		for(int i = 0;i<N2;i++){
			if(str[i] == 'A') s2[i+1] = 0;
			else if(str[i] == 'C') s2[i+1] = 1;
			else if(str[i] == 'G') s2[i+1] = 2;
			else s2[i+1] = 3;
		}		
		for(int i = 1;i <= N2;i++)
			d[0][i] = d[0][i-1]+marktable[s2[i]][4];
		for(int i = 1;i<=N1;i++)
			d[i][0] = d[i-1][0]+marktable[s1[i]][4];
		for(int i = 1;i <= N1;i++){
			for(int j = 1;j <= N2;j++){
				if(s1[i] == s2[j]) d[i][j] = d[i-1][j-1] +5;
				else d[i][j] = max(max(d[i-1][j]+marktable[s1[i]][4],
									d[i][j-1]+marktable[s2[j]][4]),
									d[i-1][j-1]+marktable[s1[i]][s2[j]]);
			}
		}
		cout << d[N1][N2] << endl;
	}
	return 0;
}
