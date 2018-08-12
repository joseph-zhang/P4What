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
bool row[10][10];
bool column[10][10];
bool sqr[10][10];
int sudoku[10][10];
bool ok;
inline int grid(int i,int j){
	return (i-1)/3*3+(j-1)/3+1;
}
void dfs(int k){
	if(k == 82){
		ok = true;
		for(int i = 1;i <= 9;i++){
			for(int j = 1;j <= 9;j++)
				printf("%d",sudoku[i][j]);
			cout << endl;
		}
		return;
	}
	int r = (k-1)/9+1;
	int c = ((k-1) % 9) + 1;
	int g = grid(r,c);
	if(sudoku[r][c]) {dfs(k+1);return;}
	for(int i = 1;i <= 9;i++){
		if((!row[r][i])&&(!column[c][i])&&(!sqr[g][i])){
			sudoku[r][c] = i;
			row[r][i] = column[c][i] = sqr[g][i]= true;
			dfs(k+1);
			if(ok) return;
			sudoku[r][c] = 0;
			row[r][i] = column[c][i] = sqr[g][i]= false;
		}
	}
}
int main(){
	int n;cin >> n;
	while(n--){
		ok = false;
		memset(row,false,sizeof(row));
		memset(column,false,sizeof(column));
		memset(sqr,false,sizeof(sqr));
		char line[11];
		for(int i = 1;i <=9;i++){
			scanf("%s",line);
			for(int j = 0;j < 9;j++){
				int temp = line[j]-'0';
				int v = j + 1;
				sudoku[i][v] = temp;
				row[i][temp] = column[v][temp] = true;
				sqr[grid(i,v)][temp] = true;
			}
		}
		dfs(1);
	}
	return 0;
}
