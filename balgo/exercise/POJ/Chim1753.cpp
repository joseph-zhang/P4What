#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<string.h>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
using namespace std;

const int dx[5] = {0,1,-1,0,0};
const int dy[5] = {0,0,0,1,-1};
int chess[4][4];
int black = 0;
int minc = 33;
bool isvalid(int x,int y){
	if(x < 0 || x >= 4 || y < 0 || y >= 4) return false;
	return true;
}
void flip(int s){
	int x = s / 4;
	int y = s % 4;
	for(int i = 0;i < 5;i++){
		int newx = x+dx[i];
		int newy = y+dy[i];
		if(isvalid(newx,newy)){
			if(chess[newx][newy])black--;
			else black++;
			chess[newx][newy] = !chess[newx][newy];
		}	
	}
}
void backtracking(int s,int cnt){
	if(!(black%16)){
		minc = min(minc,cnt);
		return;	
	}
	if(s >= 16) return;
	backtracking(s+1,cnt);
	flip(s);
	backtracking(s+1,cnt+1);
	flip(s);
}

int main(){
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			char c;
			cin >> c;
			if(c == 'w') chess[i][j] = 0;
			if(c == 'b') {chess[i][j] = 1;black++;}			
		}
	}
	backtracking(0,0);
	if(minc == 33)cout << "Impossible" << endl;
	else cout << minc << endl;
	return 0;
}
